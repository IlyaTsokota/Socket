#include "chat.h"

void sort_by_chat_widget()
{
    if (chats_f.chat_items != NULL && chats_f.chat_items[0] != NULL)
    {
        // if(!GTK_IS_CONTAINER(main_form.chats_grid)){
        //     puts("GG");
        // }
        // free_all_children_in_container(main_form.chats_grid);
        for (size_t i = 0; chats_f.chat_items[i]; i++)
        {
            char *max = (char *)gtk_label_get_text(GTK_LABEL(chats_f.chat_items[i]->time_last_message));
            for (size_t j = i; chats_f.chat_items[j]; j++)
            {
                char *curr = (char *)gtk_label_get_text(GTK_LABEL(chats_f.chat_items[j]->time_last_message));
                if (strcmp(max, curr) < 0)
                {
                    chat_item_t *temp = chats_f.chat_items[i];
                    chats_f.chat_items[i] = chats_f.chat_items[j];
                    chats_f.chat_items[j] = temp;
                }
            }
        }

        // for (int i = 0; chats_f.chat_items[i]; i++)
        // {
        //     gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
        // }
        // gtk_widget_show_all(main_form.chats_grid);
    }
}