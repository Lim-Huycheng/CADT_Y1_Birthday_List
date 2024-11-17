#include <stdio.h>
#include <time.h>

int main()
{
    time_t c_time;

    c_time = time(NULL);

    struct tm nowTime;

    nowTime = *localtime(&c_time);

    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", nowTime.tm_year + 1900, nowTime.tm_mon + 1, nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);


    return 0;
}