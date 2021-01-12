#include "chat.h"

gboolean change_insert_to_message(gpointer widget)
{
    GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW((GtkWidget *)widget));
    gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
    return false;
}
