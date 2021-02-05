#include "server.h"

char *pin_check(MYSQL *con, char *login, char *pin, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    char *encrypted_pin = crypt(pin, "1337_1488");
    const char *request_parts[] = {"Select u.u_id, u.u_avatar, u.u_login from user u join credentials c on c.u_id = u.u_id where (u.u_id = (Select u_id from user where u_login = \"", login, "\") or u.u_isBottommed = (Select u_id from user where u_login = \"", login, "\") ) and c.cr_pincode = \"", encrypted_pin, "\";", NULL};
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
    //If bug, try to comment this if
    if (num_fields <= 0)
    {
        return "1";
    }

    MYSQL_ROW row;

    login_pin_info_t *message = NULL;

    str = strdup("{\"pin_check_info\": [");

    while ((row = mysql_fetch_row(result)))
    {
        message = (login_pin_info_t *)malloc(sizeof(login_pin_info_t));
        message->u_id = strdup(row[0]);
        message->u_login = strdup(row[1]);
        message->u_avatar = strdup(row[2]);
        tmp_str = write_validation_login_info_to_json(message);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_validation_login_info_s(message);
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
