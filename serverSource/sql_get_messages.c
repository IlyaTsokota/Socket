#include "server.h"

char *get_messages(MYSQL *con, char *user_id, char *last_message_id, int sock)
{
    char *answer;
    char *bdrequest = strjoins("\
    SELECT cu.ch_id, ms.ms_id, ms.u_id, u.u_name, u.u_surname, ms.ms_text, ms.ms_datetime, ms.ms_isedited, ms.ms_isforwarded, ms.ms_ismedia, ms.ms_isreply, ms.ms_isseen \
    FROM chatusers cu \
    join message ms on cu.ch_id = ms.ch_id \
    join user u on ms.u_id = u.u_id \
    WHERE cu.u_id = \"",
                               user_id);
    bdrequest = strjoins(bdrequest, "\" AND ms.ms_id > \"");
    bdrequest = strjoins(bdrequest, last_message_id);
    bdrequest = strjoins(bdrequest, "\";");

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

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    message_t *message = NULL;
    json_t *query = (json_t *)malloc(sizeof(json_t));
    size_t query_arr_length = 1024;
    query->arr = (char **)malloc(sizeof(char *) * query_arr_length);
    size_t length = 0;

    const char *tmp_str;
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
        //puts(strdup(tmp_str));
        query->arr[length] = strdup(tmp_str);

        free((void *)tmp_str);
        free_message_s(message);
        length++;
        if (length == query_arr_length)
        {
            query_arr_length *= 2;
            query->arr = (char **)realloc(query->arr, sizeof(char *) * query_arr_length);
        }
    }
    query->arr[length] = NULL;

    char plug[3];
    write(sock, int_to_str(length), strlen(int_to_str(length)));
    read(sock, plug, 2);

    for (size_t i = 0; i < length; i++)
    {
        puts(query->arr[i]);
        write(sock, query->arr[i], strlen(query->arr[i]));
        read(sock, plug, 2);
    }
    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
