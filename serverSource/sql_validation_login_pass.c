#include "server.h"

char *password_check(MYSQL *con, char *login, char *password)
{
    char *answer;
    char *encrypted_password = crypt(password, "1337_1488");
    char *bdrequest = strjoins("SELECT COUNT(user.u_id) FROM user Join credentials on credentials.u_id = user.u_id WHERE credentials.cr_password = \"", encrypted_password);
    bdrequest = strjoins(bdrequest, "\" AND user.u_login = \"");
    bdrequest = strjoins(bdrequest, login);
    bdrequest = strjoins(bdrequest, "\";");
    free(encrypted_password);
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

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    mysql_free_result(result);
    mysql_close(con);
    return answer; // 0 or >0
}
