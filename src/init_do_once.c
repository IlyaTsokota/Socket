#include "chat.h"

void init_do_once(bool value)
{
    do_once.bshow_chats = value;
    do_once.bshow_contacts = value;
    do_once.bshow_edit_profile = value;
    do_once.bshow_language = value;
    do_once.bshow_privacy = value;
    do_once.bshow_double_bottom = value;
    do_once.bshow_appereance = value;
    do_once.bshow_open_contact = value;
    do_once.bshow_right_panel_is_clear = value;
    do_once.bshow_setting = value;
    do_once.bshow_notification = value;
    do_once.bshow_add_chat = value;
    do_once.bshow_chat_info = value;
    do_once.bshow_add_participant = value;
    do_once.bshow_remove_participant = value;
    do_once.bshow_add_contact = value;
    do_once.bshow_change_password = value;
    do_once.bshow_change_pin= value;
}
