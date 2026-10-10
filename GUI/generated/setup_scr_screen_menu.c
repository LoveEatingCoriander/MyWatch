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



void setup_scr_screen_menu(lv_ui *ui)
{
    //Write codes screen_menu
    ui->screen_menu = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_menu, 240, 280);
    lv_obj_set_scrollbar_mode(ui->screen_menu, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_menu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu, 234, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu, lv_color_hex(0xfbfbfb), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_calendar
    ui->screen_menu_btn_calendar = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_calendar_label = lv_label_create(ui->screen_menu_btn_calendar);
    lv_label_set_text(ui->screen_menu_btn_calendar_label, "calendar");
    lv_label_set_long_mode(ui->screen_menu_btn_calendar_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_calendar_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_calendar, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_calendar_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_calendar, 8, 19);
    lv_obj_set_size(ui->screen_menu_btn_calendar, 100, 50);

    //Write style for screen_menu_btn_calendar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_calendar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_calendar, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_calendar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_calendar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_calendar, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_calendar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_calendar, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_calendar, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_calendar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_calendar, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_game
    ui->screen_menu_btn_game = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_game_label = lv_label_create(ui->screen_menu_btn_game);
    lv_label_set_text(ui->screen_menu_btn_game_label, "game");
    lv_label_set_long_mode(ui->screen_menu_btn_game_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_game_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_game, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_game_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_game, 123, 19);
    lv_obj_set_size(ui->screen_menu_btn_game, 100, 50);

    //Write style for screen_menu_btn_game, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_game, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_game, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_game, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_game, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_game, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_game, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_game, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_game, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_game, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_settings
    ui->screen_menu_btn_settings = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_settings_label = lv_label_create(ui->screen_menu_btn_settings);
    lv_label_set_text(ui->screen_menu_btn_settings_label, "settings");
    lv_label_set_long_mode(ui->screen_menu_btn_settings_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_settings_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_settings, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_settings_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_settings, 8, 96);
    lv_obj_set_size(ui->screen_menu_btn_settings, 100, 50);

    //Write style for screen_menu_btn_settings, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_settings, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_settings, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_settings, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_settings, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_settings, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_settings, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_settings, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_settings, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_data
    ui->screen_menu_btn_data = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_data_label = lv_label_create(ui->screen_menu_btn_data);
    lv_label_set_text(ui->screen_menu_btn_data_label, "data");
    lv_label_set_long_mode(ui->screen_menu_btn_data_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_data_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_data, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_data_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_data, 123, 93);
    lv_obj_set_size(ui->screen_menu_btn_data, 100, 50);

    //Write style for screen_menu_btn_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_data, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_data, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_data, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_data, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_data, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_computer
    ui->screen_menu_btn_computer = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_computer_label = lv_label_create(ui->screen_menu_btn_computer);
    lv_label_set_text(ui->screen_menu_btn_computer_label, "computer");
    lv_label_set_long_mode(ui->screen_menu_btn_computer_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_computer_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_computer, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_computer_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_computer, 8, 173);
    lv_obj_set_size(ui->screen_menu_btn_computer, 100, 50);

    //Write style for screen_menu_btn_computer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_computer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_computer, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_computer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_computer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_computer, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_computer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_computer, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_computer, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_computer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_computer, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_other
    ui->screen_menu_btn_other = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_other_label = lv_label_create(ui->screen_menu_btn_other);
    lv_label_set_text(ui->screen_menu_btn_other_label, "other");
    lv_label_set_long_mode(ui->screen_menu_btn_other_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_other_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_other, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_other_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_other, 123, 174);
    lv_obj_set_size(ui->screen_menu_btn_other, 100, 50);

    //Write style for screen_menu_btn_other, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_other, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_other, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_other, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_other, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_other, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_other, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_other, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_other, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_other, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_other, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_menu_btn_StepWatch
    ui->screen_menu_btn_StepWatch = lv_btn_create(ui->screen_menu);
    ui->screen_menu_btn_StepWatch_label = lv_label_create(ui->screen_menu_btn_StepWatch);
    lv_label_set_text(ui->screen_menu_btn_StepWatch_label, "StepWatch");
    lv_label_set_long_mode(ui->screen_menu_btn_StepWatch_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_menu_btn_StepWatch_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_menu_btn_StepWatch, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_menu_btn_StepWatch_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_menu_btn_StepWatch, 8, 249);
    lv_obj_set_size(ui->screen_menu_btn_StepWatch, 100, 50);

    //Write style for screen_menu_btn_StepWatch, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_menu_btn_StepWatch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_menu_btn_StepWatch, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_menu_btn_StepWatch, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_menu_btn_StepWatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_menu_btn_StepWatch, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_menu_btn_StepWatch, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_menu_btn_StepWatch, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_menu_btn_StepWatch, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_menu_btn_StepWatch, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_menu_btn_StepWatch, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_menu.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_menu);

    //Init events for screen.
    events_init_screen_menu(ui);
}
