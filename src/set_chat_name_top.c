#include "chat.h"

void set_chat_name_top()
{
    int index = 0;
    for (int i = 0; chats_f.chat_items[i]; i++)
    {
        if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact)) == 0)
        {
            index = i;
            break;
        }
    }
    char *name = (char *)gtk_label_get_text(GTK_LABEL(chats_f.chat_items[index]->contact_name_lable));
    gtk_label_set_text(GTK_LABEL(main_form.top_panel_top_text), name);
    int opacity = gtk_widget_get_opacity(chats_f.chat_items[index]->user_is_online);
    if (opacity == 0)
    {
        gtk_label_set_text(GTK_LABEL(main_form.top_panel_bottom_text), "");
        gtk_widget_show(main_form.chat_info_event_box);
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(main_form.top_panel_bottom_text), "Online");
        gtk_widget_hide(main_form.chat_info_event_box);
    }
}