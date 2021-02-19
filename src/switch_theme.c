#include "chat.h"

gboolean switch_theme(GtkSwitch *widget, gboolean state, gpointer info)
{

    gtk_switch_set_state(widget, state);
    init_do_once(true);
    if (chats_f.curr_chat != NULL)
    {
        free(chats_f.curr_chat);
        chats_f.curr_chat = NULL;
    }

    if (main_form.last_ms_id != NULL)
    {
        free(main_form.last_ms_id);
        main_form.last_ms_id = NULL;
    }
    // = 2;
    // = true;
    char *settings = mx_file_to_str("settings.json");
    settings_t *settings_field = get_settings(settings);
    free_theme();
    switch_current_theme(settings_field->theme);
    ////puts(settings_field->login);
    create_settings_json(settings_field->login, data.theme, settings_field->language, settings_field->is_in);
    free(settings_field);

    g_main_loop_quit(main_form.loop_edit_msgs);
    g_thread_join(main_form.update_edit_msgs);
    g_main_loop_quit(main_form.loop_chat);
    g_thread_join(main_form.update_thread_chat);
    g_main_loop_quit(main_form.loop);
    g_thread_join(main_form.update_thread);
    free_message_widgets(curr_chat.messages_g);
    free_chat_widgets(chats_f.chat_items);
    free_contact_widgets(contacts_t.widgets);
    free_user_widgets(users_in_chat.users);

    clear_interface();
    gtk_widget_destroy(main_form.app_form);
    open_main_form(data.win);
    // g_signal_emit_by_name( main_form.event_box_setting, "button-press-event",  main_form.event_box_setting);

    return false;
}

void free_theme()
{
    free(data.theme);
    free(data.auth_theme_path);
    free(data.main_theme_path);
    data.theme = NULL;
    data.auth_theme_path = NULL;
    data.main_theme_path = NULL;
}

void what_theme_select(char *curr_theme)
{
    if (strcmp(curr_theme, "Dark") == 0)
    {
        data.theme = strdup("Dark");
        data.auth_theme_path = strdup("share/resources/css/auth.css");
        data.main_theme_path = strdup("share/resources/css/main.css");
    }
    else
    {
        data.theme = strdup("Light");
        data.auth_theme_path = strdup("share/resources/css/auth-light.css");
        data.main_theme_path = strdup("share/resources/css/main-light.css");
    }
}

void switch_current_theme(char *curr_theme)
{
    if (strcmp(curr_theme, "Dark") != 0)
    {
        data.theme = strdup("Dark");
        data.auth_theme_path = strdup("share/resources/css/auth.css");
        data.main_theme_path = strdup("share/resources/css/main.css");
        edit_styles_for_widget(data.win, "*{background-color: #252526;}");
    }
    else
    {
        edit_styles_for_widget(data.win, "*{background-color: #e1f3fc;}");
        data.theme = strdup("Light");
        data.auth_theme_path = strdup("share/resources/css/auth-light.css");
        data.main_theme_path = strdup("share/resources/css/main-light.css");
    }
}
