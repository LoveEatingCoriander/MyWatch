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



void setup_scr_screen_Data(lv_ui *ui)
{
    //Write codes screen_Data
    ui->screen_Data = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_Data, 240, 280);
    lv_obj_set_scrollbar_mode(ui->screen_Data, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_Data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_Data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Data, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_Data_table_Data
    ui->screen_Data_table_Data = lv_table_create(ui->screen_Data);
    lv_table_set_col_cnt(ui->screen_Data_table_Data,2);
    lv_table_set_row_cnt(ui->screen_Data_table_Data,6);
    lv_table_set_cell_value(ui->screen_Data_table_Data,0,0,"Heart_Rate");
    lv_table_set_cell_value(ui->screen_Data_table_Data,1,0,"Spo2");
    lv_table_set_cell_value(ui->screen_Data_table_Data,2,0,"Temperature");
    lv_table_set_cell_value(ui->screen_Data_table_Data,3,0,"Humidity");
    lv_table_set_cell_value(ui->screen_Data_table_Data,4,0,"Pressure");
    lv_table_set_cell_value(ui->screen_Data_table_Data,5,0,"Altitude");
    lv_table_set_cell_value(ui->screen_Data_table_Data,0,1,"65");
    lv_table_set_cell_value(ui->screen_Data_table_Data,1,1,"0");
    lv_table_set_cell_value(ui->screen_Data_table_Data,2,1,"34");
    lv_table_set_cell_value(ui->screen_Data_table_Data,3,1,"59.9");
    lv_table_set_cell_value(ui->screen_Data_table_Data,4,1,"15");
    lv_table_set_cell_value(ui->screen_Data_table_Data,5,1,"10");
    lv_obj_set_pos(ui->screen_Data_table_Data, 0, 0);
    lv_obj_set_scrollbar_mode(ui->screen_Data_table_Data, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_Data_table_Data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_pad_top(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Data_table_Data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_Data_table_Data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_Data_table_Data, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_Data_table_Data, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Data_table_Data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Data_table_Data, lv_color_hex(0xd5dee6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Data_table_Data, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_Data_table_Data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_Data_table_Data, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_Data_table_Data, lv_color_hex(0x393c41), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_Data_table_Data, &lv_font_montserratMedium_12, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_Data_table_Data, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_Data_table_Data, LV_TEXT_ALIGN_CENTER, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_Data_table_Data, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_Data_table_Data, 3, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_Data_table_Data, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_Data_table_Data, lv_color_hex(0xd5dee6), LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_Data_table_Data, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_Data_table_Data, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_Data_table_Data, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_Data_table_Data, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_Data_table_Data, 10, LV_PART_ITEMS|LV_STATE_DEFAULT);

    //The custom code of screen_Data.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_Data);

    //Init events for screen.
    events_init_screen_Data(ui);
}
