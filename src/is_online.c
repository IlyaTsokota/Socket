#include "chat.h"

char *strjoins(const char *s1, const char *s2)
{
    char *result = mx_strnew(strlen(s1) + strlen(s2));

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
}

static char *set_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char *year = int_to_str((tm.tm_year + 1900));
    char *month = int_to_str((tm.tm_mon + 1));
    char *day = int_to_str(tm.tm_mday);
    char *hour = int_to_str(tm.tm_hour);
    char *min = int_to_str(tm.tm_min);
    char *sec = int_to_str(tm.tm_sec);

    char *date = strjoins(year, "-");
    date = strjoins(date, month);
    date = strjoins(date, "-");
    date = strjoins(date, day);
    date = strjoins(date, " ");
    date = strjoins(date, hour);
    date = strjoins(date, ":");
    date = strjoins(date, min);
    date = strjoins(date, ":");
    date = strjoins(date, sec);
    free(year);
    free(month);
    free(day);
    free(hour);
    free(min);
    free(sec);
    return date;
}


static bool is_online2(double difference)
{
   if (difference<180)
    return true;
    else;
    return false;
}

bool is_online(char *last_seen)
{
    struct tm tm1, tm2;
    strptime(set_date(), "%Y-%m-%d %H:%M:%S", &tm1);
    strptime(last_seen, "%Y-%m-%d %H:%M:%S", &tm2);
    double diff = difftime(mktime(&tm1), mktime(&tm2));
    return is_online2(diff);      
}

