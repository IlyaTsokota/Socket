#include "chat.h"

char* get_last_mesage_id(char* filename) {
    FILE* file_num = NULL;
    file_num = fopen(filename, "r");
    if (file_num != NULL) {
        fclose(file_num);
        char *str = mx_file_to_str(filename);
        json_object *jobj, *values_obj, *tmp_values, *values_name;
        jobj = json_tokener_parse(str);
        free(str);
        int exist = 0;
        exist = json_object_object_get_ex(jobj, "messages", &values_obj);
        int length = json_object_array_length(values_obj) - 1;
        ////puts(int_to_str(length));
        tmp_values = json_object_array_get_idx(values_obj, length);
        json_object_object_get_ex(tmp_values, "ms_id", &values_name);
        char *tmp = strdup((char *)json_object_get_string(values_name));
        return tmp;
    }
    return strdup("0");
}