#include "chat.h"

contact_info_t *get_contact_info(char *contact_id){
            //g_mutex_lock(&main_form.mutex);

    char *num_f = strdup("22");
    char *arr[] = {contact_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc,json);
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    contact_info_t *info = malloc(sizeof(contact_info_t)); 
    exist = json_object_object_get_ex(jobj, "contact_info", &values_obj);
    tmp_values = json_object_array_get_idx(values_obj, 0);
    json_object_object_get_ex(tmp_values, "u_login", &values_name);
    info->u_login = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_name", &values_name);
    info->u_name = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_status", &values_name);
    info->u_status = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
    info->u_avatar = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    free(tmp_values);
    free(values_obj);
    free(jobj);
            //g_mutex_unlock(&main_form.mutex);

    return info;
}