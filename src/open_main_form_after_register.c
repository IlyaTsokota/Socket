#include "chat.h"

void open_main_form_after_register(GtkWidget *button, GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    open_main_form(data.win);    
}
