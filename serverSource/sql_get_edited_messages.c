#include "server.h"

char *get_edited_messages(MYSQL *con, char *user_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"SELECT ms_id, ms_text FROM message WHERE u_id = \"", user_id, "\" and ms_isedited = \"1\";", NULL};

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

    message_back_info_t *message = NULL;

    str = strdup("{\"edited_messages\": [");

    while ((row = mysql_fetch_row(result)))
    {
        message = (message_back_info_t *)malloc(sizeof(message_back_info_t));
        message->ms_id = strdup(row[0]);
        message->ms_datetime = strdup(row[1]);

        tmp_str = write_message_back_info_json(message);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_message_back_info_s(message);
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
        return strdup("1");
    }

    return strdup("1"); //0 or >0
}
