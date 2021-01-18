#ifndef CHAT_H
#define CHAT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <locale.h>
#include <wctype.h>
#include "json-c/json.h"
#include <fcntl.h>
#include <gio/gio.h>
#include <pthread.h>

typedef struct
{
	GtkWidget *grid;
	GtkWidget *btn_container;
	GtkWidget *btn;
	GtkWidget *spinner;
} cur_grid_t;

typedef struct
{
	cur_grid_t *current_grid;
	char *login;
	char *password;
} auth_check_t;

typedef struct
{
	GtkWidget *event_box_contact;
	GtkWidget *contact_container;
	GtkWidget *time_last_message;
	GtkWidget *login_last_message;
	GtkWidget *text_last_message;
	GtkWidget *contact_name_lable;
	GtkWidget *user_is_online;
	GtkWidget *contact_info;
	GtkWidget *contact_last_msg;
	GtkWidget *contact_name_container;
	GtkWidget *img_contact;
	GtkWidget *contact_img_container;
} chat_item_t;

typedef struct
{
	GtkWidget *login;
	GtkWidget *name;
	GtkWidget *surname;
	GtkWidget *password;
	GtkWidget *pin;
	GtkWidget *fail_login;
	GtkWidget *fail_name;
	GtkWidget *fail_surname;
	GtkWidget *fail_password;
	GtkWidget *fail_pin;

	char *login_text;
	char *name_text;
	char *surname_text;
} register_w;

register_w registration;

typedef struct pin_f
{
	GtkWidget *pin_form;
	GtkWidget *pin;
	GtkWidget *fail_pin;
} pin_t;

typedef struct msg_i
{
	GtkWidget *text_view;
	GtkWidget *container;
	GtkTextBuffer *buffer;
} msg_t;

typedef struct
{
	GtkWidget *login;
	GtkWidget *password;
	GtkWidget *fail_login;
	GtkWidget *fail_password;
	GtkWidget *fail_auth;
	char *login_text;
	
} autorization_w;

autorization_w autorization;

typedef struct
{
	GtkApplication *restrict app;
	GtkWidget *restrict win;
	int socket_desc;
} appdata;

appdata data;

typedef struct
{
	GtkWidget *left_content;
	GtkWidget *right_content;
	GtkWidget *main_grid;
	GtkWidget *chats_grid;
} main_form_t;

typedef struct
{
	GtkWidget *setting;
	GtkWidget *contact;
	GtkWidget *chat;
	GtkWidget *lock;
} left_panel_img_t;

typedef struct
{
	char *ch_id;
	char *ch_name;
	char *ch_avatar;
	char *u_login;
	char *u_lastSeen;
	char *u_avatar;
} chat_t;

main_form_t main_form;

void get_chats_from_db();
chat_t **request_get_chats(char *request);
void *auth_check_f(void *auth_s);
void *start_spinner(void *cur_grid);
char *mx_file_to_str(const char *filename);
void is_fullscreen(GtkWidget *window);
void show_open_contact(GtkWidget *main_grid, char *id);
void show_right_panel_is_clear(GtkWidget *main_grid);
void show_contacts(GtkWidget *main_grid);
gboolean open_contacts(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img);
char *write_to_json(char *num_f, char **arr_new);
char **json_to_data(char *json_str);
void show_setting(GtkWidget *main_grid);
void show_opened_chat(GtkWidget *main_grid, char *id);
void show_chats(GtkWidget *main_grid);
char *buffer_get_text(GtkTextBuffer *buffer);
gboolean open_setting(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img);
gboolean change_placeholder_msg_out_focus(GtkTextView *text_view, GdkEvent *event, char *placeholder);
gboolean change_placeholder_msg_in_focus(GtkTextView *text_view, GdkEvent *event, char *placeholder);
gboolean change_insert_to_message(gpointer widget);
char **array_to_request(char **arr);
void open_main_form(GtkWidget *window);
bool is_pin_user(char *pin);
void valid_entry_border_pin(GtkWidget *entry);
void change_event_pin_on_pin_form(GtkWidget *entry, int *min);
void autorization_click_pin(GtkWidget *button, struct pin_f *pin_struct);
void open_form_pin(GtkWidget *window);
bool is_autorization_user(char *login, char *password);
void autorization_in_app(GtkWidget *button, cur_grid_t *cur_grid);
gboolean open_chats(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img);
void clear_styles_from_left_panel(left_panel_img_t *left_panel_img);

void is_valid_message_to_entry(bool (*is_success)(int, int *, char *), char *value, int *minSize, GtkWidget **label_fail, GtkWidget **entry, char *message, int *flag);
void valid_entry_border_color(GtkWidget **entry);
bool request_to_server(char *request);
bool find_user_by_login(char *login);
void string_array_clear(char **arr, int size);
void application_activate(GtkApplication *application, gpointer user_data);
void application_shutdown(GtkApplication *application, gpointer user_data);
void css_set(GtkWidget **widgets, char *path_to_css);
void css_set_for_one(GtkWidget *widget, char *path_to_css);
GtkWidget *create_input(GtkBuilder *builder, char *name_elem, int *maxSize);
void login();
void edit_styles_for_widget(GtkWidget *widget, char *styles);
GtkBuilder *glade_file_to_interface(char *path_to_glade_file);
void open_register(GtkWidget *window);
void open_reg(GtkWidget *button, GtkWidget *widget);
void open_login_form(GtkWidget *button, GtkWidget *widget);
void open_login(GtkWidget *window);
void create_new_main_window(GtkWidget **restrict window, char *window_id, char *path_to_window);
void open_register_third_form(GtkWidget *button, GtkWidget *widget);
void open_register_third(GtkWidget *window);
void open_register_second(GtkWidget *window);
void open_register_second_form(GtkWidget *button, GtkWidget *widget);
void create_new_user(char *login, char *name, char *surname, char *password, char *pin);
bool is_alpha_string(char *str);
bool is_digit_or_alpha_in_str(char *str);
bool is_login_or_password(int length, int *minSize, char *text);
bool is_only_alpha(int length, int *minSize, char *text);
bool is_digits(char *str);
bool is_pin(int length, int *minSize, char *text);
char *mx_strnew(const int size);
void is_input_success(bool (*is_success)(int, int *, char *), GtkWidget **entry, int *min);
void change_event_login_or_password(GtkWidget *entry, int *min);
void change_event_entry_only_aplha(GtkWidget *entry, int *min);
void change_event_pin(GtkWidget *entry, int *min);
void open_main_form_after_register(GtkWidget *button, GtkWidget *widget);
void change_size_message_input(GtkWidget *widget, msg_t *msg_entry);
bool mx_isspace(char c);
#endif
