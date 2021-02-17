#include "chat.h"

void create_widget_contacts(char *user_id)
{
    //g_mutex_lock(&main_form.mutex);

    char *num_f = strdup("21");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc, json);
    free(json);
    //// //puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL)
    {
        return;
    }
    free(jobj);

    contact_t **contacts = get_contacts(response);
    free(response);

    if (contacts != NULL)
    {
        contacts_t.was_free = false;
        int size = 0;
        for (size_t i = 0; contacts[i]; i++)
        {
            size++;
        }
        
        for (size_t i = 0; i < size; i++)
        {
            create_one_contact(i, contacts[i]);
        }
        free_contacts_s(contacts);
    }
    //g_mutex_unlock(&main_form.mutex);
}
