#include "server.h"

char *get_filename_extension(char *filename){
 
    int index = 0;
    for (int i = strlen(filename) - 1; i >= 0; i--)
    {
        if(filename[i] == '.'){
            index = i;
            break;
        }
    }
   char *result = strdup(&filename[index]);
   return result;
}
