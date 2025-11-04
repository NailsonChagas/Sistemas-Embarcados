/*
 * pisca_led.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nailsonchagas
 */
#include <blink_led.h>

void blink_led(void *param) {
	BlinkLED *led_param = (BlinkLED*)param;
	TickType_t prev_timer_cnt;

	led_param->led_mutex = xSemaphoreCreateMutex();

	while (1) {
		prev_timer_cnt = xTaskGetTickCount();

		xSemaphoreTake(led_param->led_mutex, portMAX_DELAY);
		HAL_GPIO_WritePin(led_param->led_port, led_param->led_pin, led_param->led_state);
		led_param->led_state = ~led_param->led_state;
		xSemaphoreGive(led_param->led_mutex);

		vTaskDelayUntil(&prev_timer_cnt, led_param->led_period);
	}
}

void get_led_state(BlinkLED *led_instance, GPIO_PinState *output)
{
	xSemaphoreTake(led_instance->led_mutex, portMAX_DELAY);
	*output = led_instance->led_state;
	xSemaphoreGive(led_instance->led_mutex);
}
