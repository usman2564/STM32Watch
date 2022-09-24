/*
 * rtc.c
 *
 *  Created on: Sep 17, 2022
 *      Author: usman
 */

#include "rtc.h"
#include "i2c.h"


uint8_t RTC_getSeconds(uint8_t *i2c_data_buf)
{

	i2c_data_buf[0] = RTC_SEC_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}

uint8_t RTC_getMins(uint8_t *i2c_data_buf)
{

	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];

}

uint8_t RTC_getHours(uint8_t *i2c_data_buf)
{

	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];

}

uint8_t RTC_getWeekday(uint8_t *i2c_data_buf)
{
	i2c_data_buf[0] = RTC_WEEKDAY_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}

uint8_t RTC_getDate(uint8_t *i2c_data_buf)
{
	i2c_data_buf[0] = RTC_DATE_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}

uint8_t RTC_getMonth(uint8_t *i2c_data_buf)
{
	i2c_data_buf[0] = RTC_MONTH_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}

uint8_t RTC_getYear(uint8_t *i2c_data_buf)
{
	i2c_data_buf[0] = RTC_YEAR_REG_ADDR;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, RTC_ADDR, i2c_data_buf, 1, HAL_MAX_DELAY);

	return i2c_data_buf[0];
}


void RTC_getTime(uint8_t *time_array, uint8_t *i2c_data_buf)
{
	time_array[0] = RTC_getSeconds(i2c_data_buf);
	time_array[1] = RTC_getMins(i2c_data_buf);
	time_array[2] = RTC_getHours(i2c_data_buf);
}

void RTC_getFullDate(uint8_t *date_array, uint8_t *i2c_data_buf)
{
	date_array[0] = RTC_getWeekday(i2c_data_buf);
	date_array[1] = RTC_getDate(i2c_data_buf);
	date_array[2] = RTC_getMonth(i2c_data_buf);
	date_array[3] = RTC_getYear(i2c_data_buf);
}

void conv_time_BCD(uint8_t *time_array)
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

void conv_date_BCD(uint8_t *date_array)
{

	uint8_t BCD_date = date_array[1];
	uint8_t BCD_month = date_array[2];
	uint8_t BCD_year = date_array[3];

	date_array[1] = ((BCD_date>>4) & 0b00000011); //date in tens
	date_array[2] = (BCD_date & 0b00001111); //date in ones
	date_array[3] = ((BCD_month>>4) & 0b00000001); //month in tens
	date_array[4] = (BCD_month & 0b00001111); //month in ones
	date_array[5] = ((BCD_year>>4) & 0b00001111); //year in tens
	date_array[6] = BCD_year & 0b00001111; //year in ones

}

void RTC_updateMins(uint8_t *i2c_data_buf, uint8_t tenmins, uint8_t onemins)
{
	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	i2c_data_buf[1] = (tenmins<<4 | onemins);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateHours(uint8_t *i2c_data_buf, uint8_t tenhours, uint8_t onehours)
{
	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	i2c_data_buf[1] = (tenhours<<4 | onehours);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateWeekday(uint8_t *i2c_data_buf, uint8_t weekday)
{
	i2c_data_buf[0] = RTC_WEEKDAY_REG_ADDR;
	i2c_data_buf[1] = weekday;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateDate(uint8_t *i2c_data_buf, uint8_t tendays, uint8_t onedays)
{
	i2c_data_buf[0] = RTC_DATE_REG_ADDR;
	i2c_data_buf[1] = (tendays<<4 | onedays);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateMonth(uint8_t *i2c_data_buf, uint8_t tenmonths, uint8_t onemonths)
{
	i2c_data_buf[0] = RTC_MONTH_REG_ADDR;
	i2c_data_buf[1] = (tenmonths<<4 | onemonths);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_updateYear(uint8_t *i2c_data_buf, uint8_t tenyears, uint8_t oneyears)
{
	i2c_data_buf[0] = RTC_YEAR_REG_ADDR;
	i2c_data_buf[1] = (tenyears<<4 | oneyears);
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}

void RTC_init(uint8_t *i2c_data_buf, uint8_t current_min_BCD, uint8_t current_hour_BCD, uint8_t current_weekday,
		uint8_t current_date_BCD, uint8_t current_month_BCD, uint8_t current_year_BCD)
{
	i2c_data_buf[0] = RTC_MIN_REG_ADDR;
	i2c_data_buf[1] = current_min_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_HOUR_REG_ADDR;
	i2c_data_buf[1] = current_hour_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_WEEKDAY_REG_ADDR;
	i2c_data_buf[1] = current_weekday;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_DATE_REG_ADDR;
	i2c_data_buf[1] = current_date_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_MONTH_REG_ADDR;
	i2c_data_buf[1] = current_month_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
	i2c_data_buf[0] = RTC_YEAR_REG_ADDR;
	i2c_data_buf[1] = current_year_BCD;
	HAL_I2C_Master_Transmit(&hi2c1, RTC_ADDR, i2c_data_buf, 2, HAL_MAX_DELAY);
}
