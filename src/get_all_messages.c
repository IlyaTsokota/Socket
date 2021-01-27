#include "chat.h"

void get_all_messages(char *user_id, char *last_msg_id)
{
    char *num_f = strdup("16");
    char *arr[] = {user_id, last_msg_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *messages = request_get_messages(json);
    free(json);
    //puts(messages);
    FILE *fp = fopen("messages.json", "a");
    if (fp != NULL)
    {
        fputs(messages, fp);
        fclose(fp);
    }
    free(messages);
}
