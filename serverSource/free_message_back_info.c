#include "server.h"

void free_message_back_info_s(message_back_info_t *user)
{
    if (user != NULL)
    {
        free(user->ms_datetime);
        free(user->ms_id);
        free(user);
        user = NULL;
    }
}
