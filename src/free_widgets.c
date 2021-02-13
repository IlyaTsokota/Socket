#include "chat.h"
void free_contact_widgets(contacts_widget_s **contacts)
{
    if (contacts != NULL && !contacts_t.was_free)
    {

        ////puts("To e pizda");
        for (size_t i = 0; contacts[i]; i++)
        {
            gtk_widget_destroy(contacts[i]->contact_name_lable);
            gtk_widget_destroy(contacts[i]->contact_status_lable);
            gtk_widget_destroy(contacts[i]->contact_name_container);
            gtk_widget_destroy(contacts[i]->contact_status);
            gtk_widget_destroy(contacts[i]->img_contact);
            gtk_widget_destroy(contacts[i]->grid_list_contact_img);
            gtk_widget_destroy(contacts[i]->contact_info);
            gtk_widget_destroy(contacts[i]->contact_container);
            gtk_widget_destroy(contacts[i]->event_box_contact);
            free(contacts[i]);
        }
        free(contacts);
        ////puts("Tochno pizda");
        contacts = NULL;
        contacts_t.was_free = true;
    }
}

void free_chat_widgets(chat_item_t **contacts)
{
    if (contacts != NULL && !chats_f.was_free)
    {

        for (size_t i = 0; contacts[i]; i++)
        {   
            gtk_widget_destroy(contacts[i]->login_last_message);
            gtk_widget_destroy(contacts[i]->text_last_message);
            gtk_widget_destroy(contacts[i]->contact_name_lable);
            gtk_widget_destroy(contacts[i]->user_is_online_round);
            gtk_widget_destroy(contacts[i]->user_is_online);
            gtk_widget_destroy(contacts[i]->contact_last_msg);
            gtk_widget_destroy(contacts[i]->img_contact);
            gtk_widget_destroy(contacts[i]->contact_img_container);
            gtk_widget_destroy(contacts[i]->contact_name_container);
            gtk_widget_destroy(contacts[i]->contact_info);
            gtk_widget_destroy(contacts[i]->time_last_message);
            gtk_widget_destroy(contacts[i]->contact_container);
            gtk_widget_destroy(contacts[i]->event_box_contact);
            free(contacts[i]);
        }
        free(contacts);
        ////puts("Tochno pizda");
        contacts = NULL;
        chats_f.was_free = true;
        chats_f.size = 0;
        chats_f.chat_items = NULL;
    }
}

void free_message_widgets(messages_t **message)
{
    if (message != NULL )
    {

        for (size_t i = 0; message[i]; i++)
        {   
            gtk_widget_destroy(message[i]->message_login);
            gtk_widget_destroy(message[i]->message_time);
            gtk_widget_destroy(message[i]->message_text);
            gtk_widget_destroy(message[i]->message_info);
            gtk_widget_destroy(message[i]->message);
            gtk_widget_destroy(message[i]->event_box_message);
            free(message[i]);
        }
        free(message);
        free(curr_chat.length);
        curr_chat.messages_g = NULL;
        curr_chat.length = NULL;
    }
}

void free_user_widgets(user_in_chat_t **contacts)
{
    if (contacts != NULL )
    {

        ////puts("To e pizda");
        for (size_t i = 0; contacts[i]; i++)
        {
            gtk_widget_destroy(contacts[i]->user_img);
            gtk_widget_destroy(contacts[i]->user_name);
            gtk_widget_destroy(contacts[i]->remove_img);
            gtk_widget_destroy(contacts[i]->body_user);
            gtk_widget_destroy(contacts[i]->delete_event_box);
            gtk_widget_destroy(contacts[i]->user_event_box);
            gtk_widget_destroy(contacts[i]->users_item);
            free(contacts[i]);
        }
        free(contacts);
        ////puts("Tochno pizda");
     users_in_chat.users = NULL;
    users_in_chat.size = 0;
    }
}

