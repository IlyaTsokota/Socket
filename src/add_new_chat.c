#include "chat.h"

void add_new_chat(GtkWidget *button, GtkWidget *widgets)
{
    g_mutex_lock(&main_form.mutex);
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
        char *response = request_on_server(data.socket_desc, json);
        free(json);
        chat_t **chats = request_get_chats(response);
        free(response);
        
        create_one_chat(chats_f.size, chats[0]);
        free_chats(chats);

        gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[chats_f.size - 1]->event_box_contact, 0, (chats_f.size - 1) , 1, 1);
        gtk_widget_show_all(main_form.left_content[0]);
    }
    g_mutex_unlock(&main_form.mutex);
}
