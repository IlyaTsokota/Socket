#ifndef CHAT_H
#define CHAT_H

#define _XOPEN_SOURCE 700
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
     #include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <locale.h>
#include <wctype.h>
#include <stdarg.h>
#include "json-c/json.h"
#include <fcntl.h>
#include <gio/gio.h>
#include <pthread.h>
#include <glib.h>
#include <cairo.h>

typedef struct
{
	bool bshow_chats;
	bool bshow_contacts;
	bool bshow_edit_profile;
	bool bshow_language;
	bool bshow_privacy;
	bool bshow_double_bottom;
	bool bshow_appereance;
	bool bshow_open_contact;
	bool bshow_right_panel_is_clear;
	bool bshow_setting;
	bool bshow_notification;
	bool bshow_add_chat;
	bool bshow_chat_info;
	bool bshow_add_participant;
	bool bshow_remove_participant;
	bool bshow_add_contact;
	bool bshow_change_password;
	bool bshow_change_pin;
} do_once_t;

do_once_t do_once;

typedef struct
{
	GtkWidget *pin;
	GtkWidget *fail_pin;
} db_data;

typedef struct
{
	GtkWidget *event_box_message;
	GtkWidget *message;
	GtkWidget *message_time;
	GtkWidget *message_info;
	GtkWidget *message_text;
	GtkWidget *message_login;

} messages_t;

typedef struct
{
	GtkWidget *grid;
	GtkWidget *btn_container;
	GtkWidget *btn;
	GtkWidget *spinner;
} cur_grid_t;

typedef struct
{
	char *u_login;
	char *u_name;
	char *u_avatar;
	char *u_status;
	bool is_my_contact;
} contact_info_t;

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
	GtkWidget *user_is_online_round;
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
typedef struct
{
	GtkWidget *setting;
	GtkWidget *contact;
	GtkWidget *chat;
	GtkWidget *lock;
} left_panel_img_t;
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
	messages_t **messages_g;
	int *length;
} current_chat_s;

typedef struct
{
	GtkWidget *login;
	GtkWidget *password;
	GtkWidget *fail_login;
	GtkWidget *fail_password;
	GtkWidget *fail_auth;
	char *login_text;

} autorization_w;

typedef struct
{
	GtkWidget *users_item;
	GtkWidget *user_event_box;
	GtkWidget *body_user;
	GtkWidget *user_img;
	GtkWidget *user_name;
	GtkWidget *delete_event_box;
	GtkWidget *remove_img;

} user_in_chat_t;

typedef struct
{
	char *add_chat;
	char *add_contact;
	char *add_participant;
	char *appereance;
	char *chat_info;
	char *chats;
	char *contacts_left;
	char *contacts_right;
	char *double_bottom;
	char *edit_profile;
	char *language;
	char *left_panel_setting;
	char *login;
	char *main;
	char *notifications;
	char *opened_chat;
	char *pin_code;
	char *privacy;
	char *register_one;
	char *register_three;
	char *register_two;
	char *remove_participant;
	char *change_password;
	char *change_pin;

} localization_t;

typedef struct
{
	user_in_chat_t **users;
	int size;
} user_by_chat_t;

autorization_w autorization;

typedef struct
{
	GtkApplication *restrict app;
	GtkWidget *restrict win;
	char *user_id;
	int socket_desc;
	char *user_login;
	char *picture_name;
	char *auth_theme_path;
	char *main_theme_path;
	char *theme;
	bool isBottomed;
	char *language;
} appdata;

appdata data;

