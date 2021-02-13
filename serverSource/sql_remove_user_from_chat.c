#include "server.h"

char *remove_user_from_chat(MYSQL *con, char *u_id)
{
    const char *request_parts[] = {"delete from chatusers where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR

    mysql_close(con);

    return strdup("1");;
}
