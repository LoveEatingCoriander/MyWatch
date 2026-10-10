#include "MyTask.h"

osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
    .name = "KeyTask",
    .priority = osPriorityNormal3,
    .stack_size = 256 * 4,
};

osMessageQueueId_t KeyQueueHandle;
const osMessageQueueAttr_t keyQueue_attributes = {
    .name = "KeyQueue",
};

osSemaphoreId KeyBinarySemHandle;
const osSemaphoreAttr_t KeyBinary_attributes = {
    .name = "KeyBinarySem",
};

static volatile uint32_t last_key_irq_tick = 0U;

void StartKeyTask(void *augment)
{

    for (;;)
    {
        if (osSemaphoreAcquire(KeyBinarySemHandle, osWaitForever) == osOK)
        {
            uint8_t keyvalue = KeyScan();
            osMessageQueuePut(KeyQueueHandle, &keyvalue, 0, 0);            
            osMessageQueuePut(BreakIdleQueueHandle, &keyvalue, 0, osWaitForever);             
        }
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    if (GPIO_Pin == KEY1_Pin || GPIO_Pin == KEY2_Pin)
    {
        if ((now - last_key_irq_tick) < 50U)
        {
            return;
        }
        last_key_irq_tick = now;

        if (KeyBinarySemHandle != NULL)
        {
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;
            xSemaphoreGiveFromISR( KeyBinarySemHandle, &xHigherPriorityTaskWoken );
        }
    }
}
