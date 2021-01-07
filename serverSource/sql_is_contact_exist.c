#include <server.h>
char *is_contact_exist(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func)
{
    char *answer;

    char *bdrequest = strjoins("SELECT count(u_id) from contacts where c_id = \"", contact_id);
    bdrequest = strjoins(bdrequest, "\" and u_id = \"");
    bdrequest = strjoins(bdrequest, my_id);
    bdrequest = strjoins(bdrequest, "\";");
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

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    mysql_free_result(result);
    if(close_con_after_end_of_func==1)
    {
    mysql_close(con);
    }
    return answer; //0 or >0
}
