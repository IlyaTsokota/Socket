#include "chat.h"

void get_all_messages(char *user_id, char *last_msg_id)
{
    char *num_f = strdup("16");
    char *arr[] = {user_id, last_msg_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *messages = request_get_messages(json);
    json_object *jobj;
    jobj = json_tokener_parse(messages);
    if (jobj == NULL) { return;}
    free(jobj);
    free(json);

    char *str_from_file = mx_file_to_str("messages.json");
    
    FILE *fp;
    if (str_from_file == NULL)
    {
        fp = fopen("messages.json", "w");
        if (fp != NULL)
        {
            fputs(messages, fp);
            fclose(fp);
        }
    }
    else
    {
        remove("messages.json");
        fp = fopen("messages.json", "w");

        size_t size_str_in_file = strlen(str_from_file) - 3;
        size_t size_str_from_db = strlen(messages);
        size_t full_size = size_str_in_file + size_str_from_db - 14;

        str_from_file = realloc(str_from_file, full_size + 2);
        str_from_file[size_str_in_file++] = ',';
        strcpy(&str_from_file[size_str_in_file], &messages[14]);
        
        if (fp != NULL)
        {
            
            fputs(str_from_file, fp);
            fclose(fp);
        }
        
    }
    if(str_from_file != NULL){
          free(str_from_file);
    }
    free(messages);
}
