#include "chat.h"

void open_login_form(GtkWidget *button, GtkWidget *widget)
{
    gtk_widget_destroy(widget);
    open_login(data.win);
}

void logout(GtkWidget *button, GtkWidget *widget)
{
    init_do_once(true);
    main_form.current_panel_id = -1;
    gtk_widget_destroy(main_form.app_form);
    remove("messages.json");
    char* settings = mx_file_to_str("settings.json");
    settings_t *settings_field = get_settings(settings);
    create_settings_json("NULL", settings_field->theme, settings_field->language, "FALSE");
    free_settings(settings_field);
    open_login(data.win);
}
