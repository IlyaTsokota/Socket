#include "chat.h"

void open_register_third_form(GtkWidget *button, GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    open_register_third(data.win);
}