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

    //puts(bdrequest); //Вывод запроса в консоль
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
    json_t *query = (json_t *)malloc(sizeof(json_t));
    size_t  query_arr_length = 1024;
    query->arr = (char**)malloc(sizeof(char*) * query_arr_length);
    size_t length = 0;

    const char* tmp_str;
    while ((row = mysql_fetch_row(result)))
    {
        chat = (chat_t *)malloc(sizeof(chat_t));
        chat->ch_id = strdup(row[0]); //mx_strnew(strlen(row[0]));
        chat->ch_name = strdup(row[1]);//mx_strnew(strlen(row[1]));
        chat->ch_avatar = strdup(row[2]);//mx_strnew(strlen(row[2]));
        chat->u_login = strdup(row[3]);//mx_strnew(strlen(row[3]));
        chat->u_lastSeen = strdup(row[4]);//mx_strnew(strlen(row[4]));
        chat->u_avatar = strdup(row[5]);//mx_strnew(strlen(row[5]));
        tmp_str = write_chat_to_json(chat);
        //puts(strdup(tmp_str));
        query->arr[length] = strdup(tmp_str);
        
        free((void*)tmp_str);
        free_chat_s(chat);
        length++;
        if  (length == query_arr_length) {
            query_arr_length *= 2;
            query->arr = (char**)realloc(query->arr, sizeof(char*) * query_arr_length);
        }
    }
    query->arr[length] = NULL;
    
    char plug[3];
    char *num = int_to_str(length);
    write(sock, num, strlen(num));
    free(num);
    read(sock, plug, 2);
   
    for (size_t i = 0; i < length; i++)
    {
        puts(query->arr[i]);
        write(sock, query->arr[i], strlen(query->arr[i]));
        read(sock, plug, 2);
    }

    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
