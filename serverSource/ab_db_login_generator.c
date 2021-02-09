#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define BUF_SIZE (500)



char *get_file(FILE *file7, int line_no, char *filename)
{
    file7 = fopen(filename, "r");
    
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
    char *password = (char *)malloc(101 * sizeof(char));
    for (i = 0; i < count; i++)
    {puts("start");
        int random1 = rand() % 500;
        int random2 = rand() % 500;
        int random3 = rand() % 500;
        int random4 = rand() % 500;

        char *filename1 = strdup("4"); 
        char *filename2 = strdup("5"); 
        char *filename3 = strdup("6"); 
        char *filename4 = strdup("7"); 

        char *line1 = get_file(stdin, random1, filename1);
        char *line2 = get_file(stdin, random2, filename2);
        char *line3 = get_file(stdin, random3, filename3);
        char *line4 = get_file(stdin, random4, filename4);
        free(filename1);
        free(filename2);
        free(filename3);
        free(filename4);
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
        free(line1);
        free(line2);
        free(line3);
        free(line4);

        puts("start");
    }
    for (i = 0; password[i] != '\0'; i++)
    {
        if (password[i] == '\n')
        {
            password[i] = '-';
        }
    }
    puts("start1");
    length = strlen(password);
    password[length - 1] = '\0';
    return password;
}
