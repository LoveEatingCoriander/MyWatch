#include "MyTask.h"

osThreadId DateTimeTaskHandle;
const osThreadAttr_t DateTimeTask_attributes={
    .name="DateTime",
    .priority=osPriorityNormal2,
    .stack_size=128*4,
};

osMessageQueueId_t DateTimeQueueHandle;
const osMessageQueueAttr_t DateTimeQueue_attributes={
    .name="DateTimeQueue",
};

void StartDateTimeTask(void *augment){
    DateTime datetime={0};
    for(;;){
        HAL_RTC_GetTime(&hrtc,&datetime.time,RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc,&datetime.date,RTC_FORMAT_BIN);
        osMessageQueuePut(DateTimeQueueHandle,&datetime,0,0);
        osDelay(2);
    }
}


