#include "server.h"

char *make_message_seen(MYSQL *con, char *ms_id)
{
    const char *request_parts[] = {"UPDATE message SET ms_isseen = \"1\" WHERE ms_id = \"", ms_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    mysql_close(con);

    return "1";
}
