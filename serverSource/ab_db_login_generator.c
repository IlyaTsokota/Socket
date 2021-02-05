#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define BUF_SIZE (500)

char *get_file4(FILE *file4, int line_no)
{
    file4 = fopen("4", "r");
    char buf[BUF_SIZE];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char *line1 = malloc(BUF_SIZE);
    int in_line = line_no == 1;
    size_t bytes_read;
    if (line_no < 1)
        return NULL;
    if (!line1)
        return NULL;
    while (line_no && (bytes_read = fread(buf, 1, BUF_SIZE, file4)) > 0)
    {
        int i;
        for (i = 0; i < (int)bytes_read; i++)
        {
            if (in_line)
            {
                if (curr_ofs >= curr_alloc)
                {
                    curr_alloc <<= 1;
                    line1 = realloc(line1, curr_alloc);
                    if (!line1)
                        return NULL;
                }
                line1[curr_ofs++] = buf[i];
            }
            if (buf[i] == '\n')
            {
                line_no--;

                if (line_no == 1)
                    in_line = 1;

                if (line_no == 0)
                    break;
            }
        }
    }
    if (line_no != 0)
    {
        free(line1);
        return NULL;
    }
    line1 = realloc(line1, curr_ofs + 1);
    if (!line1)
        return NULL;
    line1[curr_ofs] = '\0';
    return line1;
    fclose(file4);
}

char *get_file5(FILE *file5, int line_no)
{
    file5 = fopen("5", "r");
    char buf[BUF_SIZE];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char *line2 = malloc(BUF_SIZE);
    int in_line = line_no == 1;
    size_t bytes_read;
    if (line_no < 1)
        return NULL;
    if (!line2)
        return NULL;
    while (line_no && (bytes_read = fread(buf, 1, BUF_SIZE, file5)) > 0)
    {
        int i;
        for (i = 0; i < (int)bytes_read; i++)
        {
            if (in_line)
            {
                if (curr_ofs >= curr_alloc)
                {
                    curr_alloc <<= 1;
                    line2 = realloc(line2, curr_alloc);
                    if (!line2)
                        return NULL;
                }
                line2[curr_ofs++] = buf[i];
            }
            if (buf[i] == '\n')
            {
                line_no--;

                if (line_no == 1)
                    in_line = 1;

                if (line_no == 0)
                    break;
            }
        }
    }
    if (line_no != 0)
    {
        free(line2);
        return NULL;
    }
    line2 = realloc(line2, curr_ofs + 1);
    if (!line2)
        return NULL;
    line2[curr_ofs] = '\0';
    return line2;
    fclose(file5);
}

char *get_file6(FILE *file6, int line_no)
{
    file6 = fopen("6", "r");
    char buf[BUF_SIZE];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char *line3 = malloc(BUF_SIZE);
    int in_line = line_no == 1;
    size_t bytes_read;
    if (line_no < 1)
        return NULL;
    if (!line3)
        return NULL;
    while (line_no && (bytes_read = fread(buf, 1, BUF_SIZE, file6)) > 0)
    {
        int i;
        for (i = 0; i < (int)bytes_read; i++)
        {
            if (in_line)
            {
                if (curr_ofs >= curr_alloc)
                {
                    curr_alloc <<= 1;
                    line3 = realloc(line3, curr_alloc);
                    if (!line3)
                        return NULL;
                }
                line3[curr_ofs++] = buf[i];
            }
            if (buf[i] == '\n')
            {
                line_no--;

                if (line_no == 1)
                    in_line = 1;

                if (line_no == 0)
                    break;
            }
        }
    }
    if (line_no != 0)
    {
        free(line3);
        return NULL;
    }
    line3 = realloc(line3, curr_ofs + 1);
    if (!line3)
        return NULL;
    line3[curr_ofs] = '\0';
    return line3;
    fclose(file6);
}

char *get_file7(FILE *file7, int line_no)
{
    file7 = fopen("7", "r");
    char buf[BUF_SIZE];
    size_t curr_alloc = BUF_SIZE, curr_ofs = 0;
    char *line4 = malloc(BUF_SIZE);
    int in_line = line_no == 1;
    size_t bytes_read;
    if (line_no < 1)
        return NULL;
    if (!line4)
        return NULL;
    while (line_no && (bytes_read = fread(buf, 1, BUF_SIZE, file7)) > 0)
    {
        int i;
        for (i = 0; i < (int)bytes_read; i++)
        {
            if (in_line)
            {
                if (curr_ofs >= curr_alloc)
                {
                    curr_alloc <<= 1;
                    line4 = realloc(line4, curr_alloc);
                    if (!line4)
                        return NULL;
                }
                line4[curr_ofs++] = buf[i];
            }
            if (buf[i] == '\n')
            {
                line_no--;

                if (line_no == 1)
                    in_line = 1;

                if (line_no == 0)
                    break;
            }
        }
    }
    if (line_no != 0)
    {
        free(line4);
        return NULL;
    }
    line4 = realloc(line4, curr_ofs + 1);
    if (!line4)
        return NULL;
    line4[curr_ofs] = '\0';
    return line4;
    fclose(file7);
}

char *pass_gen()
{
    srand(time(NULL));
    int count = 2;
    int i;
    int n = 1;
    int length;
    char *password;
    password = (char *)malloc((100 + 1) * sizeof(char));
    for (i = 0; i < count; i++)
    {
        int random1 = rand() % 500;
        int random2 = rand() % 500;
        int random3 = rand() % 500;
        int random4 = rand() % 500;
        char *line1 = get_file4(stdin, random1);
        char *line2 = get_file5(stdin, random2);
        char *line3 = get_file6(stdin, random3);
        char *line4 = get_file7(stdin, random4);
        int randfile = rand() % 4;
        switch (randfile)
        {
        case 0:
            strcat(password, line1);
            n++;
            break;

        case 1:
            strcat(password, line2);
            n++;
            break;

        case 2:
            strcat(password, line3);
            n++;
            break;

        case 3:
            strcat(password, line4);
            n++;
            break;
        }
    }
    for (i = 0; password[i] != '\0'; i++)
    {
        if (password[i] == '\n')
        {
            password[i] = '-';
        }
    }
    length = strlen(password);
    password[length - 1] = '\0';
    return password;
}
