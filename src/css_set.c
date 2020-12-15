#include "chat.h"

void css_set(GtkWidget *widgets[], char *path_to_css, int size)
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, path_to_css, NULL);
    GtkStyleContext *context;
    for (int i = 0; i < size; i++)
    {
        {
            context = gtk_widget_get_style_context(widgets[i]);
            gtk_style_context_add_provider(context,
                                           GTK_STYLE_PROVIDER(css_provider),
                                           GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }
}

void css_set_for_one(GtkWidget *widget, char *path_to_css){
GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, path_to_css, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_provider(context,
                                    GTK_STYLE_PROVIDER(css_provider),
                                    GTK_STYLE_PROVIDER_PRIORITY_USER);
}
