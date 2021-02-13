#include "server.h"

char *set_date()
{
    char *date;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); //*gmtime(&t);
    //char *answer = (char *)malloc(sizeof(char) * 60);
    char *year = mx_strnew(4);
    char *month = mx_strnew(2);
    char *day = mx_strnew(2);
    char *hour = mx_strnew(2);
    char *min = mx_strnew(2);
    char *sec = mx_strnew(2);
    itobase10(year, tm.tm_year + 1900);
    itobase10(month, tm.tm_mon + 1);
    itobase10(day, tm.tm_mday);
    itobase10(hour, tm.tm_hour);
    itobase10(min, tm.tm_min);
    itobase10(sec, tm.tm_sec);
    const char *request_parts[] = {year, "-", month, "-", day, " ", hour, ":", min, ":", sec, NULL};
    date = strjoins_arr(request_parts);
    free(year); //IR
    free(month); //IR
    free(day); //IR
    free(hour); //IR
    free(min); //IR
    free(sec); //IR
    
    return date;
}