#include "MyTask.h"

osThreadId_t LCDTaskhandle;
const osThreadAttr_t LCDTask_attributes={
    .name="LCDTask",
    .priority=(osPriority_t) osPriorityNormal,
    .stack_size=128*4,
};


void LCDTask(void *augment){
    uint8_t data;
    for(;;){
        if(osMessageQueueGet(LCDUpdateQueueHandle,&data,0,osWaitForever)==osOK){
            if(data==1){
                LCD_Close_Light();
            }
            else if (data==2){
                LCD_Set_Light(100);
            }
        }
        osDelay(10);
    }
}

