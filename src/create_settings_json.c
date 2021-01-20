#include "chat.h"

void create_settings_json(char *login, char *theme, char *language, char *is_in){
    struct json_object *object;
	struct json_object *tmp;

	object = json_object_new_object();
    tmp = json_object_new_string(login);
	json_object_object_add(object, "login", tmp);
    tmp = json_object_new_string(theme);
	json_object_object_add(object, "theme", tmp);
    tmp = json_object_new_string(language);
	json_object_object_add(object, "language", tmp);
    tmp = json_object_new_string(is_in);
	json_object_object_add(object, "is_in", tmp);
    char *json_str = (char *)json_object_to_json_string(object);
    str_to_file("settings.json", json_str);
    free(json_str);
    free(tmp);
    free(object);
}

settings_t *get_settings(char *settings){
    struct json_object *jobj;
	struct json_object *tmp;

    settings_t *settings_s = malloc(sizeof(settings_t));
	jobj = json_tokener_parse(settings);
	free(settings);
    json_object_object_get_ex(jobj, "login", &tmp);
    settings_s->login = strdup((char *)json_object_get_string(tmp));
    free(tmp);
	json_object_object_get_ex(jobj, "theme", &tmp);
    settings_s->theme = strdup((char *)json_object_get_string(tmp));
    free(tmp);
    json_object_object_get_ex(jobj, "language", &tmp);
    settings_s->language = strdup((char *)json_object_get_string(tmp));
    free(tmp);	
    json_object_object_get_ex(jobj, "is_in", &tmp);
    settings_s->is_in = strdup((char *)json_object_get_string(tmp));
    free(tmp);
    free(jobj);
    return settings_s;
}

void free_settings(settings_t *settings){
    if(settings != NULL){
        free(settings->login);
        free(settings->language);
        free(settings->theme);
        free(settings->is_in);
        free(settings);
        settings = NULL;
    }
}
