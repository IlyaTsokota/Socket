#include "server.h"

char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data, int sock)
{
    char *answer;

    const char *request_parts[] = {"select count(u_id) from chatusers where ch_id =\"", ch_id, "\";", NULL};
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
    if (strcmp(answer, "2") != 0)
    {
        char *date_time = set_date();
        const char *request_parts[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"",
                                       ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\"", ms_data, "\");", NULL};
        char *bdrequest = strjoins_arr(request_parts);

        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }
        mysql_close(con);

        free(date_time); //IR
        free(bdrequest); //IR
        char *str = strdup("1");
        if (socket_send_data(str, sock))
        {
            return "0";
        }
        else
        {
            return "1";
        }
    }
    else
    {
        char *maxid;

        const char *request_parts2[] = {"select max(u_id) from chatusers where ch_id = \"", ch_id, "\";", NULL};
        char *bdrequest2 = strjoins_arr(request_parts2);

        puts(bdrequest2); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }

        free(bdrequest2); //IR

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
                maxid = row[i];
            }
        }
        mysql_free_result(result);

        char *minid;

        const char *request_parts3[] = {"select max(u_id) from chatusers where ch_id = \"", ch_id, "\";", NULL};
        char *bdrequest3 = strjoins_arr(request_parts3);

        puts(bdrequest3); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest3))
        {
            finish_with_error(con);
        }

        free(bdrequest3); //IR

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
                minid = row[i];
            }
        }
        mysql_free_result(result);

        char *answer3;

        const char *request_parts4[] = {"select count(u_blocked) from contacts where c_id = \"", minid, "and u_id =\"", maxid, "\"limit 1;", NULL};

        char *bdrequest4 = strjoins_arr(request_parts4);

        puts(bdrequest4); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest4))
        {
            finish_with_error(con);
        }

        free(bdrequest4); //IR

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
                answer3 = row[i];
            }
        }
        mysql_free_result(result);
        if (strcmp(answer3, "0") != 0)
        {
            return "1";
        }
        else
        {
            char *date_time = set_date();
            const char *request_parts[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"",
                                           ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\"", ms_data, "\");", NULL};
            char *bdrequest = strjoins_arr(request_parts);

            puts(bdrequest); //Вывод запроса в консоль

            if (mysql_query(con, bdrequest))
            {
                finish_with_error(con);
            }
            mysql_close(con);

            free(date_time); //IR
            free(bdrequest); //IR
            char *str = strdup("1");
            if (socket_send_data(str, sock))
            {
                return "0";
            }
            else
            {
                return "1";
            }
        }
    }

    return "1";
}