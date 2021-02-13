#include "chat.h"

login_pin_info_t *request_get_pin_info(char *response)
{
    json_object *jobj, *values_obj, *tmp_values, *values_name;
    jobj = json_tokener_parse(response);
    login_pin_info_t *info = malloc(sizeof(login_pin_info_t));
    int exist = json_object_object_get_ex(jobj, "pin_check_info", &values_obj);
    tmp_values = json_object_array_get_idx(values_obj, 0);
    json_object_object_get_ex(tmp_values, "u_id", &values_name);
    info->u_id = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_login", &values_name);
    info->u_login = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_avatar", &values_name);
    info->u_avatar = strdup((char *)json_object_get_string(values_name));
    free(values_name);
    json_object_object_get_ex(tmp_values, "u_isBottommed", &values_name);
    info->u_isBottomed = json_object_get_boolean(values_name);
    free(values_name);
    free(tmp_values);
    free(values_obj);
    free(jobj);
    return info;
}
