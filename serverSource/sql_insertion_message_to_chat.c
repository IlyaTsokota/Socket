#include "server.h"

char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data)
{
    char *answer;
    //Добавить сообщение
    char *bdrequest = strjoins("INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"", ch_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, user_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, set_date());
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, ms_is_forwarded);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, ms_is_reply);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, "0");
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, "0\",\"");
    bdrequest = strjoins(bdrequest, ms_is_media);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, ms_data);
    bdrequest = strjoins(bdrequest, "\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    return "1";
}
