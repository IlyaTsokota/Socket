#include "server.h"

int get_query_number(char *line)
{
    return atoi(line);
}

char *queries_handler(MYSQL *con, char **array, int sock)
{
    int query_number = get_query_number(array[0]);
    switch (query_number)
    {
    case 1:
        puts("Query 01 -> password_check");
        return password_check(con, array[1], array[2]);
    case 2:
        puts("Query 02 -> pin_check");
        return pin_check(con, array[1], array[2]);
    case 3:
        puts("Query 03 -> user_add");
        return user_add(con, array[1], array[2], array[3], array[4], array[5]);
    case 4:
        puts("Query 04 -> contact_add");
        return contact_add(con, array[1], array[2], 1);
    case 5:
        puts("Query 05 -> contact_remove");
        return contact_remove(con, array[1], array[2]);
    case 6:
        puts("Query 06 -> group_chat_create");
        return group_chat_create(con, array[1], array[2]);
    case 7:
        puts("Query 07 -> is_login_exist");
        return is_login_exist(con, array[1]);
    case 8:
        puts("Query 08 -> chat_create");
        return chat_create(con, array[1], array[2]);
    case 9:
        puts("Query 09 -> contact_block");
        return contact_block(con, array[1], array[2]);
    case 10:
        puts("Query 10 -> chat_remove");
        return chat_remove(con, array[1]);
    case 11:
        puts("Query 11 -> is_contact_exist");
        return is_contact_exist(con, array[1], array[2], 1);
    case 12:
        puts("Query 12 -> add_user_to_group_chat");
        return add_user_to_group_chat(con, array[1], array[2]);
    case 13:
        puts("Query 13 -> add_message_to_chat");
        return add_message_to_chat(con, array[1], array[2], array[3], array[4], array[5], array[6]);
    case 14:
        puts("Query 14 -> contact_unblock");
        return contact_unblock(con, array[1], array[2]);
    case 15:
        puts("Query 15 -> make_message_seen");
        return make_message_seen(con, array[1]);
    case 16:
        puts("Query 16 -> get_messages");
        return get_messages(con, array[1], array[2], sock);
    case 17:
        puts("Query 17 -> get_chats");
        return get_chats(con, array[1], sock);

    // operator doesn't match any case
    default:
        puts("Server queries_handler default error");
        return "Server queries_handler default error";
    }
}
