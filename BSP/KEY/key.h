#ifndef __KEY_H__
#define __KEY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define KEY_1_Pin GPIO_PIN_4
#define KEY_1_GPIO_Port GPIOA
#define KEY_1_EXTI_IRQn EXTI4_IRQn
#define KEY_2_Pin GPIO_PIN_5
#define KEY_2_GPIO_Port GPIOA
#define KEY_2_EXTI_IRQn EXTI9_5_IRQn

	
void Key_Port_Init(void);
void Key_Interrupt_Callback(void);
uint8_t KeyScan();




#ifdef __cplusplus
}
#endif
#endif

