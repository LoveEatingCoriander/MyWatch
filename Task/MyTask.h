#ifndef _MYTASK_H_
#define _MYTASK_H_

#include "main.h"

void lvglTask(void *augment);

extern osThreadId_t HardwareInitHandle;
extern const osThreadAttr_t HardwareTask_attributes;
void StartHardwareTask(void *argument);

extern osThreadId_t KeyTaskHandle;
extern const osThreadAttr_t KeyTask_attributes;
extern osMessageQueueId_t KeyQueueHandle;
extern const osMessageQueueAttr_t keyQueue_attributes;
extern osSemaphoreId KeyBinarySemHandle;
extern const osSemaphoreAttr_t KeyBinary_attributes;
void StartKeyTask(void *augment);

typedef struct 
{
    float temp;
    float humidity;
    float altitude;
    float pressure;
}Sensor_Data;
extern osThreadId_t SensorDateTaskHandle;
extern const osThreadAttr_t SensorDataTask_attributes;
extern osMessageQueueId_t SensorDataQueueHandle;
extern const osMessageQueueAttr_t SensorData_attributes;
void StartSensorDataTask(void *augment);

typedef struct{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
}DateTime;
extern osThreadId DateTimeTaskHandle;
extern const osThreadAttr_t DateTimeTask_attributes;
extern osMessageQueueId_t DateTimeQueueHandle;
extern const osMessageQueueAttr_t DateTimeQueue_attributes;
void StartDateTimeTask(void *augment);

extern osThreadId SleepTaskHandle;
extern const osThreadAttr_t SleepTask_attributes;
extern osThreadId_t WakeUpTaskHandle;
extern const osThreadAttr_t WakeUpTask_attributes;
extern osMessageQueueId_t BreakIdleQueueHandle;
extern const osMessageQueueAttr_t BreakIdleQueue_attributes;
extern osMessageQueueId_t IdleQueueHandle;
extern const osMessageQueueAttr_t IdleQueue_attributes;
extern osMessageQueueId_t LCDUpdateQueueHandle;
extern const osMessageQueueAttr_t LCDUpdateQueue_attributes;
void SleepTask(void *augment);
void WakeUpTask(void *augment);

extern osThreadId_t LCDTaskhandle;
extern const osThreadAttr_t LCDTask_attributes;
void LCDTask(void *augment);

#endif
