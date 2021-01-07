#include "server.h"

char *user_add(MYSQL *con, char *login, char *name, char *surname, char *password, char *pin)
{
    //Проверить нет ли такого юзера   SELECT  count(u_login) from user where u_login = "itsokota"
    char *answer;
    char *status = "Status is empty ;c";
    char *isonline = "1";
    char *encrypted_password = crypt(password, "1337_1488");
    char *encrypted_pin= crypt(pin, "1337_1488");
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
    puts("LLL\n");
    puts(answer);
    if (atoi(answer) == 1)
        return "0"; //user already exist

    //Добавить юзера
    bdrequest =  strjoins("INSERT INTO user ( u_login, u_name, u_surname, u_status, u_isOnline, u_lastSeen, u_avatar) VALUES (\"", login);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, name);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, surname);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, status);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, isonline);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, set_date());
    bdrequest = strjoins(bdrequest, "\",\"1234\");");

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    //Узнать айди user
   bdrequest = strjoins("SELECT u_id from user where u_login = \"", login);
    bdrequest = strjoins(bdrequest, "\";");
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

    num_fields = mysql_num_fields(result);

    while ((row = mysql_fetch_row(result)))
    {
        for (int i = 0; i < num_fields; i++)
        {
            answer = row[i];
        }
    }
    mysql_free_result(result);
    // mysql_close(con);

    //Добавить юзеру пароль и пин в креденшлс
    bdrequest = strjoins("INSERT INTO credentials (u_id, cr_password, cr_pincode) VALUES (\"", answer);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, encrypted_password);
    bdrequest = strjoins(bdrequest, "\",\"");
    bdrequest = strjoins(bdrequest, encrypted_pin);
    bdrequest = strjoins(bdrequest, "\");");
    puts(bdrequest);
     if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
        mysql_close(con);

    return "1";
}
