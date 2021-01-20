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
    char *file_name = strjoins(user_id, "_chats.json");
    FILE *json = fopen(file_name, "a");
    int size, read_size, stat, packet_index;
    char send_buffer[10240], read_buffer[256];
    fputs("{\"chats\": [", json);
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
        if (json != NULL)
        {
            fputs(tmp_str, json);
            fputs(",", json);
        }
        free((void *)tmp_str);
        free_chat_s(chat);
    }
    fputs("]}", json);
    
    puts("GG1");
    // find size file
    fseek(json, 0, SEEK_END);
    size = ftell(json);
    fseek(json, 0, SEEK_SET);
   
    puts("GG2");
    //send size
    puts(int_to_str(size));
    write(sock, (void *)&size, sizeof(int));
    puts("GG3");
    do
    {
        stat = read(sock, &read_buffer, 255);
    } while (stat < 0);
    puts("GG4");
    while (!feof(json))
    {
        read_size = fread(send_buffer, 1, sizeof(send_buffer) - 1, json);
        do
        {
            stat = write(sock, send_buffer, read_size);
        } while (stat < 0);
        // packet_index++;
        // bzero(send_buffer, sizeof(send_buffer));
    }
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
    remove(file_name);
    free(file_name);
    mysql_free_result(result);
    mysql_close(con);
    return "0"; //0 or >0
}
