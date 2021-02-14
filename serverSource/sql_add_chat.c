#include "server.h"
//Создать чат
char *chat_create(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func, char *is_return_data, int sock)
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
    char *chat_id = strdup(answer);
    mysql_free_result(result);
    //Добавить в чатюзерс юзера создавшего переписку
    const char *request_parts[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", chat_id, "\",\"", my_id, "\",\"0\");", NULL};
    bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR
    //Добавить в чатюзерс контакта
    const char *request_parts1[] = {"INSERT INTO chatusers (ch_id, u_id, ch_isadmin) VALUES (\"", chat_id, "\",\"", contact_id, "\",\"0\");", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    if (strcmp(is_return_data, "1") == 0)
    {
        puts("Here");
        char *str, *tmp_str1;
        const char *tmp_str, *coma_str = ",";
        const char *request_parts[] = {"SELECT ch.ch_id, ch.ch_name, ch.ch_avatar, IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select concat(b.u_name, ' ', b.u_surname) from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_lastSeen from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_avatar from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\" and a.ch_id = ch.ch_id)) from chat ch join chatusers cu on ch.ch_id = cu.ch_id where cu.u_id = \"", my_id, "\" and ch.ch_id = (select max(dfs.ch_id )from chat dfs) ;", NULL};
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

        chat_t *chat = NULL;

        str = strdup("{\"chats\": [");
        while ((row = mysql_fetch_row(result)))
        {
            chat = (chat_t *)malloc(sizeof(chat_t));
            chat->ch_id = strdup(row[0]);
            chat->ch_name = strdup(row[1]);
            chat->ch_avatar = strdup(row[2]);
            chat->u_login = strdup(row[3]);
            chat->u_lastSeen = strdup(row[4]);
            chat->u_avatar = strdup(row[5]);
            tmp_str = write_chat_to_json(chat);
            //
            tmp_str1 = strjoin(3, str, tmp_str, coma_str);
            free(str);
            str = tmp_str1;
            tmp_str1 = NULL;
            //
            free((void *)tmp_str);
            free_chat_s(chat);
        }
        str[strlen(str) - 1] = '\0';
        //
        tmp_str1 = strjoin(2, str, "]}");
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        //
        mysql_free_result(result);
        if (close_con_after_end_of_func == 1)
    {

        mysql_close(con);
    }

        if (socket_send_data(str, sock))
        {
            return strdup("0");
        }
        else
        {
            return strdup("1");
        }
        return strdup("1");
    }
    else
    {
        puts("Here111");
        add_message_to_chat(con, chat_id, "1", "0", "0", "0", "Добро пожаловать в Socket!\nЧувствуйте себя в безопасности.\nКаждое сообщение в Socket, как и это, надёжно зашифровано.\nSaved Messages необходим для файло-помойки, можешь отправлять мне всякий хлам ;)\n", sock, 0);
        free(chat_id);
        //отправить сообщение
    }

    if (close_con_after_end_of_func == 1)
    {

        mysql_close(con);
    }

 return strdup("1");
}
