#ifndef CHAT_H
#define CHAT_H

#include "mysql/mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include "json-c/json.h"

typedef struct
{
    char **arr;
    size_t cnt;
} array_t;

typedef struct
{
    char *ch_id;
    char *ch_name;
    char *ch_avatar;
    char *u_login;
    char *u_lastSeen;
    char *u_avatar;
} chat_t;

#define array_init(a) (a).arr = NULL, (a).cnt = 0
void array_clear(array_t *a);
int array_resize(array_t *a, size_t n);
void array_strtok(array_t *a, char *s, const char *delim);
void free_chat_s(chat_t *chat);
char *strjoins(const char *s1, const char *s2);
char **add_string(char **array, char *string);
char **init_array();
char* int_to_str(int n);

//working with queries
array_t query_delimiter(char *str);
int get_query_number(char *line);
char *queries_handler(MYSQL *con, char **array, int sock);

//json
char *write_chat_to_json(chat_t *chat);

array_t json_to_data(char *json_str);

//sql errors
void finish_with_error(MYSQL *con);

//sql-users
char *user_add(MYSQL *con, char *login, char *name, char *surname, char *password, char *pin); //03
char *is_login_exist(MYSQL *con, char *login);                                                 //07
//sql-chats
char *get_chats(MYSQL *con, char *user_id, int sock);              //17
char *make_message_seen(MYSQL *con, char *ms_id);                     //15
char *chat_create(MYSQL *con, char *my_id, char *contact_id);         //08
char *group_chat_create(MYSQL *con, char *my_id, char *chat_name);    //06
char *chat_remove(MYSQL *con, char *chat_id);                         //10
char *add_user_to_group_chat(MYSQL *con, char *user_id, char *ch_id); //12
//sql-validations
char *password_check(MYSQL *con, char *login, char *password); //01
char *pin_check(MYSQL *con, char *login, char *pin);           //02
//sql-contacts
char *is_contact_exist(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func); //11
char *contact_add(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func);      //04
char *contact_remove(MYSQL *con, char *my_id, char *contact_id);                                    //05
char *contact_block(MYSQL *con, char *my_id, char *contact_id);                                     //09
char *contact_unblock(MYSQL *con, char *my_id, char *contact_id);                                   //14
//sql-message
char *get_messages(MYSQL *con, char *user_id, char *last_message_id);                                                                          //16
char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data); //13

char *mx_strnew(const int size);
void mx_printint(int n);
void mx_printchar(char c);
char *itobase10(char *buf, int value);
char *set_date();

#endif
