/*
 * rtc.c
 *
 *  Created on: Sep 17, 2022
 *      Author: usman
 */

#include "rtc.h"
#include "i2c.h"

uint8_t i2c_data_buf[5] = {0};

uint8_t RTC_getSeconds()
{

	i2c_data_buf[0] = RTC_SEC_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	//check return
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}

uint8_t RTC_getMins()
{

	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];

}

uint8_t RTC_getHours()
{

	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];

}

void RTC_init(uint8_t current_min_BCD, uint8_t current_hour_BCD)
{
	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	i2c_data_buf[1] = current_min_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	i2c_data_buf[1] = current_hour_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}


void RTC_getTime(uint8_t *time_array)
{
	time_array[0] = RTC_getSeconds();
	time_array[1] = RTC_getMins();
	time_array[2] = RTC_getHours();
}

void conv_BCD(uint8_t *time_array)
{
	uint8_t BCD_sec = time_array[0];
	uint8_t BCD_min = time_array[1];
	uint8_t BCD_hour = time_array[2];

	time_array[0] = ((BCD_sec>>4) & 0b00000111);
	time_array[1] = (BCD_sec & 0b00001111);

	time_array[2] = ((BCD_min>>4) & 0b00000111);
	time_array[3] = (BCD_min & 0b00001111);

	time_array[4] = ((BCD_hour>>4) & 0b00000011);
	time_array[5] = (BCD_hour & 0b00001111);

}

void RTC_updateMins(uint8_t tenmins, uint8_t onemins)
{
	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	i2c_data_buf[1] = (tenmins<<4 | onemins);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateHours(uint8_t tenhours, uint8_t onehours)
{
	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	i2c_data_buf[1] = (tenhours<<4 | onehours);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}



