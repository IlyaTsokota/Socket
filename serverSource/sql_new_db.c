#include "server.h"

char *create_double_bottom(MYSQL *con, char *u_id, char *pin)
{
    //Проверить нет ли у юзера даблботтома
    char *answer;
    char *name = "Socket";
    char *surname = "User";
    puts("GG");
    char *login = strdup("Pizda");
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
            answer = row[i];
        }
    }
    mysql_free_result(result);
    char *answer1 = strdup(answer); 
    puts(answer1);
    if (atoi(answer1) == 1){
        free(answer1);
        return "0";
        } //DB already exist
    free(answer1);

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
            answer = row[i];
        }
    }
    mysql_free_result(result);

    char *answer2 = strdup(answer); 
        puts(answer2);

    if (atoi(answer2) == 1){
    free(answer2);
        login = pass_gen(); }//Login already exist, try to create generate new login
    free(answer2);

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
            answer = row[i];
        }
    }
    char *answer3 = strdup(answer); 
    mysql_free_result(result);
    // mysql_close(con);

    //Добавить юзеру пароль и пин в креденшлс
    const char *request_parts4[] = {"INSERT INTO credentials (u_id, cr_password, cr_pincode) VALUES (\"", answer3, "\",\"", encrypted_password, "\",\"", encrypted_pin, "\");", NULL};
    bdrequest = strjoins_arr(request_parts4);
    free(answer3);

    puts(bdrequest);
    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    mysql_close(con);

    free(bdrequest); //IR
    free(datetime);  //IR

    return "1";
}
