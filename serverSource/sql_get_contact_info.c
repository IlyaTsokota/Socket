#include "server.h"

char *get_contact_info(MYSQL *con, char *contact_id, char *my_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"SELECT u_login, concat(u_name, ' ', u_surname), u_avatar, u_status FROM user  where u_id = \"", contact_id, "\";", NULL};

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

    contact_info_t *contact = NULL;

    str = strdup("{\"contact_info\": [");

    while ((row = mysql_fetch_row(result)))
    {
        contact = (contact_info_t *)malloc(sizeof(contact_info_t));
        contact->u_login = strdup(row[0]);
        contact->u_name = strdup(row[1]);
        contact->u_avatar = strdup(row[2]);
        contact->u_status = strdup(row[3]);

        // tmp_str = write_contact_info_to_json(contact); Тут выпилил
        // tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        // free(str);
        // str = tmp_str1;
        // tmp_str1 = NULL;
        // free((void *)tmp_str);
        // free_contact_info_s(contact);
    }
    const char *request_parts2[] = {"select count(c_id) from contacts where c_id = \"", contact_id, "\" and u_id = \"", my_id, "\";", NULL};

    bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    MYSQL_RES *result1 = mysql_store_result(con);

    if (result1 == NULL)
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    num_fields = mysql_num_fields(result1);

    MYSQL_ROW row1 = mysql_fetch_row(result1);

    contact->is_my_contact = strcmp(row1[0], "0") ? false : true;

    //Сюда вставил
    tmp_str = write_contact_info_to_json(contact);
    tmp_str1 = strjoin(3, str, tmp_str, coma_str);
    free(str);
    str = tmp_str1;
    tmp_str1 = NULL;
    free((void *)tmp_str);
    free_contact_info_s(contact);
    //
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
