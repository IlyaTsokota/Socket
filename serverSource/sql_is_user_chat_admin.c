#include <server.h>
char *is_user_chat_admin(MYSQL *con, char *ch_id, char *u_id)
{
    char *answer;

    const char *request_parts[] = {"select ch_isadmin from chatusers where u_id = ", u_id, "\" and ch_id =  \"", ch_id, "\" limit 1;", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    mysql_free_result(result);
    mysql_close(con);

    return answer; //0 or >0
}
