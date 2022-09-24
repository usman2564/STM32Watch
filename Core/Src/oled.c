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


void OLED_init(struct OLED *OLED)
{

	OLED->OLED_SETCOLUMN[0] = 0x15;
	OLED->OLED_SETROW[0] = 0x75;
	OLED->RECTANGLE_FILL_CONFIG[0] = 0x26;
	OLED->RECTANGLE_FILL_CONFIG[1] = 0x01;


	//active low CS pin should default high, place OLED in command mode
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_SET);

	OLED_sendCommand(&OLED_OFF, 1);
	HAL_Delay(100);
	OLED_sendCommand(OLED_ADDRESSMODE, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_STARTLINE, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_OFFSET, 2);
	HAL_Delay(100);
	OLED_sendCommand(&OLED_NORMALMODE, 1);
	HAL_Delay(100);
	OLED_sendCommand(OLED_SETMULTIPLEX, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_MASTER_CONFIG, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_POWERMODE, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_PRECHARGE, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_SETFREQ, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_PRECHARGEA, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_PRECHARGEB, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_PRECHARGEC, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_PRECHARGELEVEL, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_MASTER_CURRENT, 2);
	HAL_Delay(100);
	OLED_sendCommand(OLED_CONTRAST, 6);
	HAL_Delay(100);
	OLED_sendCommand(&OLED_ON, 1);
	HAL_Delay(100);


	OLED_setFillColor(OLED->OLED_DRAW_RECTANGLE_BUFFER, OLED->OLED_DRAW_LINE_BUFFER, 0, 0, 0);
	HAL_Delay(50);
	OLED_drawRect(OLED->OLED_DRAW_RECTANGLE_BUFFER, OLED->RECTANGLE_FILL_CONFIG, 0, 0, 95, 63, OLED_FILL_TRUE);
	HAL_Delay(50);
	OLED_setFillColor(OLED->OLED_DRAW_RECTANGLE_BUFFER, OLED->OLED_DRAW_LINE_BUFFER, 40, 40, 40);
	HAL_Delay(50);
	OLED_drawRect(OLED->OLED_DRAW_RECTANGLE_BUFFER, OLED->RECTANGLE_FILL_CONFIG, 12, 28, 83, 54, OLED_FILL_FALSE);
	HAL_Delay(50);

}

void OLED_sendCommand(uint8_t *OLED_COMMAND, uint8_t number_of_bytes)
{

	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, OLED_COMMAND, number_of_bytes, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(D_C_GPIO_Port, D_C_Pin, GPIO_PIN_SET);
	delay_micros(100);

}

void OLED_sendData(uint8_t *OLED_DATA, uint8_t number_of_bytes)
{
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, OLED_DATA, number_of_bytes, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(NOT_CS_GPIO_Port, NOT_CS_Pin, GPIO_PIN_SET);
	delay_micros(100);
}

void OLED_setFillColor(uint8_t *rectangle_buffer, uint8_t *line_buffer, uint8_t colorR, uint8_t colorG, uint8_t colorB)
{

	rectangle_buffer[4] = colorR;
	rectangle_buffer[5] = colorG;
	rectangle_buffer[6] = colorB;

	rectangle_buffer[7] = colorR;
	rectangle_buffer[8] = colorG;
	rectangle_buffer[9] = colorB;



	line_buffer[4] = colorR;
	line_buffer[5] = colorG;
	line_buffer[6] = colorB;

}

void OLED_drawRect(uint8_t *rectangle_buffer, uint8_t *fill_buffer, uint8_t startX, uint8_t startY, uint8_t endX, uint8_t endY, uint8_t fill_flag)
{

	rectangle_buffer[0] = startX;
	rectangle_buffer[1] = startY;
	rectangle_buffer[2] = endX;
	rectangle_buffer[3] = endY;


	if(fill_flag == OLED_FILL_TRUE)
		fill_buffer[1] = 0x01;
	else
		fill_buffer[1] = 0x00;

	OLED_sendCommand(fill_buffer, 2);
	HAL_Delay(100);
	OLED_sendCommand(&OLED_DRAW_RECTANGLE, 1);
	HAL_Delay(100);
	OLED_sendCommand(rectangle_buffer, DRAW_RECTANGLE_BUFFER_SIZE);

}

void OLED_setCursor(uint8_t x, uint8_t y, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW)
{
	OLED_SETCOLUMN[1] = x;
	OLED_SETCOLUMN[2] = x+CHAR_WIDTH-1;
	OLED_SETROW[1] = y;
	OLED_SETROW[2] = y+CHAR_HEIGHT-1;

	OLED_sendCommand(OLED_SETCOLUMN, 3);
	OLED_sendCommand(OLED_SETROW, 3);
}


void OLED_drawChar_CMD(char c)
{

	for(uint8_t i = 0; i < CHAR_WIDTH; i++)
	{

		for(uint8_t j = 0; j < CHAR_HEIGHT; j++)
		{
			if(((charMap[c - 0x30][i])<<j) & (0x8000))
				OLED_sendData(OLED_FONTCOLOR, 2);
			else
				OLED_sendData(OLED_BACKCOLOR, 2);
		}

	}

}

void OLED_drawString(char *string_buffer, uint8_t x, uint8_t y, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW)
{
	uint8_t i = 0;
	while(string_buffer[i] != 0)
	{
		OLED_drawChar(x+(i*CHAR_WIDTH), y, string_buffer[i], OLED_SETCOLUMN, OLED_SETROW);
		i++;
	}
}

void OLED_drawChar(uint8_t x, uint8_t y, char c, uint8_t *OLED_SETCOLUMN, uint8_t *OLED_SETROW)
{
	OLED_setCursor(x, y, OLED_SETCOLUMN, OLED_SETROW);
	OLED_drawChar_CMD(c);
}

