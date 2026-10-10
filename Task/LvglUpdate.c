#include "MyTask.h"

lv_ui guider_ui;

void lvglTask(void *augment)
{

    custom_init(&guider_ui);
    setup_ui(&guider_ui);
    uint8_t keyvalue = 0;
    Sensor_Data sensor_data = {0};
    DateTime datetime = {0};
    uint8_t update = 0;
    char data[16];
    for (;;)
    {
        if (osMessageQueueGet(KeyQueueHandle, &keyvalue, 0, 0) == osOK)
        {
            if (keyvalue == 1)
            {
                if (lv_scr_act() == guider_ui.screen_home)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_Lock, guider_ui.screen_Lock_del, &guider_ui.screen_home_del, setup_scr_screen_Lock, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_menu)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_home, guider_ui.screen_home_del, &guider_ui.screen_menu_del, setup_scr_screen_home, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_calendar)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_calendar_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_computer)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_computer_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_Game)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_Game_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_Setting)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_Setting_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_Data)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_Data_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_StepWatch)
                {
                    ui_load_scr_animation(&guider_ui, &guider_ui.screen_menu, guider_ui.screen_menu_del, &guider_ui.screen_StepWatch_del, setup_scr_screen_menu, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
                }
                else if (lv_scr_act() == guider_ui.screen_Lock)
                {
                    
                }
            }
        }
        if (osMessageQueueGet(SensorDataQueueHandle, &sensor_data, 0, 0) == osOK)
        {
            if (lv_obj_is_valid(guider_ui.screen_home_label_temp))
            {
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.temp);
                lv_label_set_text(guider_ui.screen_home_label_temp, data);
            }
            if (lv_obj_is_valid(guider_ui.screen_home_label_humidity))
            {
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.humidity);
                lv_label_set_text(guider_ui.screen_home_label_humidity, data);
            }
            if (lv_obj_is_valid(guider_ui.screen_Data_table_Data))
            {
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.temp);
                lv_table_set_cell_value(guider_ui.screen_Data_table_Data, 2, 1, data);
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.humidity);
                lv_table_set_cell_value(guider_ui.screen_Data_table_Data, 3, 1, data);
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.altitude);
                lv_table_set_cell_value(guider_ui.screen_Data_table_Data, 4, 1, data);
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%.1f", sensor_data.pressure);
                lv_table_set_cell_value(guider_ui.screen_Data_table_Data, 5, 1, data);
            }
        }
        if (osMessageQueueGet(DateTimeQueueHandle, &datetime, 0, 0) == osOK)
        {
            if (lv_obj_is_valid(guider_ui.screen_home_datetext_date))
            {
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%04d/%02d/%d", 2000 + datetime.date.Year, datetime.date.Month, datetime.date.WeekDay);
                lv_label_set_text(guider_ui.screen_home_datetext_date, data);
            }
            if (lv_obj_is_valid(guider_ui.screen_calendar_calendar_date))
            {
                lv_calendar_set_today_date(guider_ui.screen_calendar_calendar_date, 2000 + datetime.date.Year, datetime.date.Month, datetime.date.WeekDay);
                lv_calendar_set_showed_date(guider_ui.screen_calendar_calendar_date, 2000 + datetime.date.Year, datetime.date.Month);
            }
            if (lv_obj_is_valid(guider_ui.screen_home_label_1))
            {
                memset(data, 0, sizeof(data));
                snprintf(data, sizeof(data), "%02d:%02d:%02d", datetime.time.Hours, datetime.time.Minutes - 1, datetime.time.Seconds);
                lv_label_set_text(guider_ui.screen_home_label_1, data);
            }
        }

        lv_task_handler();
        osDelay(1);
    }
}
