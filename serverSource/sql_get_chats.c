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

    // free(bdrequest);

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    chat_t *chat = NULL;

    const char *tmp_str;
    int size, read_size, stat, packet_index;
    char  read_buffer[256];
    puts("PZDC");
    char *str = mx_strnew(0);
    str = strjoins(str,"{\"chats\": [" );
        puts("PZDC1");

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
        //write to file
        str = strjoins(str,tmp_str);
        str = strjoins(str,",");
        free((void *)tmp_str);
        free_chat_s(chat);
        puts(str);
    }
    str[strlen(str) - 1] = '\0';
    str = strjoins(str,"]}");
    puts(str);
    puts("GG1");
    size = strlen(str);
    puts("GG2");
    puts(int_to_str(size));
    write(sock, (void *)&size, sizeof(int));
    puts("GG3");
    ssize_t packet_size = 1024;
    ssize_t packet_count = 0;
    do {
            stat = write(sock, str, ((packet_count + 1) * packet_size));
            packet_count++;
    } while (stat < 0);
    puts("GG5");
    // char plug[3];
    // char *num = int_to_str(length);
    // write(sock, num, strlen(num));
    // free(num);
    // read(sock, plug, 2);

    // for (size_t i = 0; i < length; i++)
    // {
    //     puts(query->arr[i]);
    //     write(sock, query->arr[i], strlen(query->arr[i]));
    //     read(sock, plug, 2);
    // }
     // fclose(json);
    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
