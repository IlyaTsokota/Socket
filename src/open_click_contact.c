#include "chat.h"

gboolean open_click_contact(GtkWidget *widget)
{

    hide_gtk_widgets(main_form.right_content);
    char *id = (char*)gtk_widget_get_name(widget);
    show_open_contact(main_form.main_grid, id);
    gtk_widget_show_all(main_form.right_content[2]);

    return false;
}
