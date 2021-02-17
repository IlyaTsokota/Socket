#include "chat.h"

void sort_by_chat_widget()
{
    if (chats_f.chat_items != NULL)
    {
        if (main_form.chats_grid != NULL)
            {
                char *max, *curr;
                chat_item_t *temp;
                gtk_widget_hide(main_form.chats_grid);
                free_all_children_in_container(main_form.chats_grid);
                for (size_t i = 0; i < chats_f.size - 1; i++)
                {
                    for (size_t j = 0; j < chats_f.size - i - 1; j++)
                    {
                        max = (char *)gtk_label_get_text(GTK_LABEL(chats_f.chat_items[j + 1]->time_last_message));
                        curr = (char *)gtk_label_get_text(GTK_LABEL(chats_f.chat_items[j]->time_last_message));

                        if (strcmp(curr, max) < 0)
                        {
                            temp = chats_f.chat_items[j];
                            chats_f.chat_items[j] = chats_f.chat_items[j + 1];
                            chats_f.chat_items[j + 1] = temp;
                        }
                    }
                }

                for (int i = 0; i < chats_f.size; i++)
                {
                    gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
                }
                gtk_widget_show_all(main_form.chats_grid);
            }
    }
}

void sort_chats(chat_t **chats, int size)
{
    char *max, *curr;
    chat_t *temp;
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if (strcmp(chats[j]->u_time, chats[j + 1]->u_time) < 0)
            {
                temp = chats[j];
                chats[j] = chats[j + 1];
                chats[j + 1] = temp;
            }
        }
    }
}

