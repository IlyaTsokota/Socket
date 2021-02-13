
#include "server.h"

char *change_message(MYSQL *con, char *ch_id, char *ms_id, char *ms_text)
{

    const char *request_parts[] = {"update message set ms_text = \"", ms_text, "\", ms_isedited = \"1\" where ch_id = \"", ch_id, "\" ", "and ms_id = \"", ms_id, "\";", NULL};
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
