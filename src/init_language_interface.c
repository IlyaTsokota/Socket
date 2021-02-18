#include "chat.h"

void init_language_interface(char *language)
{
    if (strcmp(language, "English") == 0)
    {
        data.language = strdup("English");
        localization_s.add_chat = strdup("share/add_chat.glade");
        localization_s.add_contact = strdup("share/add_contact.glade");
        localization_s.add_participant = strdup("share/add_participant.glade");
        localization_s.appereance = strdup("share/appereance.glade");
        localization_s.chat_info = strdup("share/chat_info.glade");
        localization_s.chats = strdup("share/chats.glade");
        localization_s.contacts_left = strdup("share/contacts_left.glade");
        localization_s.contacts_right = strdup("share/contacts_right.glade");
        localization_s.double_bottom = strdup("share/double_bottom.glade");
        localization_s.edit_profile = strdup("share/edit_profile.glade");
        localization_s.language = strdup("share/language.glade");
        localization_s.left_panel_setting = strdup("share/left_panel_setting.glade");
        localization_s.login = strdup("share/login.glade");
        localization_s.main = strdup("share/main.glade");
        localization_s.notifications = strdup("share/notifications.glade");
        localization_s.opened_chat = strdup("share/opened_chat.glade");
        localization_s.pin_code = strdup("share/pin_code.glade");
        localization_s.privacy = strdup("share/privacy.glade");
        localization_s.register_one = strdup("share/register_one.glade");
        localization_s.register_three = strdup("share/register_three.glade");
        localization_s.register_two = strdup("share/register_two.glade");
        localization_s.remove_participant = strdup("share/remove_participant.glade");
        localization_s.change_password = strdup("share/change_password.glade");
        localization_s.change_pin = strdup("share/change_pin.glade");
    }
    else
    {
        data.language = strdup("Russian");
        localization_s.add_chat = strdup("share/add_chat-ru.glade");
        localization_s.add_contact = strdup("share/add_contact-ru.glade");
        localization_s.add_participant = strdup("share/add_participant-ru.glade");
        localization_s.appereance = strdup("share/appereance-ru.glade");
        localization_s.chat_info = strdup("share/chat_info-ru.glade");
        localization_s.chats = strdup("share/chats.glade");
        localization_s.contacts_left = strdup("share/contacts_left-ru.glade");
        localization_s.contacts_right = strdup("share/contacts_right-ru.glade");
        localization_s.double_bottom = strdup("share/double_bottom-ru.glade");
        localization_s.edit_profile = strdup("share/edit_profile-ru.glade");
        localization_s.language = strdup("share/language-ru.glade");
        localization_s.left_panel_setting = strdup("share/left_panel_setting-ru.glade");
        localization_s.login = strdup("share/login-ru.glade");
        localization_s.main = strdup("share/main.glade");
        localization_s.notifications = strdup("share/notifications-ru.glade");
        localization_s.opened_chat = strdup("share/opened_chat-ru.glade");
        localization_s.pin_code = strdup("share/pin_code-ru.glade");
        localization_s.privacy = strdup("share/privacy-ru.glade");
        localization_s.register_one = strdup("share/register_one-ru.glade");
        localization_s.register_three = strdup("share/register_three-ru.glade");
        localization_s.register_two = strdup("share/register_two-ru.glade");
        localization_s.remove_participant = strdup("share/remove_participant-ru.glade");
        localization_s.change_password = strdup("share/change_password-ru.glade");
        localization_s.change_pin = strdup("share/change_pin-ru.glade");
    }
}

gboolean switch_language(GtkSwitch *widget, gboolean state, gpointer info)
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
    free_language_interface();
    free(data.language);
    data.language = NULL;
    char *switch_lang = strcmp(settings_field->language, "English") == 0 ? strdup("Russian") : strdup("English");
    init_language_interface(switch_lang);
    free(switch_lang);

    create_settings_json(settings_field->login, settings_field->theme, data.language, settings_field->is_in);
    free(settings_field);

   g_main_loop_quit( main_form.loop_edit_msgs );
    g_thread_join(main_form.update_edit_msgs);
    g_main_loop_quit( main_form.loop_chat );
    g_thread_join(main_form.update_thread_chat);
    g_main_loop_quit( main_form.loop );
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

void free_language_interface()
{
    free(localization_s.add_chat);
    free(localization_s.add_contact);
    free(localization_s.add_participant);
    free(localization_s.appereance);
    free(localization_s.chat_info);
    free(localization_s.chats);
    free(localization_s.contacts_left);
    free(localization_s.contacts_right);
    free(localization_s.double_bottom);
    free(localization_s.edit_profile);
    free(localization_s.language);
    free(localization_s.left_panel_setting);
    free(localization_s.login);
    free(localization_s.main);
    free(localization_s.notifications);
    free(localization_s.opened_chat);
    free(localization_s.pin_code);
    free(localization_s.privacy);
    free(localization_s.register_one);
    free(localization_s.register_three);
    free(localization_s.register_two);
    free(localization_s.remove_participant);
    free(localization_s.change_password);
    free(localization_s.change_pin);
}