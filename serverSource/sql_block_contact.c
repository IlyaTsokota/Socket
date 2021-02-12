#include "server.h"

char *contact_block(MYSQL *con, char *my_id, char *contact_id)
{
    char *answer;
    if (atoi(is_contact_exist(con, my_id, contact_id,0)) == 0)
    {
        contact_add(con, contact_id, my_id,0);
    }
    const char *request_parts[] = {"UPDATE contacts SET u_blocked = \"1\" WHERE u_id = \"", my_id, "\" and c_id = \"", contact_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);
    free(bdrequest); //IR
    return "1";
}
