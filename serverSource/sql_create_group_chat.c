#include "server.h"
//Создать чат
char *group_chat_create(MYSQL *con, char *my_id, char *chat_name)
{
    char *answer;

    const char *request_parts[] = {"INSERT INTO chat (ch_name, ch_avatar) VALUES (\"", chat_name, "\",\"1234\");", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR
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
            answer = strdup(row[i]);
        }
    }
    mysql_free_result(result);
    //Добавить в чатюзерс юзера админа
    const char *request_parts1[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", answer, "\",\"", my_id, "\",\"1\");", NULL};
    bdrequest = strjoins_arr(request_parts1);
    free(answer);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    mysql_close(con);
    free(bdrequest); //IR
    return "1";
}
