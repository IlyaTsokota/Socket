
#include "server.h"

char *delete_message(MYSQL *con, char *ch_id, char *ms_id)
{

    const char *request_parts[] = {"delete from message where ch_id = \"", ch_id, "\" ", "and ms_id = \"", ms_id, "\";", NULL};
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
