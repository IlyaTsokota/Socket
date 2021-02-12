#include "server.h"

char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data, int sock, int is_send_answer)
{
    char *answer;

    const char *request_parts[] = {"select ch_name from chat ch join chatusers chu on ch.ch_id = chu.ch_id where chu.ch_id =\"", ch_id, "\" limit 1;", NULL};
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
            answer = strdup(row[i]);
        }
    }

    mysql_free_result(result);

    if (strcmp(answer, "personal_chat") != 0)
    {
        free(answer);
        char *date_time = set_date();
        const char *request_parts0[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"",
                                        ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\"", ms_data, "\");", NULL};
        bdrequest = strjoins_arr(request_parts0);

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
        free(answer);
        char *maxid;
        const char *request_parts2[] = {"select max(u_id) from chatusers where ch_id = \"", ch_id, "\";", NULL};
        bdrequest = strjoins_arr(request_parts2);

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
                maxid = strdup(row[i]);
            }
        }
        mysql_free_result(result);

        char *minid;

        const char *request_parts3[] = {"select min(u_id) from chatusers where ch_id = \"", ch_id, "\";", NULL};
        bdrequest = strjoins_arr(request_parts3);

        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }

        free(bdrequest); //IR
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
                minid = strdup(row[i]);
            }
        }
        mysql_free_result(result);

        char *answer3;

        const char *request_parts4[] = {"select count(u_blocked) from contacts where c_id = \"", minid, "\" and u_id =\"", maxid, "\" limit 1;", NULL};

        bdrequest = strjoins_arr(request_parts4);
        free(minid);
        free(maxid);
        puts(bdrequest); //Вывод запроса в консоль

        if (mysql_query(con, bdrequest))
        {
            finish_with_error(con);
        }

        free(bdrequest); //IR

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
                answer3 = strdup(row[i]);
            }
        }
        mysql_free_result(result);
        if (strcmp(answer3, "0") == 0)
        {
            char *string = strdup("1");
            if (is_send_answer == 1)
                socket_send_data(string, sock);
            free(answer3);
            return "1";
        }
        else
        {
            free(answer3);

            char *date_time = set_date();
            const char *request_parts7[] = {"INSERT INTO message (ch_id, u_id, ms_datetime, ms_isforwarded, ms_isreply, ms_isseen, ms_isedited, ms_ismedia, ms_text) VALUES (\"",
                                            ch_id, "\",\"", user_id, "\",\"", date_time, "\",\"", ms_is_forwarded, "\",\"", ms_is_reply, "\",\"0\",\"0\",\"", ms_is_media, "\",\"", ms_data, "\");", NULL};
            bdrequest = strjoins_arr(request_parts7);

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