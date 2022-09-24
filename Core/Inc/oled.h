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

#define OLED_DATA_MODE 0
#define OLED_COMMAND_MODE 1


struct OLED {

	uint8_t OLED_STATUS_FLAG;
	uint8_t OLED_SETCOLUMN[3];
	uint8_t OLED_SETROW[3];
	uint8_t RECTANGLE_FILL_CONFIG[2];
	uint8_t OLED_DRAW_RECTANGLE_BUFFER[DRAW_RECTANGLE_BUFFER_SIZE];
	uint8_t OLED_DRAW_LINE_BUFFER[DRAW_LINE_BUFFER_SIZE];
	char string_buffer[10];

};


void OLED_init(struct OLED *OLED);
void OLED_sendCommand(uint8_t *OLED_COMMAND, uint8_t number_of_bytes);
void OLED_sendData(uint8_t *OLED_DATA, uint8_t number_of_bytes);
void OLED_setFillColor(uint8_t *rectangle_buffer, uint8_t *line_buffer, uint8_t colorR, uint8_t colorG, uint8_t colorB);
void OLED_drawRect(uint8_t *rectangle_buffer, uint8_t *fill_buffer, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fill_flag);
void OLED_setCursor(uint8_t x, uint8_t y, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW);
void OLED_drawChar_CMD(char c);
void OLED_drawString(char *string_buffer, uint8_t x, uint8_t y, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW);
void OLED_drawChar(uint8_t x, uint8_t y, char c, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW);



#endif /* INC_OLED_H_ */
