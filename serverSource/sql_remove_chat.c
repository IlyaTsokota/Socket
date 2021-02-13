#include "server.h"

char *chat_remove(MYSQL *con, char *chat_id)
{
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";

    const char *request_parts[] = {"Delete from message where ch_id=\"", chat_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    const char *request_parts1[] = {"delete from chatusers where ch_id=\"", chat_id, "\";", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    const char *request_parts2[] = {"delete from chat where ch_id=\"", chat_id, "\";", NULL};
    bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    mysql_close(con);

    return strdup("1");;
}
