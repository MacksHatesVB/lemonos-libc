#pragma once

#include <stdint.h>

enum {
	CMOS_RTC_SECONDS = 0,
	CMOS_RTC_SECOND_ALARM,
	CMOS_RTC_MINUTES,
	CMOS_RTC_MINUTE_ALARM,
	CMOS_RTC_HOURS,
	CMOS_RTC_HOUR_ALARM,
	CMOS_RTC_DAY,
	CMOS_RTC_WEEK,
	CMOS_RTC_MONTH,
	CMOS_RTC_YEAR,
	CMOS_STATUS_A,
	CMOS_STATUS_B,
	CMOS_STATUS_C,
	CMOS_STATUS_D,
	CMOS_DIAGNOSTIC,
	CMOS_FLOPPY = 0x10,
	CMOS_CENTURY = 0x32, // every other register is seemingly bios specific
};

enum {
	CMOS_PORT_ADDR = 0x70,
	CMOS_PORT_DATA = 0x71,
};

int cmos_updating();
uint8_t cmos_read_register(uint16_t reg);
void cmos_write_register(uint16_t reg, uint8_t value);
