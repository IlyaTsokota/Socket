#include "server.h"

void free_validation_login_info2_s(login_pin_info_t2 *message)
{
    if (message != NULL)
    {
        free(message->u_login);
        free(message->u_avatar);
        free(message->u_id);
        free(message->u_isBottommed);

        free(message);
        message = NULL;
    }
}
