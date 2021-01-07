#include "server.h"

char *add_user_to_group_chat(MYSQL *con, char *user_id, char *ch_id)
{
    char *answer;

    char *bdrequest = strjoins("SELECT count(u_id) from chatusers where u_id = \"", user_id);
    bdrequest = strjoins(bdrequest, "\" and ch_id = \"");
    bdrequest = strjoins(bdrequest, ch_id);
    bdrequest = strjoins(bdrequest, "\";");
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

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
    if (atoi(answer) == 1)
        return "0"; //user already exist in this chat

    //Добавить юзера
    bdrequest = strjoins("INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", ch_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, user_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, "0\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    return "1";
}
