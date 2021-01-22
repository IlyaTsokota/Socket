#include "chat.h"

gboolean open_click_chat(GtkWidget *widget, GdkEventButton *event)
{
    char *id = (char*)gtk_widget_get_name(widget);
    puts(id);
    puts("GG");
    show_opened_chat(main_form.main_grid, id);
    return false;
}
