#include "server.h"

char *contact_remove(MYSQL *con, char *my_id, char *contact_id)
{
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";

    char *bdrequest =  strjoins("delete from contacts where u_id=\"", my_id);
    bdrequest = strjoins(bdrequest, "\" and c_id=\"");
    bdrequest = strjoins(bdrequest, contact_id);
    bdrequest = strjoins(bdrequest, "\";");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
        mysql_close(con);

    return "1";
}
