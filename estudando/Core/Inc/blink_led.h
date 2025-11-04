/*
 * pisca_led.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nailsonchagas
 */

#ifndef INC_BLINK_LED_H_
#define INC_BLINK_LED_H_

#include "stm32g4xx_hal.h"
#include "cmsis_os.h"

typedef struct led_t {
    TickType_t led_period;
    uint16_t led_pin;
    GPIO_TypeDef *led_port;
    GPIO_PinState led_state;
    SemaphoreHandle_t led_mutex;
} BlinkLED;

void blink_led(void *param);
void get_led_state(BlinkLED *led_instance, GPIO_PinState *output);

#endif /* INC_BLINK_LED_H_ */
