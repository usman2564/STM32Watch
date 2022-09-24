/*
 * statemachine.c
 *
 *  Created on: Sep 23, 2022
 *      Author: usman
 */

#include "statemachine.h"

void Watch_init(struct Watch *Watch, uint8_t minutes_BCD, uint8_t hours_BCD, uint8_t weekday_BCD, uint8_t date_BCD, uint8_t month_BCD, uint8_t year_BCD)
{

	HAL_TIM_Base_Start(&htim21);
	OLED_init(&(Watch->OLED));
	RTC_init(Watch->RTC_MOD.RTC_I2C_BUF, minutes_BCD, hours_BCD, weekday_BCD, date_BCD, month_BCD, year_BCD);


	Watch->WatchState = Get_Time;

}

void Watch_Get_Time_State(struct Watch *Watch)
{

	RTC_getTime(&(Watch->RTC_MOD.time_array), &(Watch->RTC_MOD.RTC_I2C_BUF));
	conv_time_BCD(&(Watch->RTC_MOD.time_array[0]));

	Watch->WatchState = Display_Time;

}

void Watch_Display_Time_State(struct Watch *Watch)
{

	sprintf(Watch->OLED.string_buffer, "%d%d:%d%d:%d%d", Watch->RTC_MOD.time_array[4] , Watch->RTC_MOD.time_array[5], Watch->RTC_MOD.time_array[2],
			Watch->RTC_MOD.time_array[3], Watch->RTC_MOD.time_array[0], Watch->RTC_MOD.time_array[1]);
	OLED_drawString(Watch->OLED.string_buffer, 16, 35, &(Watch->OLED.OLED_SETCOLUMN[0]), &(Watch->OLED.OLED_SETROW[0]));

	Watch->WatchState = Get_Date;

}

void Watch_Get_Date_State(struct Watch *Watch)
{

	RTC_getFullDate(Watch->RTC_MOD.date_array, Watch->RTC_MOD.RTC_I2C_BUF);
	conv_date_BCD(Watch->RTC_MOD.date_array);

	Watch->WatchState = Display_Date;

}

void Watch_Display_Date_State(struct Watch *Watch)
{

	if(Watch->RTC_MOD.date_array[0] == 0)
		sprintf(Watch->OLED.string_buffer, "SUN;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else if(Watch->RTC_MOD.date_array[0] == 1)
		sprintf(Watch->OLED.string_buffer, "MON;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else if(Watch->RTC_MOD.date_array[0] == 2)
		sprintf(Watch->OLED.string_buffer, "TUE;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else if(Watch->RTC_MOD.date_array[0] == 3)
		sprintf(Watch->OLED.string_buffer, "WED;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else if(Watch->RTC_MOD.date_array[0] == 4)
		sprintf(Watch->OLED.string_buffer, "THU;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else if(Watch->RTC_MOD.date_array[0] == 5)
		sprintf(Watch->OLED.string_buffer, "FRI;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	else
		sprintf(Watch->OLED.string_buffer, "SAT;;;%d%d", Watch->RTC_MOD.date_array[1] , Watch->RTC_MOD.date_array[2]);
	OLED_drawString(Watch->OLED.string_buffer, 16, 5, &(Watch->OLED.OLED_SETCOLUMN[0]), &(Watch->OLED.OLED_SETROW[0]));

	Watch->WatchState = Get_Time;

}

