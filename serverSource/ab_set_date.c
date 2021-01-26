#include "server.h"

char *set_date()
{
    char *date;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); //*gmtime(&t);
    //char *answer = (char *)malloc(sizeof(char) * 60);
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