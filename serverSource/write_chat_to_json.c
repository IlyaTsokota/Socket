#include "server.h"

const char *write_chat_to_json(chat_t *chat)
{
	struct json_object *array;
	struct json_object *object;
	struct json_object *tmp;
	array = json_object_new_array();
	object = json_object_new_object();
	tmp = json_object_new_string(chat->ch_id);
	json_object_object_add(object, "ch_id", tmp);
	tmp = json_object_new_string(chat->ch_name);
	json_object_object_add(object, "ch_name", tmp);
	tmp = json_object_new_string(chat->ch_avatar);
	json_object_object_add(object, "ch_avatar", tmp);
	tmp = json_object_new_string(chat->u_login);
	json_object_object_add(object, "u_login", tmp);
	tmp = json_object_new_string(chat->u_lastSeen);
	json_object_object_add(object, "u_last_seen", tmp);
	tmp = json_object_new_string(chat->u_avatar);
	json_object_object_add(object, "u_avatar", tmp);
	const char *answer = json_object_to_json_string(object);
	return answer;
}


