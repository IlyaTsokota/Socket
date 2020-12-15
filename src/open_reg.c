#include "chat.h"

void open_reg(GtkWidget *button, GtkWidget *widget)
{
        gtk_widget_destroy(widget);
        open_register(data.win); 
}
