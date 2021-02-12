#include "server.h"

char *get_user_info(MYSQL *con, char *user_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"SELECT u_name, u_surname, u_avatar, u_status FROM user where u_id = \"", user_id, "\";", NULL};

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

    user_t *user = NULL;

    str = strdup("{\"user\": [");

    while ((row = mysql_fetch_row(result)))
    {
        user = (user_t *)malloc(sizeof(user_t));
        user->u_name = strdup(row[0]);
        user->u_surname = strdup(row[1]);
        user->u_avatar = strdup(row[2]);
        user->u_status = strdup(row[3]);

        tmp_str = write_user_to_json(user);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_user_s(user);
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
        return "0";
    }
    else
    {
        return "1";
    }

    return "1"; //0 or >0
}
