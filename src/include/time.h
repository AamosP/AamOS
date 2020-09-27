/*******************************************************************************
 * Copyright (c) 2020 Aamos Pernu.
 *******************************************************************************/
#ifndef _TIME_H
#define _TIME_H

#ifndef _TIME_T
#define _TIME_T
typedef long time_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#define CLOCKS_PER_SEC 100

typedef long clock_t;

extern time_t startup_time;

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

char *parse_mon(int md);
int get_wd(int day, int month, int year);
time_t mktime(struct tm *tp);
void time_init(void);
struct tm* get_time();
char* parse_wd(int wd);

#endif
