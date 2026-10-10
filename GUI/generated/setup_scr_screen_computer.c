/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_computer(lv_ui *ui)
{
    //Write codes screen_computer
    ui->screen_computer = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_computer, 240, 280);
    lv_obj_set_scrollbar_mode(ui->screen_computer, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_computer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_computer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_computer, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_computer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_computer_btnm_num
    ui->screen_computer_btnm_num = lv_btnmatrix_create(ui->screen_computer);
    static const char *screen_computer_btnm_num_text_map[] = {"C", "%", "/", "*", "\n", "1", "2", "3", "+", "\n", "4", "5", "6", "-", "\n", "7", "8", "9", "=", "\n", "0", ".", "",};
    lv_btnmatrix_set_map(ui->screen_computer_btnm_num, screen_computer_btnm_num_text_map);
    lv_obj_set_pos(ui->screen_computer_btnm_num, 0, 110);
    lv_obj_set_size(ui->screen_computer_btnm_num, 240, 180);

    //Write style for screen_computer_btnm_num, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_computer_btnm_num, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_computer_btnm_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_computer_btnm_num, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_computer_btnm_num, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_computer_btnm_num, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_computer_btnm_num, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_computer_btnm_num, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_computer_btnm_num, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->screen_computer_btnm_num, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->screen_computer_btnm_num, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_computer_btnm_num, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_computer_btnm_num, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_computer_btnm_num, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_computer_btnm_num, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_computer_btnm_num, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_computer_btnm_num, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_computer_btnm_num, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_computer_btnm_num, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_computer_btnm_num, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_computer_btnm_num, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_computer_btnm_num, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_computer_btnm_num, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_computer_btnm_num, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_computer_btnm_num, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_computer_btnm_num, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_computer_btnm_num, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_computer_btnm_num, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes screen_computer_ta_input
    ui->screen_computer_ta_input = lv_textarea_create(ui->screen_computer);
    lv_textarea_set_text(ui->screen_computer_ta_input, "");
    lv_textarea_set_placeholder_text(ui->screen_computer_ta_input, "");
    lv_textarea_set_password_bullet(ui->screen_computer_ta_input, "*");
    lv_textarea_set_password_mode(ui->screen_computer_ta_input, false);
    lv_textarea_set_one_line(ui->screen_computer_ta_input, false);
    lv_textarea_set_accepted_chars(ui->screen_computer_ta_input, "");
    lv_textarea_set_max_length(ui->screen_computer_ta_input, 32);
//#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
//    lv_obj_add_event_cb(ui->screen_computer_ta_input, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
//#endif
    lv_obj_set_pos(ui->screen_computer_ta_input, 0, 20);
    lv_obj_set_size(ui->screen_computer_ta_input, 240, 60);

    //Write style for screen_computer_ta_input, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_computer_ta_input, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_computer_ta_input, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_computer_ta_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_computer_ta_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_computer_ta_input, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_computer_ta_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_computer_ta_input, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_computer_ta_input, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_computer_ta_input, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_computer_ta_input, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_computer_ta_input, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_computer_ta_input, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_computer_ta_input, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_computer_ta_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_computer_ta_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_computer_ta_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_computer_ta_input, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_computer_ta_input, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_computer_ta_input, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_computer_ta_input, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_computer_ta_input, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_computer_ta_input, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //The custom code of screen_computer.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_computer);

    //Init events for screen.
    events_init_screen_computer(ui);
}
