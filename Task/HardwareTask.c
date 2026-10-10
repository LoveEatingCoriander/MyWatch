#include "MyTask.h"

osThreadId_t HardwareInitHandle;
const osThreadAttr_t HardwareTask_attributes={
  .name="HardwareTask",
  .priority=osPriorityHigh7,
  .stack_size=128*4,
};

void StartHardwareTask(void *argument){
    vTaskSuspendAll();

    LCD_Init();
    LCD_Open_Light();
    LCD_Set_Light(100);
    LCD_Fill(0, 0, 240, 280, BLACK); // 清屏验证
    CST816_Init();
    CST816_RESET();

    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    AHT_Init();
    BL24C02_Init();
    EEPROM_Init();
    EM7028_hrs_init();
    //Key_Port_Init();
    KT6328_GPIO_Init();
    LSM303DLH_Init();
    MPU_Init();
    SPL_init();

    xTaskResumeAll();
    vTaskDelete(NULL);
}

