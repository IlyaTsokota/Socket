#include "server.h"

char *contact_add_by_login(MYSQL *con, char *login, char *my_id, int close_con_after_end_of_func, int sock)
{
    //if_user_exitst
    char *answer;
    char *contact_id;
    const char *request_parts[] = {"SELECT COUNT(u_id), u_login FROM user WHERE  u_login = \"", login, "\";", NULL};
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

        answer = strdup(row[0]);
        contact_id = strdup(row[1]);
    }
    mysql_free_result(result);
    mysql_close(con);

    if (strcmp(answer, "0") == 0) //user doesn't exist
    {
        if (socket_send_data("2", sock))
        {
            free(answer);
            return strdup("1");
        }
        else
        {
            free(answer);
            return strdup("0");
        }
    }
    else
    {
        //if_user_in_my_contact_list
        const char *request_parts2[] = {"SELECT COUNT(c_id) FROM contacts WHERE  c_id = \"", contact_id, "\" and u_id = \"", my_id, "\";", NULL};

        bdrequest = strjoins_arr(request_parts2);
        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }

        free(bdrequest); //IR

        result = mysql_store_result(con);

        if (result == NULL)
        {
            finish_with_error(con);
        }

        num_fields = mysql_num_fields(result);

        while ((row = mysql_fetch_row(result)))
        {
            for (int i = 0; i < num_fields; i++)
            {
                answer = strdup(row[i]);
            }
        }
        mysql_free_result(result);
        mysql_close(con);

        if (strcmp(answer, "0") != 0) //contact exist
        {
            if (socket_send_data("1", sock))
            {
                free(answer);
                return strdup("1");
            }
            else
            {
                free(answer);
                return strdup("0");
            }
        }
        else
        {
            const char *request_parts3[] = {"INSERT INTO contacts (c_id, u_id, u_blocked) VALUES (\"", my_id, "\",\"", contact_id, "\",\"0\");", NULL};
            free(contact_id);
            bdrequest = strjoins_arr(request_parts3);

            puts(bdrequest); //Вывод запроса в консоль

            if (mysql_query(con, bdrequest))
            {
                finish_with_error(con);
            }
            if (close_con_after_end_of_func == 1)
            {
                mysql_close(con);
            }
            free(bdrequest); //IR
        }
    }
    return strdup("1");
}
