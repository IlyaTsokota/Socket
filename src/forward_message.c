#include "chat.h"

gboolean forward_message(GtkWidget *widget, GdkEventButton *event)
{
    char *id = (char *)gtk_widget_get_name(widget);

    char *num_f = strdup("17");
    char *arr[] = {main_form.curr_ms_id, id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server( json);
    free(json);

    free_chat_widgets(chats_form_sec.chat_items);
    gtk_widget_destroy(main_form.popup_window);

    return false;
}
