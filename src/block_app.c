#include "chat.h"

gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form)
{
    gtk_widget_destroy(form);
    open_form_pin(data.win, false);
    return false;
}