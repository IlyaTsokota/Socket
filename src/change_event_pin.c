#include "chat.h"

void change_event_pin(GtkWidget *entry, int *min)
{
     is_input_success(is_pin, &entry, min);
}

void change_event_pin_on_pin_form(GtkWidget *entry, int *min){
     char *entry_text = (char*)gtk_entry_get_text(GTK_ENTRY(entry));
    GtkCssProvider *css_provider = gtk_css_provider_new();
    if (!is_pin(strlen(entry_text), min, entry_text))
    {
        gtk_css_provider_load_from_data(css_provider, "* {border: 2px solid rgb(180, 6, 6); border-left: none; border-right: none;}", -1, NULL);
    }
    else
    {
        gtk_css_provider_load_from_data(css_provider, "* {border: 2px solid green; border-left: none; border-right: none;}", -1, NULL);
    }
    GtkStyleContext *context = gtk_widget_get_style_context(entry);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
