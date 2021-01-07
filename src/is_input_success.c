#include "chat.h"

void is_input_success(bool (*is_success)(int, int*, char*), GtkWidget **entry, int *min)
{
    char *entry_text = (char*)gtk_entry_get_text(GTK_ENTRY(*entry));
    GtkCssProvider *css_provider = gtk_css_provider_new();
    if (!is_success(strlen(entry_text), min, entry_text))
    {
        gtk_css_provider_load_from_data(css_provider, "* {   border-bottom: 2px solid rgb(180, 6, 6);}", -1, NULL);
    }
    else
    {
        gtk_css_provider_load_from_data(css_provider, "* {   border-bottom: 2px solid green;}", -1, NULL);
    }
    GtkStyleContext *context = gtk_widget_get_style_context(*entry);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
