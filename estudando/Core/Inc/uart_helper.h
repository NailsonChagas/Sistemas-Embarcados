/*
 * uart_helper.h
 *
 *  Created on: Nov 2, 2025
 *      Author: nailsonchagas
 */

#ifndef INC_UART_HELPER_H_
#define INC_UART_HELPER_H_

#include "stm32g4xx_hal.h"
#include "cmsis_os.h"

extern SemaphoreHandle_t rx_mutex;
extern QueueHandle_t queue_rx; // fila da dados recebidos
extern QueueHandle_t queue_tx; // fila de dados a serem enviados

void init_UART_helper();
void send_data_UART();
void receive_data_UART();

#endif /* INC_UART_HELPER_H_ */

