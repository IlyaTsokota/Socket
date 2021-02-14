#include "server.h"

int get_query_number(char *line)
{
    return atoi(line);
}

char *queries_handler(MYSQL *con, char **array, int sock)
{
    int query_number = get_query_number(array[0]);
    printf("%d -- index\n", query_number);
    puts(array[0]);
        puts(array[1]);
    puts(array[2]);

    switch (query_number)
    {
    case 1:
        puts("Query 01 -> password_check");
        return password_check(con, array[1], array[2]);
    case 2:
        puts("Query 02 -> pin_check");
        return pin_check(con, array[1], array[2], sock);
    case 3:
        puts("Query 03 -> user_add");
        return user_add(con, array[1], array[2], array[3], array[4], array[5], sock);
    case 4:
        puts("Query 04 -> contact_add");
        return contact_add(con, array[1], array[2], 1);
    case 5:
        puts("Query 05 -> contact_remove");
        return contact_remove(con, array[1], array[2]);
    case 6:
        puts("Query 06 -> group_chat_create");
        return group_chat_create(con, array[1], array[2], "1", sock);
    case 7:
        puts("Query 07 -> is_login_exist");
        return is_login_exist(con, array[1]);
    case 8:
        puts("Query 08 -> chat_create");
        return chat_create(con, array[1], array[2], 1, "1", sock);
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
        return add_message_to_chat(con, array[1], array[2], array[3], array[4], array[5], array[6], sock, 1);
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
    case 18:
        puts("Query 18 -> get_my_id");
        return get_my_id(con, array[1], 1, sock);
    case 19:
        puts("Query 19 -> edit_profile");
        return edit_profile(con, array[1], array[2], array[3], array[4]);
    case 20:
        puts("Query 20 -> profile_info");
        return get_user_info(con, array[1], sock);
    case 21:
        puts("Query 21 -> get_contacts");
        return get_contacts(con, array[1], sock);
    case 22:
        puts("Query 22 -> get_contact_info");
        return get_contact_info(con, array[1], array[2], sock);
    case 23:
        puts("Query 23 -> create_double_bottom");
        return create_double_bottom(con, array[1], array[2]);
    case 24:
        puts("Query 24 -> delete_account");
        return delete_account(con, array[1]);
    case 25:
        puts("Query 25 -> recieve image");
        return receive_image(sock, array[1], array[2]);
    case 26:
        puts("Query 26 -> send_image");
        return send_image(sock, array[1], array[2]);
    case 27:
        puts("Query 27 -> change_password");
        return change_password(con, array[1], array[2]);
    case 28:
        puts("Query 28 -> change_pin");
        return change_pin(con, array[1], array[2]);
    case 29:
        puts("Query 29 -> chat_rename");
        return chat_rename(con, array[1], array[2]);
    case 30:
        puts("Query 30 -> get_chat_users");
        return get_chat_users(con, array[1], sock);
    case 31:
        puts("Query 31 -> remove_user_from_chat");
        return remove_user_from_chat(con, array[1], array[2]);
    case 32:
        puts("Query 32 -> get_chat_is_user_chat_adminusers");
        return is_user_chat_admin(con, array[1], array[2]);
    case 33:
        puts("Query 33 -> change_message");
        return change_message(con, array[1], array[2], array[3]);
    case 34:
        puts("Query 34 -> delete_message");
        return delete_message(con, array[1], array[2]);
    case 35:
        puts("Query 35 -> contact_add_by_login");
        return contact_add_by_login(con, array[1], array[2], 1 ,sock);
   case 36:
        puts("Query 36 -> get_user_info_by_login");
        return get_user_info_by_login(con, array[1],sock);
   case 37:
        puts("Query 37 -> add_first_message");
        return add_first_message(con, array[1],array[2],sock);

    default:
        puts("Server queries_handler default error");
        return "Server queries_handler default error";
    }
}
