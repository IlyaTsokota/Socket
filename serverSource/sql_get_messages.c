#include "server.h"

char *get_messages(MYSQL *con, char *user_id, char *last_message_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"SELECT cu.ch_id, ms.ms_id, ms.u_id, u.u_name, u.u_surname, ms.ms_text, ms.ms_datetime, ms.ms_isedited, ms.ms_isforwarded, ms.ms_ismedia, ms.ms_isreply, ms.ms_isseen \
    FROM chatusers cu \
    join message ms on cu.ch_id = ms.ch_id \
    join user u on ms.u_id = u.u_id \
    WHERE cu.u_id = \"", user_id, "\" AND ms.ms_id > \"", last_message_id, "\" order by ms.ms_id;", NULL};

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

    message_t *message = NULL;
    
    
    str = strdup("{\"messages\": [");
    
    while ((row = mysql_fetch_row(result)))
    {
        message = (message_t *)malloc(sizeof(message_t));
        message->ch_id = strdup(row[0]);
        message->ms_id = strdup(row[1]);
        message->u_id = strdup(row[2]);
        message->u_name = strdup(row[3]);
        message->u_surname = strdup(row[4]);
        message->ms_text = strdup(row[5]);
        message->ms_datetime = strdup(row[6]);
        message->ms_isedited = strdup(row[7]);
        message->ms_isforwarded = strdup(row[8]);
        message->ms_ismedia = strdup(row[9]);
        message->ms_isreply = strdup(row[10]);
        message->ms_isseen = strdup(row[11]);
        tmp_str = write_message_to_json(message);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_message_s(message);
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
    if (socket_send_data(str, sock)) {
        return "0";
    }
    else {
        return "1";
    }
    
    return "1"; //0 or >0
}
