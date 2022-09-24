/*
 * rtc.h
 *
 *  Created on: Sep 17, 2022
 *      Author: usman
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

struct RTC_MOD
{

	uint8_t RTC_I2C_BUF[5];
	uint8_t time_array[6];
	uint8_t date_array[7];
};




uint8_t RTC_getSeconds(uint8_t *i2c_data_buf);
uint8_t RTC_getMins(uint8_t *i2c_data_buf);
uint8_t RTC_getHours(uint8_t *i2c_data_buf);
uint8_t RTC_getWeekday(uint8_t *i2c_data_buf);
uint8_t RTC_getDate(uint8_t *i2c_data_buf);
uint8_t RTC_getMonth(uint8_t *i2c_data_buf);
uint8_t RTC_getYear(uint8_t *i2c_data_buf);



void RTC_getTime(uint8_t *time_array, uint8_t *i2c_data_buf);
void RTC_getFullDate(uint8_t *date_array, uint8_t *i2c_data_buf);

void conv_time_BCD(uint8_t *time_array);
void conv_date_BCD(uint8_t *date_array);

void RTC_updateMins(uint8_t *i2c_data_buf, uint8_t tenmins, uint8_t onemins);
void RTC_updateHours(uint8_t *i2c_data_buf, uint8_t tenhours, uint8_t onehours);
void RTC_updateWeekday(uint8_t *i2c_data_buf, uint8_t weekday);
void RTC_updateDate(uint8_t *i2c_data_buf, uint8_t tendays, uint8_t onedays);
void RTC_updateMonth(uint8_t *i2c_data_buf, uint8_t tenmonths, uint8_t onemonths);
void RTC_updateYear(uint8_t *i2c_data_buf, uint8_t tenyears, uint8_t oneyears);
void RTC_init(uint8_t *i2c_data_buf, uint8_t current_min_BCD, uint8_t current_hour_BCD, uint8_t current_weekday,
		uint8_t current_date_BCD, uint8_t current_month_BCD, uint8_t current_year_BCD);

#define RTC_ADDR (0x51<<1)
#define RTC_SEC_REG_ADDR (0x02)
#define RTC_MIN_REG_ADDR (0x03)
#define RTC_HOUR_REG_ADDR (0x04)
#define RTC_WEEKDAY_REG_ADDR (0x06)
#define RTC_DATE_REG_ADDR (0x05)
#define RTC_MONTH_REG_ADDR (0x07)
#define RTC_YEAR_REG_ADDR (0x08)

#endif /* INC_RTC_H_ */
