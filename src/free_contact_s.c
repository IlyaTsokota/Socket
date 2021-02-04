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
