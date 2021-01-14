#include "server.h"

char *get_chats(MYSQL *con, char *user_id, int sock)
{
    char *answer;
    ///char *bdrequest = strjoins("SET @OPO = \"", user_id);
    char *bdrequest = strjoins("SELECT ch.ch_id, ch.ch_name, ch.ch_avatar, IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_login from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"", user_id);
    bdrequest = strjoins(bdrequest, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_lastSeen from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"");
    bdrequest = strjoins(bdrequest, user_id);
    bdrequest = strjoins(bdrequest, "\"and a.ch_id = ch.ch_id)), IF(STRCMP(ch.ch_name, \"personal_chat\"), \"0\", (select b.u_avatar from chatusers a join user b on b.u_id = a.u_id where a.u_id != \"");
    bdrequest = strjoins(bdrequest, user_id);
    bdrequest = strjoins(bdrequest, "\" and a.ch_id = ch.ch_id))\
    from chat ch\
    join chatusers cu on ch.ch_id = cu.ch_id\
    where cu.u_id = \"");
    bdrequest = strjoins(bdrequest, user_id);
    bdrequest = strjoins(bdrequest, "\" ;");

   // puts(bdrequest); //Вывод запроса в консоль

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
    chat_t *chat = NULL;
    // int length = 0;
    // while ((row = mysql_fetch_row(result))){
    //     length++;
    // }
    // //write(sock, int_to_str(length), strlen(int_to_str(length)));
    //  puts("gg1");
    // puts(int_to_str(length));
    while ((row = mysql_fetch_row(result)))
    {
        puts("gg");
        chat = (chat_t *)malloc(sizeof(chat_t));
        chat->ch_id = mx_strnew(strlen(row[0]));
        strcpy(chat->ch_id, row[0]);
        chat->ch_name = mx_strnew(strlen(row[1]));
        strcpy(chat->ch_name, row[1]);
        chat->ch_avatar = mx_strnew(strlen(row[2]));
        strcpy(chat->ch_avatar, row[2]);
        chat->u_login = mx_strnew(strlen(row[3]));
        strcpy(chat->u_login, row[3]);
        chat->u_lastSeen = mx_strnew(strlen(row[4]));
        strcpy(chat->u_lastSeen, row[4]);
        chat->u_avatar = mx_strnew(strlen(row[5]));
        strcpy(chat->u_avatar, row[5]);
      //write(sock, write_chat_to_json(chat), strlen(write_chat_to_json(chat)));
       puts(write_chat_to_json(chat));
        free_chat_s(chat);
    }

    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
