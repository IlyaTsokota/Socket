#include "chat.h"

gboolean open_setting(GtkWidget *widget, GdkEventButton *event)
{
    gtk_widget_destroy(main_form.right_content);
    gtk_widget_destroy(main_form.left_content);
    show_setting(main_form.main_grid);
    show_right_panel_is_clear(main_form.main_grid);
    return false;
}