#include "server.h"
//Создать чат
char *group_chat_create(MYSQL *con, char *my_id, char *chat_name)
{
    char *answer;

    char *bdrequest = strjoins("INSERT INTO chat (ch_name, ch_avatar) VALUES (\"", chat_name);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, "1234");
    bdrequest = strjoins(bdrequest, "\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    //Узнаём айди созданного чата
    bdrequest = "SELECT max(ch_id) from chat LIMIT 1;";
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
    //Добавить в чатюзерс юзера админа

    bdrequest = strjoins("INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", answer);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, my_id);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, "1");
    bdrequest = strjoins(bdrequest, "\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    mysql_close(con);

    return "1";
}
