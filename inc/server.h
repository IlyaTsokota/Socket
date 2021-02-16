#ifndef CHAT_H
#define CHAT_H

//std headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h> //experimental for variadic template
//ext libs headers
#include "json-c/json.h"
#include "mysql/mysql.h"
//our own headers
#include "server_structures.h"
#include <gmodule.h>
#include <sys/types.h>
#include <sys/stat.h>

//macros defines
#define array_init(a) (a).arr = NULL, (a).cnt = 0

void write_file(int sockfd, FILE *file);
char *get_filename_extension(char *filename);
char *sql_is_pin_equal_to_db_acc(MYSQL *con, char *my_id, char *pincode); //38
//socket_send_data
bool socket_send_data(char *data, int socket);

char *send_image(int sock, char *filename);

char *receive_img_to_profile(MYSQL *con, int socket, char *u_id, char *filename); //, char *chat_id, char *message_id)
//utilities
void recieve_image(int socket , char *path);

void array_clear(array_t *a);
int array_resize(array_t *a, size_t n);
void array_strtok(array_t *a, char *s, const char *delim);
char *strjoins_arr(const char **str_arr);
char *strjoin(int nHowMany, ...);
char **add_string(char **array, char *string);
char **init_array();
char *int_to_str(int n);
char *mx_strnew(const int size);
void mx_printint(int n);
void mx_printchar(char c);
char *itobase10(char *buf, int value);
char *set_date();

//free
void free_chat_s(chat_t *chat);
void free_message_s(message_t *message);
void free_contact_s(contact_t *contact);
void free_contact_info_s(contact_info_t *contact);
void free_user_s(user_t *user);
void free_validation_login_info_s(login_pin_info_t *message);
void free_message_back_info_s(message_back_info_t *user);
void free_validation_login_info2_s(login_pin_info_t2 *message);

//working with queries
array_t query_delimiter(char *str);
int get_query_number(char *line);
char *queries_handler(MYSQL *con, char **array, int sock);

//json
const char *write_chat_to_json(chat_t *chat);
const char *write_message_to_json(message_t *message);
const char *write_contact_to_json(contact_t *contact);
const char *write_user_to_json(user_t *user);
const char *write_contact_info_to_json(contact_info_t *contact);
const char *write_validation_login_info_to_json(login_pin_info_t *message);
const char *write_message_back_info_json(message_back_info_t *contact);
const char *write_validation_login_info_to_json2(login_pin_info_t2 *message);
array_t json_to_data(char *json_str);

//sql errors
void finish_with_error(MYSQL *con);

//sql-users
char *user_add(MYSQL *con, char *login, char *name, char *surname, char *password, char *pin, int sock); //03
char *get_my_id_no_answer(MYSQL *con, char *login, int close_con_after_end_of_func);                     //no answer 03
char *is_login_exist(MYSQL *con, char *login);                                                           //07
char *create_double_bottom(MYSQL *con, char *u_id, char *pin, int sock);                                 //23
char *delete_account(MYSQL *con, char *my_id);                                                           //24
char *get_user_info(MYSQL *con, char *user_id, int sock);                                                //20
char *get_user_info_by_login(MYSQL *con, char *login, int sock);                                         //36

//sql-chats
char *get_chats(MYSQL *con, char *user_id, int sock);                                                                                            //17
char *make_message_seen(MYSQL *con, char *ms_id);                                                                                                //15
char *group_chat_create(MYSQL *con, char *my_id, char *chat_name, char *is_return_data, int sock);                                               //06
char *chat_create(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func, char *is_return_data, int message_type, int sock); //08
char *chat_remove(MYSQL *con, char *chat_id);                                                                                                    //10

char *add_user_to_group_chat(MYSQL *con, char *login, char *ch_id);
char *chat_rename(MYSQL *con, char *ch_id, char *new_chat_name);  //29
char *get_chat_users(MYSQL *con, char *ch_id, int sock);          //30
char *remove_user_from_chat(MYSQL *con, char *u_id, char *ch_id); //31
char *is_user_chat_admin(MYSQL *con, char *ch_id, char *u_id);

//sql-validations
char *password_check(MYSQL *con, char *login, char *password); //01
char *pin_check(MYSQL *con, char *login, char *pin, int sock); //02

//sql-contacts
char *is_contact_exist(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func);          //11
char *contact_add(MYSQL *con, char *my_id, char *contact_id, int close_con_after_end_of_func);               //04
char *contact_remove(MYSQL *con, char *my_id, char *contact_id);                                             //05
char *contact_block(MYSQL *con, char *my_id, char *contact_id);                                              //09
char *contact_unblock(MYSQL *con, char *my_id, char *contact_id);                                            //14
char *get_contacts(MYSQL *con, char *user_id, int sock);                                                     //21
char *get_contact_info(MYSQL *con, char *contact_id, char *my_id, int sock);                                 //22
char *contact_add_by_login(MYSQL *con, char *login, char *my_id, int close_con_after_end_of_func, int sock); //35

//sql-credentials
char *change_password(MYSQL *con, char *u_id, char *new_pass); //27
char *change_pin(MYSQL *con, char *u_id, char *new_pin);       //28

//sql-message
char *get_messages(MYSQL *con, char *user_id, char *last_message_id, int sock);                                                                                              //16
char *add_message_to_chat(MYSQL *con, char *ch_id, char *user_id, char *ms_is_forwarded, char *ms_is_reply, char *ms_is_media, char *ms_data, int sock, int is_send_answer); //13
char *change_message(MYSQL *con, char *ch_id, char *ms_id, char *ms_text);                                                                                                   //33
char *delete_message(MYSQL *con, char *ch_id, char *ms_id);                                                                                                                  //34
char *add_first_message(MYSQL *con, char *my_id, char *c_id, int sock);                                                                                                      //37
//sql-unsorte
char *get_my_id(MYSQL *con, char *login, int close_con_after_end_of_func, int sock); //18
char *edit_profile(MYSQL *con, char *u_id, char *name, char *surname, char *quote);  //19
char *sql_update_chat_image(MYSQL *con, int socket, char *ch_id, char *filename); //39

//db-login-generator
char *pass_gen();
char *get_file7(FILE *file7, int line_no);
char *get_file6(FILE *file6, int line_no);
char *get_file5(FILE *file5, int line_no);
char *get_file4(FILE *file4, int line_no);
#endif
