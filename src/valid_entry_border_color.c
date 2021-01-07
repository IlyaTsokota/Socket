#include "chat.h"

void valid_entry_border_color(GtkWidget **entry)
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider, "* {   border-bottom: 2px solid rgb(180, 6, 6);}", -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(*entry);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
