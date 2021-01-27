#include "chat.h"

char *strjoins(const char *s1, const char *s2)
{
    char *result = mx_strnew(strlen(s1) + strlen(s2));
    //puts(int_to_str((int)strlen(s2)));

    if (result)
    {
        strcpy(result, s1);
        strcpy(result + strlen(s1), s2);
        //strcat(result, s2);
    }
    //result[strlen(s1) + strlen(s2)] = '\0';
    return result;
}

static char *set_date()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
puts(".................................");
    char *year = int_to_str((tm.tm_year + 1900));
    puts(year);
    char *month = int_to_str((tm.tm_mon + 1));
    puts(month);
    char *day = int_to_str(tm.tm_mday);
    puts(day);
    char *hour = int_to_str(tm.tm_hour);
    puts(hour);
    char *min = int_to_str(tm.tm_min);
    puts(min);
    // char *sec = int_to_str(tm.tm_sec);
    // puts(sec);
puts(".................................");
    char *date = strjoins(year, "-");
    date = strjoins(date, month);
    date = strjoins(date, "-");
    date = strjoins(date, day);
    date = strjoins(date, " ");
    date = strjoins(date, hour);
    date = strjoins(date, ":");
    date = strjoins(date, min);
    date = strjoins(date, ":00");
    // date = strjoins(date, sec);
    free(year);
    free(month);
    free(day);
    free(hour);
    free(min);
    // free(sec);
    //puts(date);
    return date;
}

static bool is_online2(double difference)
{
    if (difference < 180)
    {
        return true;
    }
    return false;
}

bool is_online(char *last_seen)
{
    struct tm tm1, tm2;
    char* date = set_date();
    puts(date);
    strptime(date, "%Y-%m-%d %H:%M:%S", &tm1);
    free(date);
    puts(last_seen);
    strptime(last_seen, "%Y-%m-%d %H:%M:%S", &tm2);
    if (mktime(&tm1) == -1 || mktime(&tm2) == -1) {
        g_print("MKTIME ERROR!\n");
    }
    double diff = difftime(mktime(&tm1), mktime(&tm2));
    g_print("%f -- diff\n", diff);
    return is_online2(diff);
}
