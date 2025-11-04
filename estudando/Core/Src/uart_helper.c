/*
 * uart_helper.c
 *
 *  Created on: Nov 2, 2025
 *      Author: nailsonchagas
 */
#include "uart_helper.h"

SemaphoreHandle_t rx_mutex = NULL;
QueueHandle_t queue_rx = NULL;
QueueHandle_t queue_tx = NULL;

void init_UART_helper()
{
	rx_mutex = xSemaphoreCreateBinary();
	queue_rx = xQueueCreate(16, sizeof(uint8_t));
	queue_tx = xQueueCreate(16, sizeof(uint8_t));
}

void send_data_UART()
{

}
