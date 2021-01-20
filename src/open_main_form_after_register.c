#include "chat.h"

void open_main_form_after_register(GtkWidget *button, GtkWidget *widget)
{
    char* settings = mx_file_to_str("settings.json");
    settings_t *settings_field = get_settings(settings);
    create_settings_json(registration.login_text, settings_field->theme, settings_field->language, "TRUE");
    free_settings(settings_field); 
    gtk_widget_destroy(widget);
    open_main_form(data.win);    
}
