#include "server.h"

char *edit_profile(MYSQL *con, char* u_id, char* name, char* surname, char*quote)
{
    const char *request_parts[] = {"UPDATE user SET u_name = \"", name, "\", u_surname = \"", surname, "\", u_status = \"", quote, "\" where u_id =\"", u_id ,"\";", NULL};
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
