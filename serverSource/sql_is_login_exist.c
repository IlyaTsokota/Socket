#include <server.h>
char *is_login_exist(MYSQL *con, char *login)
{
    char *answer;
    // char *date = set_date();

    char *bdrequest = strjoins("SELECT count(u_login) from user where u_login = \"", login);
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
     mysql_close(con);
    
    return answer; //0 or >0
}
