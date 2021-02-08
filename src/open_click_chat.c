#include "chat.h"

gboolean open_click_chat(GtkWidget *widget, GdkEventButton *event)
{
    char *id = (char *)gtk_widget_get_name(widget);
    if (strcmp(id, chats_f.curr_chat) != 0)
    {       
        if(chats_f.curr_chat != NULL)
            free(chats_f.curr_chat);
        chats_f.curr_chat = strdup(id);
        free_all_children_in_container(main_form.message_line);
        int j = 0;
        for (int i = 0; curr_chat.messages_g[i]; i++)
        {
            if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(curr_chat.messages_g[i]->message)) == 0)
            {
                gtk_grid_attach(GTK_GRID(main_form.message_line), curr_chat.messages_g[i]->event_box_message, 0, j++, 1, 1);
            }
        }
        gtk_widget_show_all(main_form.message_line);
    }
    return false;
}
