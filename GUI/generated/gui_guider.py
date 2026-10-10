# Copyright 2026 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=240,h=280)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(240*280*4)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 240
disp_drv.ver_res = 280
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create screen_home
screen_home = lv.obj()
screen_home.set_size(240, 280)
screen_home.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home.set_style_bg_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_digital_clock_time
screen_home_digital_clock_time_time = [int(11), int(25), int(50), "AM"]
screen_home_digital_clock_time = lv.dclock(screen_home, "11:25:50 AM")
screen_home_digital_clock_time_timer = lv.timer_create_basic()
screen_home_digital_clock_time_timer.set_period(1000)
screen_home_digital_clock_time_timer.set_cb(lambda src: digital_clock_cb(screen_home_digital_clock_time_timer, screen_home_digital_clock_time, screen_home_digital_clock_time_time, True, True ))
screen_home_digital_clock_time.set_pos(67, 32)
screen_home_digital_clock_time.set_size(103, 22)
# Set style for screen_home_digital_clock_time, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_digital_clock_time.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_bg_color(lv.color_hex(0x0c0d0d), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_pad_top(4, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_digital_clock_time.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_datetext_date
screen_home_datetext_date = lv.label(screen_home)
screen_home_datetext_date.set_text("2023/07/31")
screen_home_datetext_date.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
screen_home_datetext_date.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_datetext_date_calendar = None
screen_home_datetext_date.add_event_cb(lambda e: datetext_event_handler(e, screen_home_datetext_date_calendar), lv.EVENT.ALL, None)
screen_home_datetext_date.set_pos(160, 4)
screen_home_datetext_date.set_size(76, 16)
# Set style for screen_home_datetext_date, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_datetext_date.set_style_text_color(lv.color_hex(0xd41a1a), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_text_font(test_font("montserratMedium", 10), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_text_letter_space(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_bg_color(lv.color_hex(0x010101), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_pad_top(3, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_datetext_date.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_img_heart
screen_home_img_heart = lv.img(screen_home)
screen_home_img_heart.set_src("B:MicroPython/_heart_alpha_50x50.bin")
screen_home_img_heart.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_img_heart.set_pivot(50,50)
screen_home_img_heart.set_angle(0)
screen_home_img_heart.set_pos(17, 122)
screen_home_img_heart.set_size(50, 50)
# Set style for screen_home_img_heart, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_img_heart.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_heart.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_heart.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_img_humidity
screen_home_img_humidity = lv.img(screen_home)
screen_home_img_humidity.set_src("B:MicroPython/_humidity_alpha_50x50.bin")
screen_home_img_humidity.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_img_humidity.set_pivot(50,50)
screen_home_img_humidity.set_angle(0)
screen_home_img_humidity.set_pos(181, 122)
screen_home_img_humidity.set_size(50, 50)
# Set style for screen_home_img_humidity, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_img_humidity.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_humidity.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_humidity.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_img_temp
screen_home_img_temp = lv.img(screen_home)
screen_home_img_temp.set_src("B:MicroPython/_temp_alpha_50x50.bin")
screen_home_img_temp.add_flag(lv.obj.FLAG.CLICKABLE)
screen_home_img_temp.set_pivot(50,50)
screen_home_img_temp.set_angle(0)
screen_home_img_temp.set_pos(99, 122)
screen_home_img_temp.set_size(50, 50)
# Set style for screen_home_img_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_img_temp.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_img_temp.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_label_heart
screen_home_label_heart = lv.label(screen_home)
screen_home_label_heart.set_text("65")
screen_home_label_heart.set_long_mode(lv.label.LONG.WRAP)
screen_home_label_heart.set_width(lv.pct(100))
screen_home_label_heart.set_pos(17, 176)
screen_home_label_heart.set_size(53, 16)
# Set style for screen_home_label_heart, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_label_heart.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_color(lv.color_hex(0xce0101), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_heart.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_label_temp
screen_home_label_temp = lv.label(screen_home)
screen_home_label_temp.set_text("36.1")
screen_home_label_temp.set_long_mode(lv.label.LONG.WRAP)
screen_home_label_temp.set_width(lv.pct(100))
screen_home_label_temp.set_pos(99, 176)
screen_home_label_temp.set_size(53, 18)
# Set style for screen_home_label_temp, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_label_temp.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_color(lv.color_hex(0xc91c1c), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_temp.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_label_humidity
screen_home_label_humidity = lv.label(screen_home)
screen_home_label_humidity.set_text("59.9")
screen_home_label_humidity.set_long_mode(lv.label.LONG.WRAP)
screen_home_label_humidity.set_width(lv.pct(100))
screen_home_label_humidity.set_pos(181, 176)
screen_home_label_humidity.set_size(53, 18)
# Set style for screen_home_label_humidity, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_label_humidity.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_color(lv.color_hex(0xc91c1c), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_humidity.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_cont_settings
screen_home_cont_settings = lv.obj(screen_home)
screen_home_cont_settings.set_pos(0, 0)
screen_home_cont_settings.set_size(240, 150)
screen_home_cont_settings.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for screen_home_cont_settings, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_cont_settings.set_style_border_width(2, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_border_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_border_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_border_side(lv.BORDER_SIDE.FULL, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_bg_opa(145, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_bg_color(lv.color_hex(0x8c8383), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_cont_settings.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create screen_home_label_light
screen_home_label_light = lv.label(screen_home_cont_settings)
screen_home_label_light.set_text("Light")
screen_home_label_light.set_long_mode(lv.label.LONG.WRAP)
screen_home_label_light.set_width(lv.pct(100))
screen_home_label_light.set_pos(171, 120)
screen_home_label_light.set_size(59, 18)
# Set style for screen_home_label_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_label_light.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_font(test_font("montserratMedium", 16), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_label_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create screen_home_slider_light
screen_home_slider_light = lv.slider(screen_home_cont_settings)
screen_home_slider_light.set_range(0, 100)
screen_home_slider_light.set_mode(lv.slider.MODE.NORMAL)
screen_home_slider_light.set_value(50, lv.ANIM.OFF)
screen_home_slider_light.set_pos(202, 13)
screen_home_slider_light.set_size(10, 100)
# Set style for screen_home_slider_light, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
screen_home_slider_light.set_style_bg_opa(60, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_radius(8, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_outline_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for screen_home_slider_light, Part: lv.PART.MAIN, State: lv.STATE.FOCUSED.
screen_home_slider_light.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.FOCUSED)

# Set style for screen_home_slider_light, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
screen_home_slider_light.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_radius(8, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for screen_home_slider_light, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
screen_home_slider_light.set_style_bg_opa(255, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_color(lv.color_hex(0x2195f6), lv.PART.KNOB|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.KNOB|lv.STATE.DEFAULT)
screen_home_slider_light.set_style_radius(8, lv.PART.KNOB|lv.STATE.DEFAULT)

screen_home.update_layout()

def screen_home_event_handler(e):
    code = e.get_code()
    indev = lv.indev_get_act()
    gestureDir = lv.DIR.NONE
    if indev is not None: gestureDir = indev.get_gesture_dir()
    if (code == lv.EVENT.GESTURE and lv.DIR.BOTTOM == gestureDir):
        if indev is not None: indev.wait_release()
        pass
        screen_home_cont_settings.clear_flag(lv.obj.FLAG.HIDDEN)
        
    if (code == lv.EVENT.CLICKED):
        pass
        screen_home_cont_settings.add_flag(lv.obj.FLAG.HIDDEN)
        
screen_home.add_event_cb(lambda e: screen_home_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(screen_home)

while SDL.check():
    time.sleep_ms(5)

