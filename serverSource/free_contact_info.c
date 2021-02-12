#include "server.h"

void free_contact_info_s(contact_info_t *contact)
{
    if (contact != NULL)
    {
        free(contact->u_login);
        free(contact->u_name);
        free(contact->u_status);
        free(contact->u_avatar);
     
        free(contact);
        contact = NULL;
    }
}
