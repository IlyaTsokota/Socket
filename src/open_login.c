#include "chat.h"

void open_login(GtkWidget *window)
{
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    GtkBuilder *builder = glade_file_to_interface("share/login.glade");
    GtkWidget *loginForm = GTK_WIDGET(gtk_builder_get_object(builder, "loginForm"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *labelCreate = GTK_WIDGET(gtk_builder_get_object(builder, "createLabel"));
    GtkWidget *labelLogin = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *labelPassword = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLable"));
    autorization.login = create_input(builder, "loginInput", maxSize);
    g_signal_connect(G_OBJECT(autorization.login), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    autorization.password = create_input(builder, "passwordInput", maxSize);
    g_signal_connect(G_OBJECT(autorization.password), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    autorization.fail_login = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));
    autorization.fail_password = GTK_WIDGET(gtk_builder_get_object(builder, "fail_password"));
    GtkWidget *arrWidgetForStyled[] = {labelLogo, labelText, labelCreate, labelLogin, labelPassword, autorization.password, autorization.login, btnNext, loginForm, autorization.fail_login, autorization.fail_password};
    css_set(arrWidgetForStyled, "share/resources/css/auth.css", 11);
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(autorization_in_app), loginForm);
    g_signal_connect(G_OBJECT(labelCreate), "clicked", G_CALLBACK(open_reg), loginForm);
    gtk_container_add(GTK_CONTAINER(window), loginForm);
    g_object_unref(builder);
}
