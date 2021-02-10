#include "chat.h"

void add_new_chat(GtkWidget *button, GtkWidget *widgets)
{
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(widgets));

    if (strlen(name) <= 0)
    {
        // gtk_label_set_text(GTK_LABEL(widgets[1]), "The field can't be empty");
        valid_entry_border_color(&widgets);
    }
    else
    {
        char *num_f = strdup("6");
        char *arr[] = {data.user_id, name, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        request_to_server(json);
        add_one_chat_after_request(data.user_id);
        gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[chats_f.size - 1]->event_box_contact, 0, chats_f.size - 1, 1, 1);
    }
}
