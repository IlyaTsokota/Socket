#include "chat.h"

message_arr *get_messages_from_file(char *filename)
{
    char *str = mx_file_to_str(filename);
    message_arr *messages = messages_to_json(str);
    free(str);
    if (messages == NULL) {
        return NULL;
    }
    return messages;
}
