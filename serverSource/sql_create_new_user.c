#include "server.h"

char *user_add(MYSQL *con, char *login, char *name, char *surname, char *password, char *pin, int sock)
{
    //Проверить нет ли такого юзера   SELECT  count(u_login) from user where u_login = "itsokota"
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";
    char *encrypted_password = crypt(password, "1337_1488");
    char *encrypted_pin = crypt(pin, "1337_1488");
    char *datetime = set_date();
    const char *request_parts[] = {"SELECT count(u_login) from user where u_login = \"", login, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);

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

    while ((row = mysql_fetch_row(result)))
    {
        answer = strdup(row[0]);
    }
    mysql_free_result(result);
    puts("LLL\n");
    puts(answer);
    if (atoi(answer) == 1) {
        free(answer);
       return strdup("0");
    }
    free(answer);
    //Добавить юзера
    const char *request_parts1[] = {"INSERT INTO user ( u_login, u_name, u_surname, u_status, u_isBottommed, u_lastSeen, u_avatar) VALUES (\"", login, "\",\"",
                                    name, "\",\"", surname, "\",\"", status, "\",\"", isonline, "\",\"", datetime, "\",\"1234\");", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    //Узнать айди user
    const char *request_parts2[] = {"SELECT u_id from user where u_login = \"", login, "\";", NULL};
    bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    result = mysql_store_result(con);

    if (result == NULL)
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        answer = strdup(row[0]);
    }
    puts(answer);
    mysql_free_result(result);

    //Добавить юзеру пароль и пин в креденшлс
    const char *request_parts3[] = {"INSERT INTO credentials (u_id, cr_password, cr_pincode) VALUES (\"", answer, "\",\"", encrypted_password, "\",\"", encrypted_pin, "\");", NULL};
    bdrequest = strjoins_arr(request_parts3);

    puts(bdrequest);

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    //Добавить юзеру Saved Messages в контакты
    chat_create(con, answer, "1", 0, "0", sock);
    
    mysql_close(con);
    free(answer); //IR
    free(bdrequest); //IR
    free(datetime);  //IR

   return strdup("1");
}
