/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_home;
	bool screen_home_del;
	lv_obj_t *screen_home_datetext_date;
	lv_obj_t *screen_home_img_heart;
	lv_obj_t *screen_home_img_humidity;
	lv_obj_t *screen_home_img_temp;
	lv_obj_t *screen_home_label_heart;
	lv_obj_t *screen_home_label_temp;
	lv_obj_t *screen_home_label_humidity;
	lv_obj_t *screen_home_cont_settings;
	lv_obj_t *screen_home_label_light;
	lv_obj_t *screen_home_slider_light;
	lv_obj_t *screen_home_btn_close;
	lv_obj_t *screen_home_btn_close_label;
	lv_obj_t *screen_home_btn_settings;
	lv_obj_t *screen_home_btn_settings_label;
	lv_obj_t *screen_home_btn_menu;
	lv_obj_t *screen_home_btn_menu_label;
	lv_obj_t *screen_home_label_1;
	lv_obj_t *screen_menu;
	bool screen_menu_del;
	lv_obj_t *screen_menu_btn_calendar;
	lv_obj_t *screen_menu_btn_calendar_label;
	lv_obj_t *screen_menu_btn_game;
	lv_obj_t *screen_menu_btn_game_label;
	lv_obj_t *screen_menu_btn_settings;
	lv_obj_t *screen_menu_btn_settings_label;
	lv_obj_t *screen_menu_btn_data;
	lv_obj_t *screen_menu_btn_data_label;
	lv_obj_t *screen_menu_btn_computer;
	lv_obj_t *screen_menu_btn_computer_label;
	lv_obj_t *screen_menu_btn_other;
	lv_obj_t *screen_menu_btn_other_label;
	lv_obj_t *screen_menu_btn_StepWatch;
	lv_obj_t *screen_menu_btn_StepWatch_label;
	lv_obj_t *screen_computer;
	bool screen_computer_del;
	lv_obj_t *screen_computer_btnm_num;
	lv_obj_t *screen_computer_ta_input;
	lv_obj_t *screen_calendar;
	bool screen_calendar_del;
	lv_obj_t *screen_calendar_calendar_date;
	lv_obj_t *screen_Data;
	bool screen_Data_del;
	lv_obj_t *screen_Data_table_Data;
	lv_obj_t *screen_StepWatch;
	bool screen_StepWatch_del;
	lv_obj_t *screen_Setting;
	bool screen_Setting_del;
	lv_obj_t *screen_Game;
	bool screen_Game_del;
	lv_obj_t *screen_Lock;
	bool screen_Lock_del;
	lv_obj_t *screen_Lock_ta_pwd;
	lv_obj_t *screen_Lock_btnm_pwd;
	lv_obj_t *screen_Lock_label_password;
	lv_obj_t *screen_Lock_win_password;
	lv_obj_t *screen_Lock_win_password_item0;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_home(lv_ui *ui);
void setup_scr_screen_menu(lv_ui *ui);
void setup_scr_screen_computer(lv_ui *ui);
void setup_scr_screen_calendar(lv_ui *ui);
void setup_scr_screen_Data(lv_ui *ui);
void setup_scr_screen_StepWatch(lv_ui *ui);
void setup_scr_screen_Setting(lv_ui *ui);
void setup_scr_screen_Game(lv_ui *ui);
void setup_scr_screen_Lock(lv_ui *ui);
LV_IMG_DECLARE(_heart_alpha_50x50);
LV_IMG_DECLARE(_humidity_alpha_50x50);
LV_IMG_DECLARE(_temp_alpha_50x50);

LV_FONT_DECLARE(lv_font_montserratMedium_10)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_12)


#ifdef __cplusplus
}
#endif
#endif
