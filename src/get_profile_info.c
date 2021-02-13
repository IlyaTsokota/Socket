#include "chat.h"

user_t *get_profile_info(){
    //g_mutex_lock(&main_form.mutex);

    char *num_f = strdup("20");
    char *arr[] = {data.user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc,json);
    int exist = 0;
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    user_t *user = malloc(sizeof(user_t)); 
    exist = json_object_object_get_ex(jobj, "user", &values_obj);
    tmp_values = json_object_array_get_idx(values_obj, 0);
    json_object_object_get_ex(tmp_values, "u_name", &values_name);
    user->u_name = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_surname", &values_name);
    user->u_surname = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_status", &values_name);
    user->u_status = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
    user->u_avatar = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    free(tmp_values);
    free(values_obj);
    free(jobj);
    //g_mutex_unlock(&main_form.mutex);

    return user;
}