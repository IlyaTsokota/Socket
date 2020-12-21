#include "chat.h"
void open_login(GtkWidget *window){
    int* minSize = (int*)malloc(sizeof(int));
    *minSize = 4;
    int* maxSize = (int*)malloc(sizeof(int));
    *maxSize = 16;
    GtkBuilder *builder = glade_file_to_interface("share/login.glade");
    GtkWidget *loginForm = GTK_WIDGET(gtk_builder_get_object(builder, "loginForm"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *labelCreate = GTK_WIDGET(gtk_builder_get_object(builder, "createLabel"));
    GtkWidget *labelLogin = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *labelPassword = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLable"));
    GtkWidget *inputLogin = create_input(builder, "loginInput", maxSize, minSize);
    GtkWidget *inputPassword = create_input(builder, "passwordInput", maxSize, minSize);
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *arrWidgetForStyled[] = {labelLogo, labelText, labelCreate, labelLogin, labelPassword, inputPassword, inputLogin, btnNext, loginForm, window};
    css_set(arrWidgetForStyled, "share/resources/css/auth.css", 9);
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(validation_login), arrWidgetForStyled);
    g_signal_connect(G_OBJECT(labelCreate), "clicked", G_CALLBACK(open_reg), loginForm);
    gtk_container_add(GTK_CONTAINER(window), loginForm);
    g_object_unref(builder);
}
