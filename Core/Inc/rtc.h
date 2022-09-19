/*
 * rtc.h
 *
 *  Created on: Sep 17, 2022
 *      Author: usman
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"

uint8_t RTC_getSeconds();
uint8_t RTC_getMins();
uint8_t RTC_getHours();
void RTC_getTime(uint8_t *time_array);
void RTC_updateMins(uint8_t tenmins, uint8_t onemins);
void RTC_updateHours(uint8_t tenhours, uint8_t onehours);
void RTC_init(uint8_t current_min_BCD, uint8_t current_hour_BCD);
void conv_BCD(uint8_t *time_array);

#define RTC_ADDR (0x51<<1)
#define RTC_SEC_REG_ADDR (0x02)
#define RTC_MIN_REG_ADDR (0x03)
#define RTC_HOUR_REG_ADDR (0x04)
#endif /* INC_RTC_H_ */
