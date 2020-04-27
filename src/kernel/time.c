/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#include <time.h>
#include <aamOS/kernel.h>
#include <asm/io.h>

#define CMOS_READ(reg) ({ \
outb(0x70,0x80|reg); \
inb(0x71); \
})

#define CMOS_SET(reg, val) ({ \
	outb(0x70,0x80|reg); \
	outb(0x71,val); \
})

#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)

#define MINUTE 60
#define HOUR (60*MINUTE)
#define DAY (24*HOUR)
#define YEAR (365*DAY)

static int month[12] = { 0,
DAY * (31),
DAY * (31 + 29),
DAY * (31 + 29 + 31),
DAY * (31 + 29 + 31 + 30),
DAY * (31 + 29 + 31 + 30 + 31),
DAY * (31 + 29 + 31 + 30 + 31 + 30),
DAY * (31 + 29 + 31 + 30 + 31 + 30 + 31),
DAY * (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31),
DAY * (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30),
DAY * (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31),
DAY * (31 + 29 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30) };

static char* months[12] = {
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
};

char *parse_mon(int md) {
	return months[md];
}

time_t mktime(struct tm *tm) {
	long res;
	int year;

	year = tm->tm_year - 1970;
	/* magic offsets (y+1) needed to get leapyears right.*/
	res = YEAR * year + DAY * ((year + 1) / 4);
	res += month[tm->tm_mon];
	/* and (y+2) here. If it wasn't a leap-year, we have to adjust */
	if (tm->tm_mon > 1 && ((year + 2) % 4))
		res -= DAY;
	res += DAY * (tm->tm_mday - 1);
	res += HOUR * tm->tm_hour;
	res += MINUTE * tm->tm_min;
	res += tm->tm_sec;
	return res;
}

struct tm* get_time() {
	static struct tm time;
	int c = CMOS_READ(0x32);
	BCD_TO_BIN(c);
	time.tm_year = CMOS_READ(0x09);
	BCD_TO_BIN(time.tm_year);
	time.tm_year += c*100;
	time.tm_mon = CMOS_READ(0x08)-1;
	BCD_TO_BIN(time.tm_mon);
	time.tm_mday = CMOS_READ(0x07);
	BCD_TO_BIN(time.tm_mday);
	time.tm_wday = CMOS_READ(0x06);
	BCD_TO_BIN(time.tm_wday);
	time.tm_hour = CMOS_READ(0x04);
	BCD_TO_BIN(time.tm_hour);
	time.tm_min = CMOS_READ(0x02);
	BCD_TO_BIN(time.tm_min);
	time.tm_sec = CMOS_READ(0x00);
	BCD_TO_BIN(time.tm_sec);
	return &time;
}

void time_init() {
	startup_time = mktime(get_time());
}

static char *weekdays[7] = { "Sunday", "Monday", "Tuesday",
		"Wednesday", "Thursday", "Friday", "Saturday" };

char* parse_wd(int wd) {
	return weekdays[wd-1];
}
