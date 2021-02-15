#include <server.h>

char *sql_is_pin_equal_to_db_acc(MYSQL *con, char *my_id, char *pincode)
{
    char *answer;
    char *encrypted_pin = crypt(pincode, "1337_1488");
    //AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    const char *request_parts[] = {"select count(c.cr_pincode)  from credentials c where c.u_id = ( select u_id from user where u_isBottommed = \"", my_id, "\") and c.cr_pincode = \"", encrypted_pin, "\";", NULL};
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
            answer = row[i];
        }
    }
    mysql_free_result(result);
    mysql_close(con);

    return strdup(answer);
}
