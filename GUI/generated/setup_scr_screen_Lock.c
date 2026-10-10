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



void setup_scr_screen_Lock(lv_ui *ui)
{
    //Write codes screen_Lock
    ui->screen_Lock = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_Lock, 240, 280);
    lv_obj_set_scrollbar_mode(ui->screen_Lock, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_Lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_Lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_Lock_ta_pwd
    ui->screen_Lock_ta_pwd = lv_textarea_create(ui->screen_Lock);
    lv_textarea_set_text(ui->screen_Lock_ta_pwd, "");
    lv_textarea_set_placeholder_text(ui->screen_Lock_ta_pwd, "");
    lv_textarea_set_password_bullet(ui->screen_Lock_ta_pwd, "*");
    lv_textarea_set_password_mode(ui->screen_Lock_ta_pwd, true);
    lv_textarea_set_one_line(ui->screen_Lock_ta_pwd, false);
    lv_textarea_set_accepted_chars(ui->screen_Lock_ta_pwd, "");
    lv_textarea_set_max_length(ui->screen_Lock_ta_pwd, 8);
//#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
 //   lv_obj_add_event_cb(ui->screen_Lock_ta_pwd, ta_event_cb, LV_EVENT_ALL, ui->g_kb_top_layer);
//#endif
    lv_obj_set_pos(ui->screen_Lock_ta_pwd, 0, 25);
    lv_obj_set_size(ui->screen_Lock_ta_pwd, 240, 60);

    //Write style for screen_Lock_ta_pwd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_Lock_ta_pwd, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Lock_ta_pwd, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Lock_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_Lock_ta_pwd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_Lock_ta_pwd, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Lock_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Lock_ta_pwd, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Lock_ta_pwd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_Lock_ta_pwd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Lock_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Lock_ta_pwd, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Lock_ta_pwd, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Lock_ta_pwd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Lock_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Lock_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Lock_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Lock_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_Lock_ta_pwd, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_Lock_ta_pwd, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Lock_ta_pwd, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Lock_ta_pwd, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Lock_ta_pwd, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write codes screen_Lock_btnm_pwd
    ui->screen_Lock_btnm_pwd = lv_btnmatrix_create(ui->screen_Lock);
    static const char *screen_Lock_btnm_pwd_text_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", "OK", "C", "",};
    lv_btnmatrix_set_map(ui->screen_Lock_btnm_pwd, screen_Lock_btnm_pwd_text_map);
    lv_obj_set_pos(ui->screen_Lock_btnm_pwd, 0, 121);
    lv_obj_set_size(ui->screen_Lock_btnm_pwd, 240, 150);

    //Write style for screen_Lock_btnm_pwd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_Lock_btnm_pwd, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Lock_btnm_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Lock_btnm_pwd, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Lock_btnm_pwd, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Lock_btnm_pwd, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_Lock_btnm_pwd, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Lock_btnm_pwd, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Lock_btnm_pwd, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui->screen_Lock_btnm_pwd, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui->screen_Lock_btnm_pwd, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Lock_btnm_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Lock_btnm_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Lock_btnm_pwd, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Lock_btnm_pwd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_Lock_btnm_pwd, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_Lock_btnm_pwd, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Lock_btnm_pwd, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Lock_btnm_pwd, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Lock_btnm_pwd, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_Lock_btnm_pwd, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Lock_btnm_pwd, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Lock_btnm_pwd, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Lock_btnm_pwd, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Lock_btnm_pwd, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Lock_btnm_pwd, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Lock_btnm_pwd, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Lock_btnm_pwd, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //Write codes screen_Lock_label_password
    ui->screen_Lock_label_password = lv_label_create(ui->screen_Lock);
    lv_label_set_text(ui->screen_Lock_label_password, "passwoard:");
    lv_label_set_long_mode(ui->screen_Lock_label_password, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_Lock_label_password, 5, 30);
    lv_obj_set_size(ui->screen_Lock_label_password, 101, 23);

    //Write style for screen_Lock_label_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_Lock_label_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Lock_label_password, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Lock_label_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_Lock_label_password, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Lock_label_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_Lock_win_password
    ui->screen_Lock_win_password = lv_win_create(ui->screen_Lock, 41);
    lv_obj_t * screen_Lock_win_password_title = lv_win_add_title(ui->screen_Lock_win_password, "title");
    ui->screen_Lock_win_password_item0 = lv_win_add_btn(ui->screen_Lock_win_password, LV_SYMBOL_CLOSE, 40);
    lv_obj_t *screen_Lock_win_password_label = lv_label_create(lv_win_get_content(ui->screen_Lock_win_password));
    lv_label_set_text(screen_Lock_win_password_label, "Password is wrong!!!");
    lv_obj_set_scrollbar_mode(lv_win_get_content(ui->screen_Lock_win_password), LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_pos(ui->screen_Lock_win_password, 26, 53);
    lv_obj_set_size(ui->screen_Lock_win_password, 180, 100);
    lv_obj_set_scrollbar_mode(ui->screen_Lock_win_password, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_Lock_win_password, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_Lock_win_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_Lock_win_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Lock_win_password, lv_color_hex(0xeeeef6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Lock_win_password, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->screen_Lock_win_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Lock_win_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_Lock_win_password_extra_content_main_default
    static lv_style_t style_screen_Lock_win_password_extra_content_main_default;
    ui_init_style(&style_screen_Lock_win_password_extra_content_main_default);

    lv_style_set_bg_opa(&style_screen_Lock_win_password_extra_content_main_default, 255);
    lv_style_set_bg_color(&style_screen_Lock_win_password_extra_content_main_default, lv_color_hex(0xeeeef6));
    lv_style_set_bg_grad_dir(&style_screen_Lock_win_password_extra_content_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&style_screen_Lock_win_password_extra_content_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_screen_Lock_win_password_extra_content_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_Lock_win_password_extra_content_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_Lock_win_password_extra_content_main_default, 0);
    lv_style_set_text_line_space(&style_screen_Lock_win_password_extra_content_main_default, 2);
    lv_obj_add_style(lv_win_get_content(ui->screen_Lock_win_password), &style_screen_Lock_win_password_extra_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_Lock_win_password_extra_header_main_default
    static lv_style_t style_screen_Lock_win_password_extra_header_main_default;
    ui_init_style(&style_screen_Lock_win_password_extra_header_main_default);

    lv_style_set_bg_opa(&style_screen_Lock_win_password_extra_header_main_default, 255);
    lv_style_set_bg_color(&style_screen_Lock_win_password_extra_header_main_default, lv_color_hex(0xe6e6e6));
    lv_style_set_bg_grad_dir(&style_screen_Lock_win_password_extra_header_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_text_color(&style_screen_Lock_win_password_extra_header_main_default, lv_color_hex(0x393c41));
    lv_style_set_text_font(&style_screen_Lock_win_password_extra_header_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_Lock_win_password_extra_header_main_default, 255);
    lv_style_set_text_letter_space(&style_screen_Lock_win_password_extra_header_main_default, 0);
    lv_style_set_text_line_space(&style_screen_Lock_win_password_extra_header_main_default, 2);
    lv_style_set_pad_top(&style_screen_Lock_win_password_extra_header_main_default, 5);
    lv_style_set_pad_right(&style_screen_Lock_win_password_extra_header_main_default, 5);
    lv_style_set_pad_bottom(&style_screen_Lock_win_password_extra_header_main_default, 5);
    lv_style_set_pad_left(&style_screen_Lock_win_password_extra_header_main_default, 5);
    lv_style_set_pad_column(&style_screen_Lock_win_password_extra_header_main_default, 5);
    lv_obj_add_style(lv_win_get_header(ui->screen_Lock_win_password), &style_screen_Lock_win_password_extra_header_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_Lock_win_password_extra_btns_main_default
    static lv_style_t style_screen_Lock_win_password_extra_btns_main_default;
    ui_init_style(&style_screen_Lock_win_password_extra_btns_main_default);

    lv_style_set_radius(&style_screen_Lock_win_password_extra_btns_main_default, 8);
    lv_style_set_border_width(&style_screen_Lock_win_password_extra_btns_main_default, 0);
    lv_style_set_bg_opa(&style_screen_Lock_win_password_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_Lock_win_password_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_Lock_win_password_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_shadow_width(&style_screen_Lock_win_password_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_Lock_win_password_item0, &style_screen_Lock_win_password_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_Lock.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_Lock);

    //Init events for screen.
    events_init_screen_Lock(ui);
}
