#include "server.h"

array_t json_to_data(char *json_str)
{
	struct json_object *jobj;

	struct json_object *func_number;
	struct json_object *data;
	struct json_object *data_item;

	jobj = json_tokener_parse(json_str);

	json_object_object_get_ex(jobj, "func-number", &func_number);
	json_object_object_get_ex(jobj, "data", &data);

	int n_data = json_object_array_length(data);
	char *func_num_val = (char *)json_object_get_string(func_number);

	char **arr = (char **)malloc(sizeof(char *) * (n_data + 2));
	arr[0] = mx_strnew(strlen(func_num_val));
	strcpy(arr[0], func_num_val);
	for (int i = 0; i < n_data; i++)
	{
		data_item = json_object_array_get_idx(data, i);
		char *val = mx_strnew(strlen((char *)json_object_get_string(data_item)));
		val = (char *)json_object_get_string(data_item);
		arr[i + 1] = mx_strnew(strlen(val));
		strcpy(arr[i + 1], val);
	}
	arr[n_data + 1] = NULL;
	array_t array_obj;
	array_obj.arr = arr;
	array_obj.cnt = n_data + 1;

	return array_obj;
}
