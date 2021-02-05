#include "chat.h"

gboolean open_click_chat(GtkWidget *widget, GdkEventButton *event)
{
    char *id = (char*)gtk_widget_get_name(widget);
    free(chats_f.curr_chat);
    chats_f.curr_chat = strdup(id);
    gtk_widget_destroy(main_form.right_content);
    show_opened_chat(main_form.main_grid, id);

    return false;
}
