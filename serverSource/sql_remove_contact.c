#include "server.h"

char *contact_remove(MYSQL *con, char *my_id, char *contact_id)
{
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";


    const char *request_parts[] = {"delete from contacts where u_id=\"", my_id, "\" and c_id=\"", contact_id, "\";", NULL};
    char *bdrequest =  strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    
    free(bdrequest); //IR

    mysql_close(con);
    return strdup("1");;
}
