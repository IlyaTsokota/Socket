#include "chat.h"

bool is_pin_user(char *pin)
{
    char *num_f = strdup("02");
    char *arr[] = {autorization.login_text, pin, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc,json);
    if (strcmp(response, "0") == 0)
    {
        return false;
    }
    login_pin_info_t *pin_info = request_get_pin_info(response);
    free(response);
    data.user_id = strdup(pin_info->u_id);
    data.user_login = strdup(pin_info->u_login);
    data.picture_name = strdup(pin_info->u_avatar);
    free_validation_login_info_s(pin_info);
    return true;
}
