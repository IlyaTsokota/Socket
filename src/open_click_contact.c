#include "chat.h"

gboolean open_click_contact(GtkWidget *widget)
{
    gtk_widget_destroy(main_form.right_content);
    char *id = (char*)gtk_widget_get_name(widget);
    show_open_contact(main_form.main_grid, id);
    return false;
}
