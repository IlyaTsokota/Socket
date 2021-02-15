#include "server.h"

char *change_password(MYSQL *con, char *u_id, char *new_pass)
{
    char *encrypted_pass = crypt(new_pass, "1337_1488");

    const char *request_parts[] = {"update credentials set cr_password = \"", encrypted_pass, "\" where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR

    mysql_close(con);

   return strdup("1");
}
