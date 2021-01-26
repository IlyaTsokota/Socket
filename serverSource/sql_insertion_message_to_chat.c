#include "server.h"

char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data)
{
    char *answer;
    //Добавить сообщение
    char *date_time = set_date();
    const char *request_parts[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"", 
    ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\"", ms_data, "\");", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    free(date_time); //IR
    free(bdrequest); //IR

    return "1";
}
