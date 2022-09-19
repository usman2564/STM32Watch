/*
 * oled.h
 *
 *  Created on: Sep 10, 2022
 *      Author: usman
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "main.h"
#include "spi.h"
#include "tim.h"

#define SPI_TIMEOUT_DELAY 100
#define DRAW_RECTANGLE_BUFFER_SIZE 10
#define DRAW_LINE_BUFFER_SIZE 7

#define OLED_FILL_TRUE 1
#define OLED_FILL_FALSE 0

void OLED_sendCommand(SPI_HandleTypeDef *hspi, uint8_t *OLED_COMMAND, uint8_t number_of_bytes);
void OLED_init();
void OLED_drawRect(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fill_flag);
void OLED_drawPixelFONT();
void OLED_drawPixelBACK();
void OLED_setFillColor(uint8_t colorC, uint8_t colorB, uint8_t colorA);
void OLED_drawTopChar(char c);
void OLED_drawBotChar(char c);
void OLED_drawChar(uint8_t x, uint8_t y, char c);
void OLED_drawString(char *string_buffer, uint8_t x, uint8_t y);

#endif /* INC_OLED_H_ */
