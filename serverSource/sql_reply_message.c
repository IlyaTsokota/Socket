
#include "server.h"

char *reply_message(MYSQL *con, char *ms_id, char *reply_to_ch_id)
{
    char *date_time = set_date();
    const char *request_parts[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) select \"", reply_to_ch_id, "\", u_id,(select c.ms_datetime from message c where \
    c.ms_id = \"",
                                   ms_id, "\"), \"0\", \"1\", \"0\", \"0\",(select b.ms_ismedia from message b where b.ms_id = \"", ms_id, "\"),(select h.ms_text from message h where h.ms_id = \"", ms_id, "\") from message where ms_id = \"", ms_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    mysql_close(con);

    return strdup("1");
}
