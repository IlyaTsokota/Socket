#include "chat.h"

void str_to_file(const char *filepath, const char *data)
{   
    remove(filepath);
    FILE *fp = fopen(filepath, "wb");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}