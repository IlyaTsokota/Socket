#include "chat.h"

void str_to_file(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "w+");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}