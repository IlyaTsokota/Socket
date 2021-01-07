#include "server.h"

char *make_message_seen(MYSQL *con, char *ms_id)
{
    char *answer;

    char *bdrequest = strjoins("UPDATE message SET ms_isseen = \"1\" WHERE ms_id = \"", ms_id);
    bdrequest = strjoins(bdrequest, "\";");
    
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    return "1";
}
