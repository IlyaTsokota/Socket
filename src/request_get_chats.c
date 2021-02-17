#include "chat.h"

chat_t **request_get_chats(char *str)
{
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(str);
    exist = json_object_object_get_ex(jobj, "chats", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    {
        int last_msg_index = 0;
        chat_t **chats = malloc(sizeof(chat_t *) * (length + 1));
        chats[length] = NULL;
        for (ssize_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            chats[i] = malloc(sizeof(chat_t));
            json_object_object_get_ex(tmp_values, "ch_id", &values_name);
            chats[i]->ch_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_name", &values_name);
            chats[i]->ch_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "ch_avatar", &values_name);
            chats[i]->ch_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_login", &values_name);
            chats[i]->u_login = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_last_seen", &values_name);
            chats[i]->u_lastSeen = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
            chats[i]->u_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
            last_msg_index = -1;
            if (curr_chat.messages_g != NULL)
            {
                for (ssize_t j = *(curr_chat.length) - 1; j >= 0; j--)
                {
                    char *ms_id = (char *)gtk_widget_get_name(curr_chat.messages_g[j]->message);
                    if (strcmp(ms_id,  chats[i]->ch_id) == 0)
                    {
                        last_msg_index = j;
                        break;
                    }
                }
            }
            if (last_msg_index != -1)
            {
                chats[i]->u_time = strdup(gtk_label_get_text(GTK_LABEL(curr_chat.messages_g[last_msg_index]->message_time)));
            }
            else
            {
                chats[i]->u_time  = strdup("");
            }
        }
        free(values_obj);
        free(jobj);

        return chats;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}
