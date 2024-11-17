#include <stdio.h>
#include <time.h>

int main()
{
    time_t c_time;

    c_time = time(NULL);

    struct tm nowTime;

    nowTime = *localtime(&c_time);

    printf("Current month: %d\n", nowTime.tm_mon + 1);


    return 0;
}