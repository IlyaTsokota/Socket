#include "chat.h"

void get_all_messages(char *user_id, char *last_msg_id)
{
    char *num_f = strdup("16");
    char *arr[] = {user_id, last_msg_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *messages = request_get_messages(json);
    free(json);
    
    FILE *fp = fopen("messages.json", "a");
    if (fp != NULL)
    {
        fputs(messages, fp);
        fclose(fp);
    }
    free(messages);
}

// #include "chat.h"

// void get_all_messages(char *user_id, char *last_msg_id)
// {
//     char *num_f = strdup("16");
//     char *arr[] = {user_id, last_msg_id, NULL};
//     char *json = write_to_json(num_f, arr);
//     free(num_f);
//     char *messages = request_get_messages(json);
//     free(json);
//     char *str_from_file = mx_file_to_str("messages.json");
//     FILE *fp = fopen("messages.json", "w");
//     if (str_from_file == NULL)
//     {
//         if (fp != NULL)
//         {
//             fputs(messages, fp);
//             fclose(fp);
//         }
//     }
//     else
//     {
    
//         size_t size_str_in_file = strlen(str_from_file) - 2;
//         size_t size_str_from_db = strlen(messages);
//         size_t i = 0;
//         size_t full_size = (size_str_in_file + size_str_from_db - 14);
//         g_print("%lu\n", (size_str_in_file + size_str_from_db - 14));
//         char *new_str = mx_strnew(full_size);
//         for (size_t j = 0; j < size_str_in_file; j++)
//         {
//             new_str[i++] = str_from_file[j];
//         }
//         int k = 0;
//         while(i < full_size)
//         {
//             new_str[i++] = messages[k++];
//         }
//         g_print("%lu\n", strlen(new_str));
       
//         // if (fp != NULL)
//         // {
//         //     remove("messages.json");
//         //     fputs(new_str, fp);
//         //     fclose(fp);
//         // }
//         // free(new_str);
//     }
//     if(str_from_file != NULL){
//           free(str_from_file);
//     }
//     // free(messages);
// }
