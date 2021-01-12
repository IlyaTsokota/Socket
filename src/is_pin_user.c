#include "chat.h"

bool is_pin_user(char *pin){
      char *num_f = mx_strnew(strlen("02"));
    num_f ="02";
    char *arr[] = {autorization.login_text, pin, NULL};
    char *json = write_to_json(num_f, arr);
    char *request = g_locale_to_utf8(json, strlen(json), NULL, NULL, NULL);
    free(num_f);
    return request_to_server(request);
}
