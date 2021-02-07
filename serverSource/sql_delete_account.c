#include "server.h"
//Создать чат
char *delete_account(MYSQL *con, char *my_id)
{
    char *answer;
    //Добавить в чатюзерс юзера создавшего переписку
    const char *request_parts[] = {"update user set u_name = \"Deleted\", u_surname = \"Account\", u_avatar = \"1234\", u_status = \"I'm deleted account\", u_isBottommed = \"0\" where u_id = \"", my_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest); //IR
    //Добавить в чатюзерс контакта
    const char *request_parts1[] = { "update credentials set cr_password = \"Deleted\", cr_pincode = \"Deleted\" where u_id = \"", my_id, "\";", NULL};
    bdrequest = strjoins_arr(request_parts1);

    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }

    free(bdrequest); //IR

    mysql_close(con);

    return "1";
}
