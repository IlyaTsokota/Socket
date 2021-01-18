#include "chat.h"

void server_set_connection()
{
    struct sockaddr_in client_addr;
    data.socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(data.socket_desc, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0) {
        printf("Connected to server, port is %d\n", port);
    } else {
         // сверстать окно об ошибке и вызывать здесь и вызывать функцию которая будет каждые 60 секунд вызывать повторное соединение с сервером рекурсией
        // server_set_connection();
        printf("Something wrong!\n");
        exit(1);
    }
}

void application_activate(GtkApplication *application, gpointer user_data)
{
    server_set_connection();
    GtkBuilder *builder = glade_file_to_interface("share/window_auth.glade");
    data.win = GTK_WIDGET(gtk_builder_get_object(builder, "windowAuth"));
    css_set_for_one(data.win, "share/resources/css/auth.css");
    g_object_unref(builder);
    // в будущем проверка из файла на то какое окно открыть
    // open_login(data.win);
    open_main_form(data.win);
    /////////////////////////////////////
    gtk_application_add_window(application, GTK_WINDOW(data.win));
    gtk_widget_show_all(data.win);
   
}

void application_shutdown(GtkApplication *application, gpointer user_data)
{
    close(data.socket_desc);
    g_application_quit(G_APPLICATION(application));
}

int main(int argc, char *argv[])
{
    // setlocale(LC_ALL, "");
    gtk_init(&argc, &argv);
    data.app = gtk_application_new("gtk.org", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(data.app, "activate", G_CALLBACK(application_activate), NULL);
    g_signal_connect(data.app, "shutdown", G_CALLBACK(application_shutdown), NULL);
    gint res = g_application_run(G_APPLICATION(data.app), 0, NULL);
    return 0;
}
