#include "chat.h"

bool is_pin_user(char *pin){
    char *num_f = strdup("02");
    char *arr[] = {autorization.login_text, pin, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    return request_to_server(json);
}
