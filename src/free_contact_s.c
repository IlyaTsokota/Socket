#include "chat.h"

void free_contacts_s(contact_t **contacts)
{
    if (contacts != NULL)
    {
        for (size_t i = 0; contacts[i]; i++)
        {
            free(contacts[i]->c_id);
            free(contacts[i]->u_name);
            free(contacts[i]->u_avatar);
            free(contacts[i]->u_status);
            free(contacts[i]);
        }
        free(contacts);
        contacts = NULL;
    }
}
