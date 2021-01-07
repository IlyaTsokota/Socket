#include "server.h"

char *chat_remove(MYSQL *con, char *chat_id)
{
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";

    char *bdrequest = strjoins("delete from message where ch_id=\"", chat_id);
    bdrequest = strjoins(bdrequest, "\";");
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    bdrequest = strjoins("delete from chatusers where ch_id=\"", chat_id);
    bdrequest = strjoins(bdrequest, "\";");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    bdrequest = strjoins("delete from chat where ch_id=\"", chat_id);
    bdrequest = strjoins(bdrequest, "\";");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    return "1";
}
