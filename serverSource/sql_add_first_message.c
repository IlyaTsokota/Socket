#include <server.h>

char *add_first_message(MYSQL *con, char *my_id, char *c_id, int sock)
{
    char *ch_id;
    char *is_personal_chat_exist; //exist if =2 or >2

    const char *request_parts[] = {"select c.ch_id, count(c.ch_id) from chat c join chatusers  ch on c.ch_id = ch.ch_id where(ch.u_id = \"", my_id, "\" or ch.u_id = \"", c_id, "\") and c.ch_name = \"personal_chat\" group by 1 order by 2 desc limit 1", NULL};
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
            ch_id = strdup(row[0]);
            is_personal_chat_exist = strdup(row[1]);
        }
    }
    mysql_free_result(result);

    if (strcmp(is_personal_chat_exist, "2") == 0)
    {

        char *str, *tmp_str1;
        const char *tmp_str, *coma_str = ",";
        const char *request_parts[] = {"SELECT ch.ch_id, ch.ch_name, ch.ch_avatar, IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select concat(b.u_name, ' ', b.u_surname) from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_lastSeen from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_avatar from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"",
                                       my_id, "\" and a.ch_id = ch.ch_id)) from chat ch join chatusers cu on ch.ch_id = cu.ch_id where cu.u_id = \"", my_id, "\" and ch.ch_id = \"", ch_id, "\" ;", NULL};

        bdrequest = strjoins_arr(request_parts);

        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }
        free(ch_id);
        free(bdrequest); //IR

        result = mysql_store_result(con);

        if (result == NULL)
        {
            finish_with_error(con);
        }

        num_fields = mysql_num_fields(result);

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
        mysql_close(con);

        if (socket_send_data(str, sock))
        {
            return strdup("0");
        }
        else
        {
            return strdup("1");
        }
        return strdup("1");
        //---------------------
    }
    else
    {
        char *answ = chat_create(con, my_id, c_id, 0, "1", sock);
        puts("How");
        free(answ);
        free(ch_id);
    }
    puts("Ok1");

    mysql_close(con);
    puts("Ok");
    return strdup("1");
}
