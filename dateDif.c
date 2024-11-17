#include <stdio.h>
#include <time.h>
// Calculate the number of day difference.
// Compare current date (day/month) to birthday (day/month)
// if the day differnce is within 30, show it


int dayTab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int dayOfYear(int year, int month, int day)
{
    int i, leap;
    leap = ( year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
    for (i = 1; i < month; i++)
        day += dayTab[leap][i];
    return day;
}

int main()
{
    time_t c_time;

    c_time = time(NULL);

    struct tm nowTime;

    nowTime = *localtime(&c_time);

    int dateDif, someDay;

    printf("Current month: %d\n", nowTime.tm_mon + 1);
    printf("Current day: %d\n", nowTime.tm_mday);
    printf("Current year: %d\n", nowTime.tm_year + 1900);
    printf("24 year ago: %d\n", nowTime.tm_year + 1900 - 24);
    printf("8  year ago: %d\n", nowTime.tm_year + 1900 - 24 + 8);

    printf("day of the year: %d\n", nowTime.tm_yday + 1);

    printf("year of the day calculated by function: %d\n", dayOfYear(nowTime.tm_year + 1900, nowTime.tm_mon + 1, nowTime.tm_mday));

    someDay = dayOfYear(2008, 7, 10);
    dateDif = someDay - (nowTime.tm_yday + 1);

    printf("dateDif = %d\n", dateDif);
    
    return 0;
}