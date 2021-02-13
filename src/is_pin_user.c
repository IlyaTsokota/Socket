#include "chat.h"

bool is_pin_user(char *pin)
{
    char *num_f = strdup("02");
    char *arr[] = {autorization.login_text, pin, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc,json);
    puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
   
    if (jobj == NULL)
    {
        return false;
    }

    free(jobj);
    login_pin_info_t *pin_info = request_get_pin_info(response);
    free(response);
    data.user_id = strdup(pin_info->u_id);
    data.user_login = strdup(pin_info->u_login);
    data.picture_name = strdup(pin_info->u_avatar);
    data.isBottomed = pin_info->u_isBottomed;
    free_validation_login_info_s(pin_info);
    
    return true;
}
