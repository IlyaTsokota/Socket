#include "server.h"

char *contact_add(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func)
{
    char *answer;
    const char *request_parts[] = {"INSERT INTO contacts (u_id, c_id, u_blocked) VALUES (\"", my_id, "\",\"", contact_id, "\",\"0\");", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    if (close_con_after_end_of_func == 1)
    {
        mysql_close(con);
    }
    free(bdrequest); //IR
    return strdup("1");
}
