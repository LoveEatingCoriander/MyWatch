/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include <string.h>
static char input[32];
#include <stdlib.h>   // for atof
#include <math.h>     // for isinf, isnan

// 计算并显示结果，更新 input 缓冲区
static void compute_result(lv_ui *ui) {
    // 去掉末尾可能已有的 '='
    int len = strlen(input);
    if (len > 0 && input[len-1] == '=') {
        input[len-1] = '\0';
    }

    if (strlen(input) == 0) {
        return;  // 空输入不处理
    }

    // ---- 解析并顺序计算表达式 ----
    double result = 0.0;
    double current_num = 0.0;
    char current_op = '+';
    int i = 0;

    // 提取第一个数字
    if (input[i] >= '0' && input[i] <= '9' || input[i] == '.') {
        char temp[32] = {0};
        int idx = 0;
        while (input[i] >= '0' && input[i] <= '9' || input[i] == '.') {
            temp[idx++] = input[i++];
        }
        temp[idx] = '\0';
        current_num = atof(temp);
        result = current_num;
    } else {
        // 第一个字符不是数字，显示错误
        lv_textarea_set_text(ui->screen_computer_ta_input, "Error");
        input[0] = '\0';
        return;
    }

    // 循环处理运算符 + 数字
    while (input[i] != '\0' && input[i] != '=') {
        // 跳过空白（如果有）
        while (input[i] == ' ') i++;
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            current_op = input[i++];
        } else {
            break;  // 遇到非法字符，停止解析
        }
        while (input[i] == ' ') i++;
        if (input[i] >= '0' && input[i] <= '9' || input[i] == '.') {
            char temp[32] = {0};
            int idx = 0;
            while (input[i] >= '0' && input[i] <= '9' || input[i] == '.') {
                temp[idx++] = input[i++];
            }
            temp[idx] = '\0';
            current_num = atof(temp);
            // 执行运算
            switch (current_op) {
            case '+':
                result += current_num;
                break;
            case '-':
                result -= current_num;
                break;
            case '*':
                result *= current_num;
                break;
            case '/':
                if (current_num == 0.0) {
                    lv_textarea_set_text(ui->screen_computer_ta_input, "Error");
                    input[0] = '\0';
                    return;
                }
                result /= current_num;
                break;
            default:
                break;
            }
        } else {
            break;
        }
    }

    // ---- 格式化输出结果 ----
    if (isinf(result) || isnan(result)) {
        lv_textarea_set_text(ui->screen_computer_ta_input, "Error");
        input[0] = '\0';
        return;
    }

    char result_str[32];
    if (result == (int)result) {
        snprintf(result_str, sizeof(result_str), "%d", (int)result);
    } else {
        snprintf(result_str, sizeof(result_str), "%.6f", result);
        // 去掉末尾多余的 '0'
        char *p = result_str + strlen(result_str) - 1;
        while (p > result_str && *p == '0') p--;
        if (*p == '.') p--;
        *(p+1) = '\0';
    }

    // 显示结果，并更新 input 为结果字符串（以便继续运算）
    lv_textarea_set_text(ui->screen_computer_ta_input, result_str);
    strcpy(input, result_str);
}
#include <string.h>
#ifndef PWD
#define PWD "123"
#endif
static char pwd[10];

static void screen_home_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.screen_home_cont_settings, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            lv_obj_clear_flag(guider_ui.screen_home_cont_settings, LV_OBJ_FLAG_HIDDEN);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_home_btn_close_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_Lock, guider_ui.screen_Lock_del, &guider_ui.screen_home_del, setup_scr_screen_Lock, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_home_btn_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_home_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_home (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_home, screen_home_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_home_btn_close, screen_home_btn_close_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_home_btn_menu, screen_home_btn_menu_event_handler, LV_EVENT_ALL, ui);
}

