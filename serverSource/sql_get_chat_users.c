#include "server.h"

char *get_chat_users(MYSQL *con, char *ch_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"SELECT ch.u_id,  concat(u.u_name, ' ', u.u_surname) , u.u_avatar from chatusers ch join user u on  ch.u_id = u.u_id where ch.ch_id = \"", ch_id, "\";", NULL};

    bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    login_pin_info_t *chat_users_info = NULL;

    str = strdup("{\"chat_users_info\": [");

    while ((row = mysql_fetch_row(result)))
    {
        chat_users_info = (login_pin_info_t *)malloc(sizeof(login_pin_info_t));
        chat_users_info->u_id = strdup(row[0]);
        chat_users_info->u_login = strdup(row[1]);
        chat_users_info->u_avatar = strdup(row[2]);

        tmp_str = write_validation_login_info_to_json(chat_users_info);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_validation_login_info_s(chat_users_info);
    }
    str[strlen(str) - 1] = '\0';
    tmp_str1 = strjoin(2, str, "]}");
    free(str);
    str = tmp_str1;
    tmp_str1 = NULL;
    //
    mysql_free_result(result);
    mysql_close(con);
    //
    if (socket_send_data(str, sock))
    {
        return strdup("0");
    }
    else
    {
        return strdup("1");;
    }

    return strdup("1");; //0 or >0
}
