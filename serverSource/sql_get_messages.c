#include "server.h"

char *get_messages(MYSQL *con, char *user_id, char *last_message_id)
{
    char *answer;
    char *bdrequest = strjoins("\
    SELECT cu.ch_id, ms.ms_id, ms.u_id, u.u_name, u.u_surname, ms.ms_text, ms.ms_datetime, ms.ms_isedited, ms.ms_isforwarded, ms.ms_ismedia, ms.ms_isreply, ms.ms_isseen \
    FROM chatusers cu \
    join message ms on cu.ch_id = ms.ch_id \
    join user u on ms.u_id = u.u_id \
    WHERE cu.u_id = \"", user_id);
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

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            puts(row[i]);
            //answer = row[i];
        }
    }
    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
