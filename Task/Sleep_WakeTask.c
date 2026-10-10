#include "MyTask.h"

osThreadId SleepTaskHandle;
const osThreadAttr_t SleepTask_attributes = {
    .name = "Sleep",
    .priority = osPriorityNormal6,
    .stack_size = 256 * 4,
};

osThreadId_t WakeUpTaskHandle;
const osThreadAttr_t WakeUpTask_attributes = {
    .name = "WakeUp",
    .priority = osPriorityNormal6,
    .stack_size = 256 * 4,
};

osMessageQueueId_t BreakIdleQueueHandle;
const osMessageQueueAttr_t BreakIdleQueue_attributes = {
    .name = "BreakIdleQueue",
};
osMessageQueueId_t IdleQueueHandle;
const osMessageQueueAttr_t IdleQueue_attributes = {
    .name = "IdleQueue",
};

osMessageQueueId_t LCDUpdateQueueHandle;
const osMessageQueueAttr_t LCDUpdateQueue_attributes={
    .name="LCDUpdate"
};

static uint32_t last_activity_time = 0;

// 任务1：处理关灯逻辑（每5秒检查一次是否该关灯）
void SleepTask(void *augment)
{
    uint8_t dummy = 0;
    for(;;)
    {
        // 阻塞等待 RTC 的定时唤醒信号（每5秒来一次）
        if (osMessageQueueGet(IdleQueueHandle, &dummy, 0, osWaitForever) == osOK)
        {
            // 获取当前时间，判断距离最后一次触摸是否已经超过 2 秒
            uint32_t now = HAL_GetTick(); // 假设 SysTick 已开启，单位 ms

            // 如果超过 2000ms 没有触摸，且灯还亮着，就关灯
            if ((now - last_activity_time) >= 5000)
            {
                if (LCD_Get_Light() != 0){
                    dummy=1;
                    osMessageQueuePut(LCDUpdateQueueHandle,&dummy,0,0);
                }
                    
            }
            // 如果未到2秒，什么都不做，等待下一个2秒周期再检查
        }
    }
}

// 任务2：处理触摸唤醒（开灯 + 更新时间戳）
void WakeUpTask(void *augment)
{
    uint8_t breakidle = 0;
    for(;;)
    {
        if (osMessageQueueGet(BreakIdleQueueHandle, &breakidle, 0, osWaitForever) == osOK)
        {
            // 1. 更新时间戳（重置空闲计时）
            last_activity_time = HAL_GetTick();

            // 2. 打开背光
            if (LCD_Get_Light() == 0)
            {
                breakidle = 2;
                osMessageQueuePut(LCDUpdateQueueHandle, &breakidle, 0, osWaitForever);
            }
            // 注意：这里不需要再往 IdleQueue 塞东西了！
        }
    }
}

// RTC中断：只负责发送“定时检查”的信号（不带有效载荷）
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
    uint8_t signal = 0; // 值无所谓，仅用作触发
    osMessageQueuePut(IdleQueueHandle, &signal, 0, 0);
}
