#include "chat.h"

void input_entry_event(GtkWidget *entry, int arr[])
{
    GtkStyleContext *context = gtk_widget_get_style_context(entry);
    int length = strlen(gtk_entry_get_text(GTK_ENTRY(entry)));
    g_print("%d\n", length);
     g_print("%d\n", arr[0]);
    if (length <= 4) {
        g_print("HYINA");
        // gtk_style_context_add_class(context, "bad-value");
    } else {
            g_print("Ok");
        // gtk_style_context_add_class(context, "succes-value");
    }
}