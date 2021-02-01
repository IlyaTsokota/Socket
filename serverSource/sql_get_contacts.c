#include "server.h"

char *get_contacts(MYSQL *con, char *user_id, int sock)
{
    char *answer;
    const char *request_parts[] = {"select c.c_id, concat(u.u_surname, ' ', u.u_name), u.u_avatar, u.u_status, u.u_lastSeen \
    from contacts c \
    join user u \
    on c.c_id = u.u_id \
    where c.u_id = \"",
    user_id, "\" ;", NULL};

    char *bdrequest = strjoins_arr(request_parts);

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
    free(bdrequest); //IR
    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    contact_t *contact = NULL;
    json_t *query = (json_t *)malloc(sizeof(json_t));
    size_t query_arr_length = 1024;
    query->arr = (char **)malloc(sizeof(char *) * query_arr_length);
    size_t length = 0;

    const char *tmp_str;
    while ((row = mysql_fetch_row(result)))
    {
        contact = (contact_t *)malloc(sizeof(contact_t));
        contact->c_id = strdup(row[0]);       //mx_strnew(strlen(row[0]));
        contact->u_name = strdup(row[1]);     //mx_strnew(strlen(row[1]));
        contact->u_avatar = strdup(row[2]);   //mx_strnew(strlen(row[3]));
        contact->u_status = strdup(row[3]);   //mx_strnew(strlen(row[4]));
        contact->u_lastSeen = strdup(row[4]); //mx_strnew(strlen(row[4]));

        tmp_str = write_contact_to_json(contact);
        //puts(strdup(tmp_str));
        query->arr[length] = strdup(tmp_str);

        free((void *)tmp_str);
        free_contact_s(contact);
        length++;
        if (length == query_arr_length)
        {
            query_arr_length *= 2;
            query->arr = (char **)realloc(query->arr, sizeof(char *) * query_arr_length);
        }
    }
    query->arr[length] = NULL;

    char plug[3];
    write(sock, int_to_str(length), strlen(int_to_str(length)));
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
