#include "chat.h"

gboolean open_click_chat(GtkWidget *widget, GdkEventButton *event)
{

    char *id = (char *)gtk_widget_get_name(widget);
    // if (strcmp(id, chats_f.curr_chat) != 0)
    // {
    hide_gtk_widgets(main_form.right_content);
    gtk_widget_show_all(main_form.right_content[0]);
    clear_style_all_chat_widgets();
    char *color = strcmp(data.theme, "Dark") == 0 ? strdup("* { background-color: #3c3c3c;}")
                                                  : strdup("* { background-color: #ebf3f7;}");
    edit_styles_for_widget(widget, color);
    free(color);
    if (chats_f.curr_chat != NULL)
        free(chats_f.curr_chat);
    chats_f.curr_chat = strdup(id);
    free_all_children_in_container(main_form.message_line);
    set_chat_name_top();

    if (curr_chat.messages_g != NULL)
    {
        int j = 0;
        for (int i = 0; curr_chat.messages_g[i]; i++)
        {
            if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(curr_chat.messages_g[i]->message)) == 0)
            {
                gtk_grid_attach(GTK_GRID(main_form.message_line), curr_chat.messages_g[i]->event_box_message, 0, j++, 1, 1);
            }
        }
    }

    clear_text__buffer(GTK_TEXT_VIEW(main_form.text_view));
    g_timeout_add(60, change_insert_to_message, main_form.message_scroll);

    gtk_widget_show_all(main_form.message_line);

    // }
    return false;
}

gboolean click_on_msg(GtkWidget *widget, GdkEventButton *event, GtkWidget *userdata)
{
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        view_popup_menu(widget, event, userdata);
    }
    return FALSE;
}
