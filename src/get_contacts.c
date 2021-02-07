#include "chat.h"

contact_t **get_contacts(char *response)
{
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    exist = json_object_object_get_ex(jobj, "contacts", &values_obj);
    int length = json_object_array_length(values_obj);
    if (length > 0)
    { 
        contact_t **contacts = malloc(sizeof(contact_t *) * (length + 1));
        contacts[length] = NULL;
        for (size_t i = 0; i < length; i++)
        {
            tmp_values = json_object_array_get_idx(values_obj, i);
            contacts[i] = malloc(sizeof(contact_t));
            json_object_object_get_ex(tmp_values, "c_id", &values_name);
            contacts[i]->c_id = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
            contacts[i]->u_avatar = strdup((char *)json_object_get_string(values_name));
            free(values_name);
             json_object_object_get_ex(tmp_values, "u_name", &values_name);
            contacts[i]->u_name = strdup((char *)json_object_get_string(values_name));
            free(values_name);
             json_object_object_get_ex(tmp_values, "u_status", &values_name);
            contacts[i]->u_status = strdup((char *)json_object_get_string(values_name));
            free(values_name);
            free(tmp_values);
        }
        free(values_obj);
        free(jobj);
        return contacts;
    }
    free(values_obj);
    free(jobj);
    return NULL;
}
