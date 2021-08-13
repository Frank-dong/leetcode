#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	time_t	t;
	struct	tm time_info;
	int		sec = 0;
	int		min = 0;
	int		hour = 0;
	int		day = 0;
	int		month = 0;
	int		year = 0;

	sscanf(argv[1], "%d-%d-%d %02d:%02d:%02d", &year, &month, &day, &hour, &min, &sec);
	time_info.tm_year = year-1900;
	time_info.tm_mon = month - 1;
	time_info.tm_mday = day;
	time_info.tm_hour = hour;
	time_info.tm_min = min;
	time_info.tm_sec = sec;
	time_info.tm_isdst = 0;

	t = mktime(&time_info);

	printf("%d, %d, %d, %d, %d, %d\r\n", year, month, day, hour, min, sec);
	printf("%lld\r\n", t);
	t += (5*24*3600);
	printf("%lld\r\n", t);

	struct tm* new_time = localtime(&t);
	printf("%d-%d-%d %d:%d:%d\r\n", 
			new_time->tm_year + 1900, new_time->tm_mon + 1, new_time->tm_mday, 
			new_time->tm_hour, new_time->tm_min, new_time->tm_sec);

	return 0;
}
