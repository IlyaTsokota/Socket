#include "server.h"

char *create_double_bottom(MYSQL *con, char *u_id, char *pin, int sock)
{
    //Проверить нет ли у юзера даблботтома
    char *answer;
    char *name = "Socket";
    char *surname = "User";
    puts("GG");
    const char *request_parts228[] = {u_id, pin, NULL};
    char *login = crypt(strjoins_arr(request_parts228), "1337_1488");

    //char *login = strdup("Pizda");
    // pass_gen();
    puts("GG2");
    char *status = "Status is empty ;c";
    char *encrypted_password = crypt("A8t050t3_t32M", "1337_1488");
    char *encrypted_pin = crypt(pin, "1337_1488");
    char *datetime = set_date();
    const char *request_parts[] = {"SELECT count(u_id) from user where u_isBottommed !=0 and u_id = \"", u_id, "\";", NULL};
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
        for (int i = 0; i < num_fields; i++)
        {
            answer = strdup(row[i]);
        }
    }
    mysql_free_result(result);
    if (atoi(answer) == 1)
    {
        free(answer);
        return strdup("0");
    } //DB already exist
    free(answer);

    const char *request_parts1[] = {"SELECT count(u_login) from user where u_login = \"", login, "\";", NULL};
    bdrequest = strjoins_arr(request_parts1);

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
        for (int i = 0; i < num_fields; i++)
        {
            answer = strdup(row[i]);
        }
    }
    mysql_free_result(result);

    if (atoi(answer) == 1)
    {
        free(answer);
        login = crypt(strjoins_arr(request_parts228), "1337_1488");
    } //Login already exist, try to create generate new login
    free(answer);

    //Добавить юзеру DB
    const char *request_parts2[] = {"INSERT INTO user (u_login, u_name, u_surname, u_status, u_isBottommed, u_lastSeen, u_avatar) VALUES (\"", login, "\",\"",
                                    name, "\",\"", surname, "\",\"", status, "\",\"", u_id, "\",\"", datetime, "\",\"1234\");", NULL};
    bdrequest = strjoins_arr(request_parts2);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    //Узнать айди user
    const char *request_parts3[] = {"SELECT u_id from user where u_login = \"", login, "\";", NULL};
    bdrequest = strjoins_arr(request_parts3);
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
        for (int i = 0; i < num_fields; i++)
        {
            answer = strdup(row[i]);
        }
    }
    mysql_free_result(result);
    // mysql_close(con);

    //Добавить юзеру пароль и пин в креденшлс
    const char *request_parts4[] = {"INSERT INTO credentials (u_id, cr_password, cr_pincode) VALUES (\"", answer, "\",\"", encrypted_password, "\",\"", encrypted_pin, "\");", NULL};
    bdrequest = strjoins_arr(request_parts4);
    free(answer);

    puts(bdrequest);
    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    //Добавить юзеру Saved Messages в контакты
    chat_create(con, answer, "1", 0, "0", 2, sock);

    mysql_close(con);

    free(bdrequest); //IR
    free(datetime);  //IR

    return strdup("1");
}
