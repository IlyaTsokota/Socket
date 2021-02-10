#include "server.h"

char *get_contacts(MYSQL *con, char *user_id, int sock)
{
    const char *tmp_str, *coma_str = ",";
    char *str, *bdrequest, *tmp_str1;
    const char *request_parts[] = {"select c.c_id, concat(u.u_name, ' ', u.u_surname), u.u_avatar, u.u_status \
    from contacts c \
    join user u \
    on c.c_id = u.u_id \
    where c.u_id = \"",
    user_id, "\" ;", NULL};

    bdrequest = strjoins_arr(request_parts);

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
    free(bdrequest); //IR
    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    contact_t *contact = NULL;

    str = strdup("{\"contacts\": [");

    while ((row = mysql_fetch_row(result)))
    {
        contact = (contact_t *)malloc(sizeof(contact_t));
        contact->c_id = strdup(row[0]);       //mx_strnew(strlen(row[0]));
        contact->u_name = strdup(row[1]);     //mx_strnew(strlen(row[1]));
        contact->u_avatar = strdup(row[2]);   //mx_strnew(strlen(row[3]));
        contact->u_status = strdup(row[3]);   //mx_strnew(strlen(row[4]));

       tmp_str = write_contact_to_json(contact);
        tmp_str1 = strjoin(3, str, tmp_str, coma_str);
        free(str);
        str = tmp_str1;
        tmp_str1 = NULL;
        free((void *)tmp_str);
        free_contact_s(contact);
    }
    str[strlen(str) - 1] = '\0';
    tmp_str1 = strjoin(2, str, "]}");
    free(str);
    str = tmp_str1;
    tmp_str1 = NULL;
    //
    puts(str);
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