typedef struct
{
	GtkWidget *app_form;
	GtkWidget **left_content;
	GtkWidget **right_content;
	GtkWidget *main_grid;
	GtkWidget *chats_grid;
	GtkWidget *top_panel_top_text;
	GtkWidget *top_panel_bottom_text;
	GtkWidget *message_line;
	GtkWidget *message_scroll;
	int current_panel_id;
	bool is_allow_access_next_panel;
	char *message;
	char *last_ms_id;
	GMutex mutex;
	GMutex mutex_seding_msg;
	GMutex mutex_file_transfer;

	GMainLoop *loop;
	GThread *update_thread;

	GMainLoop *loop_chat;
	GThread *update_thread_chat;

	GtkWidget *search_entry;
	GtkWidget *create_chat_event_box;
	GtkWidget *chat_info_event_box;
	GtkWidget *chat_name_title;
	GtkWidget *text_view;
	GtkWidget *chat_name_input;
	GtkWidget *users_container;
	GtkWidget *contact_info_name;
	GtkWidget *quote_text;
	GtkWidget *img_info_contact;
	GtkWidget *fullname_text;
	GtkWidget *setting_login;
	GtkWidget *box_contact;
	GtkWidget *add_contact;
	left_panel_img_t *left_panel_img;
	bool is_admin_by_chat;
	GtkWidget *delete_chat;
	GtkWidget *is_connection;
	GtkWidget *setting_img;
	GtkWidget *profile_img;
	GtkWidget *curr_chat_img;
} main_form_t;

typedef struct
{
	char *u_id;
	char *u_login;
	char *u_avatar;
	bool u_isBottomed;
} login_pin_info_t;

typedef struct
{
	GtkWidget *name;
	GtkWidget *surname;
	GtkWidget *quote;
} edit_prof_s;

typedef struct
{
	GtkWidget *edit_profile_img;
	GtkWidget *edit_profile_text;
	GtkWidget *notifications_img;
	GtkWidget *notifications_text;
	GtkWidget *privacy_img;
	GtkWidget *privacy_text;
	GtkWidget *language_img;
	GtkWidget *language_text;
	GtkWidget *theme_img;
	GtkWidget *theme_text;
	GtkWidget *double_bottom_img;
	GtkWidget *double_bottom_text;
} setting_items;

typedef struct
{
	GtkWidget *event_box_contact;
	GtkWidget *contact_container;
	GtkWidget *contact_info;
	GtkWidget *contact_status;
	GtkWidget *contact_status_lable;
	GtkWidget *contact_name_container;
	GtkWidget *contact_name_lable;
	GtkWidget *grid_list_contact_img;
	GtkWidget *img_contact;
} contacts_widget_s;

typedef struct
{
	char *ch_id;
	char *ch_name;
	char *ch_avatar;
	char *u_login;
	char *u_lastSeen;
	char *u_avatar;
	char *u_time;

} chat_t;

typedef struct
{
	char *login;
	char *theme;
	char *language;
	char *is_in;
} settings_t;

typedef struct
{
	char *ch_id;
	char *ms_id;
	char *u_id;
	char *u_name;
	char *ms_text;
	char *ms_datetime;
	char *ms_isedited;
	char *ms_isforwarded;
	char *ms_ismedia;
	char *ms_isreply;
	char *ms_isseen;

} message_t;

typedef struct
{
	message_t **messages;
	int *length;
} message_arr;

typedef struct
{
	contacts_widget_s **widgets;
	bool was_free;
	int size;
	char *curr_contact;
} contacts_arr;

typedef struct
{
	chat_item_t **chat_items;
	char *curr_chat;
	int size;
	bool was_free;
} chats_form;

typedef struct
{
	char *u_name;
	char *u_surname;
	char *u_avatar;
	char *u_status;
} user_t;

typedef struct
{
	char *c_id;
	char *u_name;
	char *u_avatar;
	char *u_status;
} contact_t;

typedef struct
{
	int socket;
} update_t;

typedef struct
{
	char *u_id;
	char *u_login;
	char *u_avatar;
} user_curr_chat_t;

typedef struct
{
	GtkWidget *input;
	GtkWidget *fail_lable;
} data_input_t;

setting_items setting_elements;
chats_form chats_f;
contacts_arr contacts_t;
main_form_t main_form;

edit_prof_s profile_s;
current_chat_s curr_chat;
user_by_chat_t users_in_chat;
localization_t localization_s;

