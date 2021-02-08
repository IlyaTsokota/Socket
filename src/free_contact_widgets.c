#include "chat.h"
void free_contact_widgets(contacts_widget_s **contacts)
{
    if (contacts != NULL && !contacts_t.was_free)
    {

        ////puts("To e pizda");
        for (size_t i = 0; contacts[i]; i++)
        {
            gtk_widget_destroy(contacts[i]->contact_name_lable);
            gtk_widget_destroy(contacts[i]->contact_status_lable);
            gtk_widget_destroy(contacts[i]->contact_name_container);
            gtk_widget_destroy(contacts[i]->contact_status);
            gtk_widget_destroy(contacts[i]->img_contact);
            gtk_widget_destroy(contacts[i]->grid_list_contact_img);
            gtk_widget_destroy(contacts[i]->contact_info);
            gtk_widget_destroy(contacts[i]->contact_container);
            gtk_widget_destroy(contacts[i]->event_box_contact);
            free(contacts[i]);
        }
        free(contacts);
        ////puts("Tochno pizda");
        contacts = NULL;
        contacts_t.was_free = true;
    }
}
