#ifndef CHAT_H
#define CHAT_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	GtkApplication *restrict app;
	GtkWidget *restrict win;
}appdata;

appdata data;
appdata *data_ptr;

void application_activate(GtkApplication *application, gpointer user_data);
void application_shutdown(GtkApplication *application, gpointer user_data);
void css_set(GtkWidget *widgets[], char *path_to_css, int size);
void css_set_for_one(GtkWidget *widget, char *path_to_css);
GtkWidget *create_input(GtkBuilder *builder, char *name_elem, int maxSize);
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

#endif
