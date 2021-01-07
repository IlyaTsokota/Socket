#include "chat.h"

void create_new_user(char *login, char *name, char *surname, char *password, char *pin){
    char *arr[] = {"03", login , name, surname, password, pin};
    char **new_arr = (char**)malloc(sizeof(char*) * 6);
    for (int i = 0; i < 6; i++)
    {
        g_print("NOTConv+error '%s'\n", g_get_codeset());
        new_arr[i] = g_locale_to_utf8(arr[i], strlen(arr[i]), NULL, NULL, NULL);//g_convert(arr[i], strlen(arr[i]), "UTF-8", "UTF-8", NULL, NULL, NULL); // 
        if (new_arr[i] == NULL) {
            g_print("STR_FAIL: ' %s ', ' %d '\n", arr[i], i);
            g_print("Conv+error '%s'\n", g_get_codeset());
            return;
        }
        //g_convert(arr[i], -1, "CP1251", "UTF-8", NULL, NULL, NULL); //= (char*)malloc(strlen(arr[i]));
        new_arr[i + 1] = NULL;
        //strcpy(new_arr[i], arr[i]);
    }
    char *request = array_to_str_with_delimiter(new_arr, 6);
    //g_print("str = ' %s '\n", lol);
    //char *lol1 = g_convert(lol, -1, "CP1251", "UTF-8", NULL, NULL, NULL);
    //g_print("str1 = ' %s '\n", lol);
    //char *request = lol;//g_convert(, -1, "CP1251", "UTF-8", NULL, NULL, NULL);
    request_to_server(request);
}
