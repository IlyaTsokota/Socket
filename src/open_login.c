#include "chat.h"

void open_login(GtkWidget *window)
{
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    cur_grid_t *cur_grid = (cur_grid_t *)malloc(sizeof(cur_grid_t));
    cur_grid->spinner = gtk_spinner_new();
    GtkBuilder *builder = glade_file_to_interface("share/login.glade");
    cur_grid->grid = GTK_WIDGET(gtk_builder_get_object(builder, "loginForm"));
    cur_grid->btn_container = GTK_WIDGET(gtk_builder_get_object(builder, "btn_container"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *labelCreate = GTK_WIDGET(gtk_builder_get_object(builder, "createLabel"));
    GtkWidget *labelLogin = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *labelPassword = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLable"));
    autorization.fail_login = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));
    autorization.fail_password = GTK_WIDGET(gtk_builder_get_object(builder, "fail_password"));
    autorization.fail_auth = GTK_WIDGET(gtk_builder_get_object(builder, "fail_auth"));
    cur_grid->btn = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
        autorization.login = create_input(builder, "loginInput", maxSize);
    g_signal_connect(G_OBJECT(autorization.login), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(autorization.login), "activate", G_CALLBACK(autorization_in_app), cur_grid->grid);
    autorization.password = create_input(builder, "passwordInput", maxSize);
    g_signal_connect(G_OBJECT(autorization.password), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(autorization.password), "activate", G_CALLBACK(autorization_in_app), cur_grid->grid);
    GtkWidget *arrWidgetForStyled[] = {labelLogo, labelText, labelCreate, labelLogin, labelPassword, autorization.password, autorization.login, cur_grid->btn , cur_grid->grid, autorization.fail_login, autorization.fail_password,autorization.fail_auth, NULL };
    css_set(arrWidgetForStyled, "share/resources/css/auth.css");
    g_signal_connect(G_OBJECT(cur_grid->btn), "clicked", G_CALLBACK(autorization_in_app), cur_grid);
    g_signal_connect(G_OBJECT(labelCreate), "clicked", G_CALLBACK(open_reg), cur_grid->grid);
    gtk_container_add(GTK_CONTAINER(window), cur_grid->grid);
    g_object_unref(builder);
}
