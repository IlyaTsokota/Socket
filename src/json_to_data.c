#include "chat.h"

char **json_to_data(char* json_str){
	struct json_object *jobj;
	struct json_object *func_number;
	struct json_object *data;
	struct json_object *data_item;
	jobj = json_tokener_parse(json_str);
	json_object_object_get_ex(jobj, "func-number", &func_number);
	json_object_object_get_ex(jobj, "data", &data);

	int n_data= json_object_array_length(data);
	char *func_num_val = (char *)json_object_get_string(func_number);
	char **arr = (char**)malloc(sizeof(char*) * (n_data + 2));
	arr[n_data + 1] = NULL;
	arr[0] = (char*)malloc(sizeof(char) * strlen(func_num_val));
	arr[0] = func_num_val;
	char *val;
	for(int i=0;i<n_data;i++) {
		data_item = json_object_array_get_idx(data, i);
		val = (char *)json_object_get_string(data_item);
		arr[i+1] = (char*)malloc(sizeof(char) * strlen(val));
		arr[i+1] = val;
	}	
	return arr;
}
