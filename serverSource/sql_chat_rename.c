#include "server.h"

char *chat_rename(MYSQL *con, char *ch_id, char *new_chat_name)
{
    const char *request_parts[] = {"update chat set ch_name = \"", new_chat_name, "\" where ch_id = \"", ch_id, "\";", NULL};
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
