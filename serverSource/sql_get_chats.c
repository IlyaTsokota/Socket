#include "server.h"

char *get_chats(MYSQL *con, char *user_id, int sock)
{
    char *answer, *str, *tmp_str1;
    const char *tmp_str, *coma_str = ",";
    const char *request_parts[] = {"SELECT ch.ch_id, ch.ch_name, ch.ch_avatar, IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_login from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"", 
        user_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_lastSeen from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"", 
        user_id, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_avatar from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"", 
        user_id, "\" and a.ch_id = ch.ch_id)) from chat ch join chatusers cu on ch.ch_id = cu.ch_id where cu.u_id = \"", user_id, "\" ;", NULL};
    char *bdrequest = strjoins_arr(request_parts);

    //puts(bdrequest); //Вывод запроса в консоль

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
    mysql_close(con);
    //
    if (socket_send_data(str, sock)) {
        return "0";
    }
    else {
        return "1";
    }
    return "1"; //0 or >0
}
