#include "server.h"

const char *write_user_to_json(user_t *user)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(user->u_name);
    json_object_object_add(object, "u_name", tmp);
    tmp = json_object_new_string(user->u_surname);
    json_object_object_add(object, "u_surname", tmp);
    tmp = json_object_new_string(user->u_status);
    json_object_object_add(object, "u_status", tmp);
    tmp = json_object_new_string(user->u_avatar);
    json_object_object_add(object, "u_avatar", tmp);


    const char *answer = json_object_to_json_string(object);
    return answer;
}