static void screen_menu_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_BOTTOM:
        {
            lv_indev_wait_release(lv_indev_get_act());
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_menu_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_menu_btn_calendar_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_calendar, guider_ui.screen_calendar_del, &guider_ui.screen_menu_del, setup_scr_screen_calendar, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_btn_settings_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_Setting, guider_ui.screen_Setting_del, &guider_ui.screen_menu_del, setup_scr_screen_Setting, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_btn_data_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_Data, guider_ui.screen_Data_del, &guider_ui.screen_menu_del, setup_scr_screen_Data, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_btn_computer_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_computer, guider_ui.screen_computer_del, &guider_ui.screen_menu_del, setup_scr_screen_computer, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_menu_btn_StepWatch_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_StepWatch, guider_ui.screen_StepWatch_del, &guider_ui.screen_menu_del, setup_scr_screen_StepWatch, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_menu (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_menu, screen_menu_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_btn_calendar, screen_menu_btn_calendar_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_btn_settings, screen_menu_btn_settings_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_btn_data, screen_menu_btn_data_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_btn_computer, screen_menu_btn_computer_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_menu_btn_StepWatch, screen_menu_btn_StepWatch_event_handler, LV_EVENT_ALL, ui);
}

static void screen_computer_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_computer_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_computer_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_computer_btnm_num_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t * obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);

        const char *btn_text = lv_btnmatrix_get_btn_text(obj, id);
        lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
        if(strcmp(btn_text,"1")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"2")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"3")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"4")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"5")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"6")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"7")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"8")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"9")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"0")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"/")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"*")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"+")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"-")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"%")==0) {
            strcat(input,btn_text);
        }
        else if(strcmp(btn_text,"=")==0) {
            compute_result(ui);
        }
        else if(strcmp(btn_text,"C")==0) {
            memset(input,0,sizeof(input));
        }
        else if(strcmp(btn_text,".")==0) {
            strcat(input,btn_text);
        }

        lv_textarea_set_text(ui->screen_computer_ta_input, input);


        break;
    }
    default:
        break;
    }
}

static void screen_computer_ta_input_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

void events_init_screen_computer (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_computer, screen_computer_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_computer_btnm_num, screen_computer_btnm_num_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_computer_ta_input, screen_computer_ta_input_event_handler, LV_EVENT_ALL, ui);
}

static void screen_calendar_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_calendar_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_calendar (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_calendar, screen_calendar_event_handler, LV_EVENT_ALL, ui);
}

static void screen_Data_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_Data_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_Data (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_Data, screen_Data_event_handler, LV_EVENT_ALL, ui);
}

static void screen_StepWatch_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_StepWatch_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_StepWatch (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_StepWatch, screen_StepWatch_event_handler, LV_EVENT_ALL, ui);
}

static void screen_Setting_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_Setting_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_Setting (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_Setting, screen_Setting_event_handler, LV_EVENT_ALL, ui);
}

static void screen_Lock_btnm_pwd_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_t * obj = lv_event_get_target(e);
        uint32_t id = lv_btnmatrix_get_selected_btn(obj);
        lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
        if (!ui) return;
        const char *btn_text = lv_btnmatrix_get_btn_text(obj, id);
        if(strcmp(btn_text,"1")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"2")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"3")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"4")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"5")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"6")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"7")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"8")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"9")==0) {
            strcat(pwd,btn_text);
        }
        else if(strcmp(btn_text,"C")==0) {
            memset(pwd,0,sizeof(pwd));
        }
        else if(strcmp(btn_text,"OK")==0) {
            if(strcmp(pwd,PWD)==0) {
                memset(pwd,0,sizeof(pwd));
                ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_Lock_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                return;
            }
            else {
                lv_obj_clear_flag(ui->screen_Lock_win_password, LV_OBJ_FLAG_HIDDEN);
            }
            memset(pwd,0,sizeof(pwd));
        }
        lv_textarea_set_text(ui->screen_Lock_ta_pwd,pwd);
        break;
    }
    default:
        break;
    }
}

static void screen_Lock_win_password_item0_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_ui *ui = (lv_ui *)lv_event_get_user_data(e);
        lv_obj_add_flag(ui->screen_Lock_win_password, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_Lock (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_Lock_btnm_pwd, screen_Lock_btnm_pwd_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_Lock_win_password_item0, screen_Lock_win_password_item0_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
