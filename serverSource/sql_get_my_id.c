#include <server.h>

char *get_my_id(MYSQL *con, char *login, int close_con_after_end_of_func, int sock)
{
    char *answer;

    const char *request_parts[] = {"SELECT u_id from user where u_login = \"", login, "\" limit 1;", NULL};
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
            answer = strdup(row[i]);
        }
    }
    char *aanswer = strdup(answer); 
    if (socket_send_data(aanswer, sock)) {
        free(aanswer);
        return strdup("0");
    }
    else {
        free(aanswer);
        return strdup("1");
    }


    mysql_free_result(result);
    if (close_con_after_end_of_func == 1)
        mysql_close(con);
        
     return answer;
}
