#include "server.h"

char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data, int sock)
{
    char *date_time = set_date();
    char *new_ms_data = mx_strnew(strlen(ms_data) + g_utf8_strlen(ms_data, -1) * 8);
    size_t len = mysql_real_escape_string(con, new_ms_data, ms_data, strlen(ms_data));
    new_ms_data[len] = '\0';
    const char *request_parts[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"",
                                   ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\'", new_ms_data, "\');", NULL};

    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_real_query(con, bdrequest, strlen(bdrequest)))
    {
        finish_with_error(con);
    }

    free(new_ms_data); // IT
    free(date_time);   //IR
    free(bdrequest);   //IR

    const char *tmp_str, *coma_str = ",";
    char *str, *tmp_str1;
    const char *request_parts1[] = {"select max(ms_id) from message;", NULL};

    bdrequest = strjoins_arr(request_parts1);

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

    message_back_info_t *contact = NULL;

    str = strdup("{\"message_back_info\": [");

    while ((row = mysql_fetch_row(result)))
    {
        contact = (message_back_info_t *)malloc(sizeof(message_back_info_t));
        contact->ms_id = strdup(row[0]);
        contact->ms_datetime = date_time;

        tmp_str = write_message_back_info_json(contact);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_message_back_info_s(contact);
    }
    str[strlen(str) - 1] = '\0';
    tmp_str1 = strjoin(2, str, "]}");
    free(str);
    str = tmp_str1;
    tmp_str1 = NULL;
    //
    puts(str);
    mysql_free_result(result);
    mysql_close(con);
    free(date_time); //IR
    free(bdrequest); //IR
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
