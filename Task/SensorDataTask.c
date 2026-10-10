#include "MyTask.h"

osThreadId_t SensorDateTaskHandle;
const osThreadAttr_t SensorDataTask_attributes={
    .name="SensorData",
    .priority=osPriorityNormal4,
    .stack_size=256*4
};

static Sensor_Data sensor_data={0};

osMessageQueueId_t SensorDataQueueHandle;
const osMessageQueueAttr_t SensorData_attributes={
    .name="SensorDataQueue",
};

void StartSensorDataTask(void *augment){
    for(;;){
        AHT_Read(&sensor_data.humidity,&sensor_data.temp);
        sensor_data.altitude=Altitude_Calculate();
        sensor_data.pressure=Pressure_Calculate();
        osMessageQueuePut(SensorDataQueueHandle,&sensor_data,0,0);
        osDelay(500);
    }
}


