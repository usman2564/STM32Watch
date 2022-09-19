/*
 * oled.c
 *
 *  Created on: Sep 10, 2022
 *      Author: usman
 */

#include "oled.h"
#include "font.h"

const uint8_t OLED_OFF = 0xAE;
const uint8_t OLED_ADDRESSMODE[2] = {0xA0, 0x73};
const uint8_t OLED_STARTLINE[2] = {0xA1, 0x00};
const uint8_t OLED_OFFSET[2] = {0xA2, 0x00};
const uint8_t OLED_NORMALMODE = 0xA4;
const uint8_t OLED_SETMULTIPLEX[2] = {0xA8, 0x3F};
const uint8_t OLED_MASTER_CONFIG[2] = {0xAD, 0x8E};
const uint8_t OLED_POWERMODE[2] = {0xB0, 0x00};
const uint8_t OLED_PRECHARGE[2] = {0xB1, 0x31};
const uint8_t OLED_SETFREQ[2] = {0xB3, 0xF0};
const uint8_t OLED_PRECHARGEA[2] = {0x8A, 0x64};
const uint8_t OLED_PRECHARGEB[2] = {0x8B, 0x78};
const uint8_t OLED_PRECHARGEC[2] = {0x8C, 0x64};
const uint8_t OLED_PRECHARGELEVEL[2] = {0xBB, 0x3A};
const uint8_t OLED_VCOMH[2] = {0xBE, 0x3E};



const uint8_t OLED_MASTER_CURRENT[2] = {0x87, 0x06};
const uint8_t OLED_CONTRAST[6] = {0x81, 0x91, 0x82, 0x50, 0x83, 0x7D};
const uint8_t OLED_ON = 0xAF;
const uint8_t OLED_DRAW_RECTANGLE = 0x22;
const uint8_t OLED_DRAW_LINE = 0x21;
const uint8_t OLED_FONTCOLOR[2] = {0xFF, 0xFF};
const uint8_t OLED_BACKCOLOR[2] = {0x00, 0x00};


uint8_t OLED_RECTANGLE_FILL_CONFIG[2] = {0x26, 0x01};
uint8_t OLED_DRAW_RECTANGLE_BUFFER[DRAW_RECTANGLE_BUFFER_SIZE] = {0, 0, 90, 60, 0, 0, 0, 0, 0, 40};
uint8_t OLED_DRAW_LINE_BUFFER[DRAW_LINE_BUFFER_SIZE] = {0, 0, 0, 0, 0, 0, 0};
uint8_t OLED_SETCOLUMN[] = {0x15, 0x00, 95};
uint8_t OLED_SETROW[] = {0x75, 0x00, 63};

void OLED_init()
{

	//active low CS pin should default high
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

	OLED_sendCommand(&hspi1, &OLED_OFF, 1);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_ADDRESSMODE, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_STARTLINE, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_OFFSET, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, &OLED_NORMALMODE, 1);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_SETMULTIPLEX, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_MASTER_CONFIG, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_POWERMODE, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_PRECHARGE, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_SETFREQ, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_PRECHARGEA, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_PRECHARGEB, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_PRECHARGEC, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_PRECHARGELEVEL, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_MASTER_CURRENT, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_CONTRAST, 6);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, &OLED_ON, 1);
	HAL_Delay(100);

}

void OLED_sendCommand(SPI_HandleTypeDef *hspi, uint8_t *OLED_COMMAND, uint8_t number_of_bytes)
{

	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(hspi, OLED_COMMAND, number_of_bytes, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_SET);
	delay_micros(100);

}

void OLED_setFillColor(uint8_t colorC, uint8_t colorB, uint8_t colorA)
{

	OLED_DRAW_RECTANGLE_BUFFER[4] = colorC;
	OLED_DRAW_RECTANGLE_BUFFER[5] = colorB;
	OLED_DRAW_RECTANGLE_BUFFER[6] = colorA;


	OLED_DRAW_RECTANGLE_BUFFER[7] = colorC;
	OLED_DRAW_RECTANGLE_BUFFER[8] = colorB;
	OLED_DRAW_RECTANGLE_BUFFER[9] = colorA;

	OLED_DRAW_LINE_BUFFER[4] = colorC;
	OLED_DRAW_LINE_BUFFER[5] = colorB;
	OLED_DRAW_LINE_BUFFER[6] = colorA;

}

void OLED_drawRect(uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fill_flag)
{

	OLED_DRAW_RECTANGLE_BUFFER[0] = startX;
	OLED_DRAW_RECTANGLE_BUFFER[1] = startY;
	OLED_DRAW_RECTANGLE_BUFFER[2] = endX;
	OLED_DRAW_RECTANGLE_BUFFER[3] = endY;


	if(fill_flag == OLED_FILL_TRUE)
		OLED_RECTANGLE_FILL_CONFIG[1] = 0x01;
	else
		OLED_RECTANGLE_FILL_CONFIG[1] = 0x00;

	OLED_sendCommand(&hspi1, OLED_RECTANGLE_FILL_CONFIG, 2);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, &OLED_DRAW_RECTANGLE, 1);
	HAL_Delay(100);
	OLED_sendCommand(&hspi1, OLED_DRAW_RECTANGLE_BUFFER, DRAW_RECTANGLE_BUFFER_SIZE);

}

void OLED_setCursor(uint8_t x, uint8_t y)
{
	OLED_SETCOLUMN[1] = x;
	OLED_SETCOLUMN[2] = x+CHAR_WIDTH-1;
	OLED_SETROW[1] = y;
	OLED_SETROW[2] = y+CHAR_HEIGHT-1;

	OLED_sendCommand(&hspi1, OLED_SETCOLUMN, 3);
	OLED_sendCommand(&hspi1, OLED_SETROW, 3);
}


void OLED_drawChar_CMD(char c)
{

	for(uint8_t i = 0; i < CHAR_WIDTH; i++)
	{

		for(uint8_t j = 0; j < CHAR_HEIGHT; j++)
		{
			if(((charMap[c - 0x30][i])<<j) & (0x8000))
				OLED_sendCommand(&hspi1, OLED_FONTCOLOR, 2);
			else
				OLED_sendCommand(&hspi1, OLED_BACKCOLOR, 2);
		}

	}

}

void OLED_drawString(char *string_buffer, uint8_t x, uint8_t y)
{
	uint8_t i = 0;
	while(string_buffer[i] != 0)
	{
		OLED_drawChar(x+(i*CHAR_WIDTH), y, string_buffer[i]);
		i++;
	}
}

void OLED_drawChar(uint8_t x, uint8_t y, char c)
{
	OLED_setCursor(x, y);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	OLED_drawChar_CMD(c);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

