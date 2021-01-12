#include "chat.h"

char *write_to_json(char* num_f,char **arr_new)
{
	struct json_object *array;
	struct json_object *object;
	struct json_object *tmp;
	array = json_object_new_array();
	object = json_object_new_object();
	int size = 0;
	for (size_t i = 0; arr_new[i]; i++)
	{
		size++;
	}
	char **arr = (char **)malloc(sizeof(char *) * size + 1);
	arr[size] = NULL;
	for (int i = 0; i < size; i++)
	{
		arr[i] = arr_new[i];
	}
	while (*arr)
	{
		tmp = json_object_new_string(*arr);
		json_object_array_add(array, tmp);
		arr++;
	}
	string_array_clear(arr,size);
	tmp = json_object_new_string(num_f);
	json_object_object_add(object, "func-number", tmp);
	json_object_object_add(object, "data", array);
	array = tmp = NULL;
	char *answer = (char *)json_object_to_json_string(object);
	json_object_put(object);
	return answer;
}