char *get_msg_img(int socket, char *ch_id, char*ms_id, char *filename);
void show_chats_widgets();
void sort_chats(chat_t **chats, int size);
gboolean update_chat(update_t *update);
void start_timer_for_update_chat();
gpointer thread_by_refresh_chat(gpointer dat);
void end_of_timer_chat(gpointer dat);
char *get_chat_img(int socket, char *ch_id, char *filename);
void update_img_in_chat(GtkFileChooser *chooser, GtkImage *img);
char *strjoins_arr(const char **str_arr);
char *get_filename_extension(char *filename);
char *get_profile_img(int socket, char *filename, char *ch_id, bool flag);
void recieve_image(int socket, char *path);
void send_image(int sock, char *filename);
void update_img_in_profile(GtkFileChooser *chooser, GtkImage *img);
gboolean switch_vpn(GtkWidget *widget);
void change_pin(GtkWidget *button, data_input_t *info);
void show_change_pin(GtkWidget *main_grid);
gboolean open_change_pin(GtkWidget *widget, GdkEventButton *event);
void change_password(GtkWidget *button, data_input_t *info);
void show_change_password(GtkWidget *main_grid);
gboolean open_change_password(GtkWidget *widget, GdkEventButton *event);
gboolean remove_chat(GtkWidget *widget);
void update_chats_after_delete();
gboolean exit_from_chat(GtkWidget *widget);
void send_from_contact(GtkWidget *button);
int get_chat_index(char *ch_id);
void free_language_interface();
gboolean switch_language(GtkSwitch *widget, gboolean state, gpointer info);
void init_language_interface(char *language);
void remove_from_contact(GtkWidget *button);
void add_to_contact(GtkWidget *button);
void clear_style_all_contact_widgets();
gboolean remove_user_from_chat(GtkWidget *widget);
void refresh_users_by_chat();
void create_one_user_widget(int i, user_curr_chat_t *contact);
void free_user_widgets(user_in_chat_t **contacts);
user_curr_chat_t **take_users_by_chat(int socket);
user_curr_chat_t **users_by_chat_to_json(char *str);
void free_user_curr_chat_t_s(user_curr_chat_t **message);
void sort_by_chat_widget();
void create_widget_contacts(char *user_id);
void add_contact(GtkWidget *button, data_input_t *info);
void add_participant(GtkWidget *button, data_input_t *info);
void show_add_contact(GtkWidget *main_grid);
gboolean open_add_contact(GtkWidget *widget, GdkEventButton *event);
void show_remove_participant(GtkWidget *main_grid);
gboolean open_remove_participant(GtkWidget *widget, GdkEventButton *event);
gboolean open_add_participant(GtkWidget *widget, GdkEventButton *event);
void show_add_participant(GtkWidget *main_grid);
int get_curr_chat_index();
void edit_name_chat(GtkWidget *button);
void set_chat_name_in_info_chat();
gboolean open_chat_info(GtkWidget *widget, GdkEventButton *event);
void show_chat_info(GtkWidget *main_grid);
void set_chat_name_top();
GtkWidget *find_child(GtkWidget *parent, const gchar *name);
void clear_style_all_chat_widgets();
gboolean open_add_chat(GtkWidget *widget, GdkEventButton *event);
void show_add_chat(GtkWidget *main_grid);
void add_new_chat(GtkWidget *button, GtkWidget *widgets);
void switch_current_theme(char *curr_theme);
void what_theme_select(char *curr_theme);
void free_theme();
gboolean switch_theme(GtkSwitch *widget, gboolean state, gpointer data);
gboolean show_emoji(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view);
void send_source(int so, char *f_num,  char *some_id, char *filename);
gboolean send_pinned_resource(GtkWidget *widget);
void clear_interface();
void free_message_widgets(messages_t **message);
void free_chat_widgets(chat_item_t **contacts);
void init_do_once(bool value);
void create_db_acc(GtkWidget *button, db_data *db_data);
void create_one_chat(int index, chat_t *chat);
login_pin_info_t *request_get_pin_info(char *response);
void free_validation_login_info_s(login_pin_info_t *message);
void *sending(gpointer text_view);
void insert_text(GtkTextBuffer *buffer, GtkTextIter *location, gchar *text, gint len, gpointer user_data);
void end_of_timer(gpointer data);
gpointer thread_by_refresh_data(gpointer data);
void start_timer_in_other_thread();
chat_t **take_chats(char *user_id, int sock);
void init_interface();
void hide_gtk_widgets(GtkWidget **widgets);
void create_chat_widgets(char *user_id, int sock);
message_arr *take_messages(int socket, char *user_id, char *last_msg_id);
message_arr *messages_to_json(char *str);
void clear_text__buffer(GtkTextView *text_view);
gboolean refresh_chat(update_t *update);
void create_one_messages(int index, message_t *message);
char *get_text_of_textview(GtkTextView *text_view);
gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view);
void free_contact_info_s(contact_info_t *contact);
contact_info_t *get_contact_info(char *contact_id);
char *strjoin(int nHowMany, ...);
char *cut_str(char *str, int count_sym_cut);
void free_contact_widgets(contacts_widget_s **contacts);
void free_chat_items(chat_item_t **chats);
void free_all_children_in_container(GtkWidget *container);
gboolean open_click_contact(GtkWidget *widget);
void free_contacts_s(contact_t **contact);
void create_one_contact(int i, contact_t *contacts);
user_t *get_profile_info();
void free_user_s(user_t *user);
void set_active_setting_item(GtkWidget *text, GtkWidget *img, char *path_img, void (*f)(GtkWidget *grid), int index);
void logout(GtkWidget *button);
void logout_on_pin_form(GtkWidget *button, GtkWidget *widget);
void update_profile(GtkWidget *button);
bool update_user_data(char *u_id, char *name, char *surname, char *quote);
gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form);
gboolean open_double_bottom(GtkWidget *widget, GdkEventButton *event);
gboolean open_notification(GtkWidget *widget, GdkEventButton *event);
gboolean open_appereance(GtkWidget *widget, GdkEventButton *event);
gboolean open_privacy(GtkWidget *widget, GdkEventButton *event);
gboolean open_language(GtkWidget *widget, GdkEventButton *event);
gboolean open_edit_profile(GtkWidget *widget, GdkEventButton *event);
void clear_styles_from_setting_elements();
void show_appereance(GtkWidget *main_grid);
void show_notification(GtkWidget *main_grid);
void show_double_bottom(GtkWidget *main_grid);
void show_privacy(GtkWidget *main_grid);
void show_language(GtkWidget *main_grid);
contact_t **get_contacts(char *response);
void show_edit_profile(GtkWidget *main_grid);
char *get_last_mesage_id(char *filename);
char *get_user_id_from_db(char *login);
char *request_get_str_from_server(char *request);
void free_messages(message_arr *message_container);
void create_widget_messages();
void get_all_messages(char *user_id, char *last_msg_id);
message_arr *get_messages_from_file(char *filename);
char *request_on_server(int socket, char *request);
gboolean open_click_chat(GtkWidget *widget, GdkEventButton *event);
bool is_online(char *last_seen);
char *strjoins(const char *s1, const char *s2);
char *int_to_str(int n);
void free_settings(settings_t *settings);
settings_t *get_settings(char *settings);
void create_settings_json(char *login, char *theme, char *language, char *is_in);
void free_chats(chat_t **chats);
void set_style_context(GtkWidget *widget, char *class_name);
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
void open_form_pin(GtkWidget *window, bool is_start_app);
bool is_autorization_user(char *login, char *password);
void autorization_in_app(GtkWidget *button, GtkWidget *grid);
gboolean open_chats(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img);
void clear_styles_from_left_panel(left_panel_img_t *left_panel_img);
void str_to_file(const char *filepath, const char *data);
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
