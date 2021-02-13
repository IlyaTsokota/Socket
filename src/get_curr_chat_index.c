#include "chat.h"

int get_curr_chat_index()
{

        int index = 0;
        for (int i = 0; chats_f.chat_items[i]; i++)
        {
            if (strcmp(chats_f.curr_chat, (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact)) == 0)
            {
                index = i;
                break;
            }
        }
        return index;
}
