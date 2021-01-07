#include "server.h"

char *set_date()
{
    char *date;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *answer = (char *)malloc(sizeof(char) * 60);
    char *year = (char *)malloc(sizeof(char) * 4);
    char *month = (char *)malloc(sizeof(char) * 2);
    char *day = (char *)malloc(sizeof(char) * 2);
    char *hour = (char *)malloc(sizeof(char) * 2);
    char *min = (char *)malloc(sizeof(char) * 2);
    char *sec = (char *)malloc(sizeof(char) * 2);
    itobase10(year, tm.tm_year + 1900);
    itobase10(month, tm.tm_mon + 1);
    itobase10(day, tm.tm_mday);
    itobase10(hour, tm.tm_hour);
    itobase10(min, tm.tm_min);
    itobase10(sec, tm.tm_sec);
    date = strjoins(year, "-");
    date = strjoins(date, month);
    date = strjoins(date, "-");
    date = strjoins(date, day);
    date = strjoins(date, " ");
    date = strjoins(date, hour);
    date = strjoins(date, ":");
    date = strjoins(date, min);
    date = strjoins(date, ":");
    date = strjoins(date, sec);

    return date;
}