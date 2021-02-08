#include "chat.h"

gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form)
{

    gtk_widget_destroy(form);
    open_form_pin(data.win, false);
    init_do_once(true);
    free(data.user_id);
    free(data.user_login);
    free(data.picture_name);
    remove("messages.json");
    return false;
}