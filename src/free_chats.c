#include "chat.h"

void free_chats(chat_t **chats)
{
    if (chats != NULL)
    {
        for (int i = 0; chats[i]; i++)
        {
            free(chats[i]->ch_id);
            free(chats[i]->ch_name);
            free(chats[i]->ch_avatar);
            free(chats[i]->u_avatar);
            free(chats[i]->u_lastSeen);
            free(chats[i]->u_login);
            free(chats[i]);
        }
        free(chats);
        chats = NULL;
    }
}

void free_messages(message_arr *message_container)
{
    if (message_container != NULL)
    {
        for (int i = 0; i < *message_container->length; i++)
        {

            free(message_container->messages[i]->ms_datetime);
            free(message_container->messages[i]->ms_id);
            free(message_container->messages[i]->ms_isedited);
            free(message_container->messages[i]->ms_isforwarded);
            free(message_container->messages[i]->ms_ismedia);
            free(message_container->messages[i]->ms_isreply);
            free(message_container->messages[i]->ms_isseen);
            free(message_container->messages[i]->ms_text);
            free(message_container->messages[i]->u_id);
            free(message_container->messages[i]->u_name);
            free(message_container->messages[i]);
        }
        free(message_container->messages);
        free(message_container->length);
        free(message_container);
        // message_container->messages = NULL;
        // message_container = NULL;
    }
}

void free_chat_items(chat_item_t **chats)
{
    if (chats != NULL && !chats_f.was_free)
    {
        for (size_t i = 0; chats[i]; i++)
        {
            gtk_widget_destroy(chats[i]->img_contact);
            gtk_widget_destroy(chats[i]->contact_img_container);
            gtk_widget_destroy(chats[i]->text_last_message);
            gtk_widget_destroy(chats[i]->login_last_message);
            gtk_widget_destroy(chats[i]->contact_last_msg);
            gtk_widget_destroy(chats[i]->contact_name_lable);
            gtk_widget_destroy(chats[i]->user_is_online_round);
            gtk_widget_destroy(chats[i]->user_is_online);
            gtk_widget_destroy(chats[i]->contact_name_container);
            gtk_widget_destroy(chats[i]->time_last_message);
            gtk_widget_destroy(chats[i]->contact_info);
            gtk_widget_destroy(chats[i]->contact_container);
            gtk_widget_destroy(chats[i]->event_box_contact);
            free(chats[i]);
        }
        free(chats);
        chats = NULL;
        chats_f.was_free = true;

    }
}
