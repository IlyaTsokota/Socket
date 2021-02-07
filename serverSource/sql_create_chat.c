#include "server.h"
//Создать чат
char *chat_create(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func)
{
    char *answer;

    char *bdrequest = "INSERT INTO chat (ch_name, ch_avatar) VALUES (\"personal_chat\",\"no_avatar\");";
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
    //Добавить в чатюзерс юзера создавшего переписку
    const char *request_parts[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", answer, "\",\"", my_id, "\",\"0\");", NULL};
    bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR
    //Добавить в чатюзерс контакта
    const char *request_parts1[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", answer, "\",\"", contact_id, "\",\"0\");", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    if (close_con_after_end_of_func == 1)
    {
        mysql_close(con);
    }

    return "1";
}
