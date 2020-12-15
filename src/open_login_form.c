#include "chat.h"

void open_login_form(GtkWidget *button, GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    open_login(data.win);
}
