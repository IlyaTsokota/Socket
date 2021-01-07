#include "server.h"

char *itobase10(char *buf, int value)
{
    sprintf(buf, "%d", value);
    return buf;
}
