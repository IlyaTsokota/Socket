#include "server.h"

char *change_pin(MYSQL *con, char *u_id, char *new_pin)
{
    char *encrypted_pin = crypt(new_pin, "1337_1488");

    const char *request_parts[] = {"update credentials set cr_pincode = \"", encrypted_pin, "\" where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR
    free(encrypted_pin);

    mysql_close(con);

    return strdup("1");;
}
