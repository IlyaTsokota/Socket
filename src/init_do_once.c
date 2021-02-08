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

}
