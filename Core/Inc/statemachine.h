/*
 * statemachine.h
 *
 *  Created on: Sep 23, 2022
 *      Author: usman
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_

#include "main.h"
#include "oled.h"
#include "rtc.h"
#include "tim.h"


typedef enum WatchStates {
	Get_Time,
	Display_Time,
	Get_Date,
	Display_Date,
} WatchState;

struct Watch
{

	enum WatchStates WatchState;
	struct OLED OLED;
	struct RTC_MOD RTC_MOD;

};


void Watch_init(struct Watch *Watch, uint8_t minutes_BCD, uint8_t hours_BCD, uint8_t weekday_BCD, uint8_t date_BCD, uint8_t month_BCD, uint8_t year_BCD);
void Watch_Display_Time_State(struct Watch *Watch);

#endif /* INC_STATEMACHINE_H_ */
