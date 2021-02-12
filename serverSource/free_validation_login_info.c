#include "server.h"

void free_validation_login_info_s(login_pin_info_t *message)
{
    if (message != NULL)
    {
        free(message->u_login);
        free(message->u_avatar);
        free(message->u_id);

        free(message);
        message = NULL;
    }
}
