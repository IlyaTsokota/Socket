#include "chat.h"

void init_language_interface(char *language)
{
    if (strcmp(language, "Englsih") == 0)
    {
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
    }
    else
    {
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
    }
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
}