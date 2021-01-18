#include "server.h"

void free_contact_s(contact_t *contact){
 if (contact != NULL)
    {
        free(contact->c_id);
        free(contact->u_name);
        free(contact->u_surname);
        free(contact->u_avatar);
        free(contact->u_status);
        free(contact->u_lastSeen);
        free(contact);
        contact = NULL;
    }
}
