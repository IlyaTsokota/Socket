#include "server.h"

char *contact_add(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func)
{
    char *answer;

    char *bdrequest = strjoins("INSERT INTO contacts (c_id, u_id, u_blocked) VALUES (\"", my_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, contact_id);
    bdrequest = strjoins(bdrequest, "\",\"0\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    if (close_con_after_end_of_func == 1)
    {
        mysql_close(con);
    }

    return "1";
}
