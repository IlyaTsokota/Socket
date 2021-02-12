#include "server.h"

const char *write_contact_to_json(contact_t *contact)
{
    struct json_object *array;
    struct json_object *object;
    struct json_object *tmp;
    array = json_object_new_array();
    object = json_object_new_object();
    tmp = json_object_new_string(contact->c_id);
    json_object_object_add(object, "c_id", tmp);
    tmp = json_object_new_string(contact->u_name);
    json_object_object_add(object, "u_name", tmp);

    tmp = json_object_new_string(contact->u_avatar);
    json_object_object_add(object, "u_avatar", tmp);
    tmp = json_object_new_string(contact->u_status);
    json_object_object_add(object, "u_status", tmp);

    const char *answer = json_object_to_json_string(object);
    return answer;
}
