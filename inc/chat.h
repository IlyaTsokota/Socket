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

typedef struct {
	GtkWidget *login;
	GtkWidget *name;
	GtkWidget *surname;
	GtkWidget *password;
	GtkWidget *pin;
	char *login_text;
	char *name_text;
	char *surname_text;
} register_w;

register_w registration;

typedef struct{
	GtkApplication *restrict app;
	GtkWidget *restrict win;
	int socket_desc;
} appdata;

appdata data;

bool request_to_server(char *request);
bool find_user_by_login(char *login);
void string_array_clear(char **arr, int size);
void application_activate(GtkApplication *application, gpointer user_data);
void application_shutdown(GtkApplication *application, gpointer user_data);
void css_set(GtkWidget *widgets[], char *path_to_css, int size);
void css_set_for_one(GtkWidget *widget, char *path_to_css);
GtkWidget *create_input(GtkBuilder *builder, char *name_elem, int *maxSize);
void validation_login(GtkWidget *button, GtkWidget *widgets[]);
void login();
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
bool is_login_or_password(int length, int*minSize, char *text);
bool is_only_alpha(int length, int*minSize, char *text);
bool is_digits(char *str);
bool is_pin(int length, int*minSize, char *text);
char *mx_strnew(const int size );
void is_input_success( bool (*is_success)(int, int*, char*), GtkWidget **entry, int *min);
void change_event_login_or_password(GtkWidget *entry, int *min);
void change_event_entry_only_aplha(GtkWidget *entry, int *min);
void change_event_pin(GtkWidget *entry, int *min);
char *array_to_str_with_delimiter(char **arr, int length);
#endif
