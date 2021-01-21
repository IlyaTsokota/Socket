#include "server.h"

void free_message_s(message_t *message)
{
    if (message != NULL)
    {
        free(message->ch_id);
        free(message->ms_id);
        free(message->u_id);
        free(message->u_name);
        free(message->u_surname);
        free(message->ms_text);
        free(message->ms_datetime);
        free(message->ms_isedited);
        free(message->ms_isforwarded);
        free(message->ms_ismedia);
        free(message->ms_isreply);
        free(message->ms_isseen);
        free(message);
        message = NULL;
    }
}
