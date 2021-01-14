#include "server.h"

char* int_to_str(int n) 
{
    if (n != 0) {
        char *str;
        int j = 0;
        int i = 0;
        long val = n;
        if (val < 0)
            val = -val;
        while (val != 0) {
            str[i++] = val % 10 + '0';
            val /= 10;
        }
        if (n < 0)
            str[i++] = '-';
       return str;
    } else {
       return "0";
    }
}