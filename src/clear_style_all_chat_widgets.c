#include "chat.h"

void clear_style_all_chat_widgets()
{
    char *color = strcmp(data.theme, "Dark") == 0 ? strdup("* { background-color: #252526;}")
                                                  : strdup("* { background-color: #c8d1e0;}");
    for (size_t i = 0; chats_f.chat_items[i]; i++)
    {
        edit_styles_for_widget(chats_f.chat_items[i]->event_box_contact, color);
    }
    free(color);
}
