#include "chat.h"

void free_user_s(user_t *user)
{
    if (user != NULL)
    {
        free(user->u_name);
        free(user->u_surname);
        free(user->u_status);
        free(user->u_avatar);
     
        free(user);
        user = NULL;
    }
}
