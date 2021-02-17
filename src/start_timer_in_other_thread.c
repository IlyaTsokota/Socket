#include "chat.h"

void start_timer_in_other_thread()
{
    main_form.update_thread = g_thread_new("hentai_miami", thread_by_refresh_data, NULL);
}

gpointer thread_by_refresh_data(gpointer dat)
{
    GMainContext *c;
    GSource *s;
    c = g_main_context_new();
    update_t *update = malloc(sizeof(update));
    update->socket = data.socket_desc;
    main_form.loop = g_main_loop_new(c, FALSE);

    s = g_timeout_source_new(3000);
    g_source_set_callback(s, G_SOURCE_FUNC(refresh_chat), update, end_of_timer);
    g_source_attach(s, c);
    g_source_unref(s);
    g_main_loop_run(main_form.loop);

    return NULL;
}

void end_of_timer(gpointer dat)
{
    g_thread_join(main_form.update_thread);
    update_t *c_data = (update_t *)dat;
    g_main_loop_quit(main_form.loop);
    free(dat);
}

void start_timer_for_update_chat()
{
    main_form.update_thread_chat = g_thread_new("update_chat", thread_by_refresh_chat, NULL);
}

gpointer thread_by_refresh_chat(gpointer dat)
{
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr("159.224.0.212"); //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        GMainContext *c;
        GSource *s;
        c = g_main_context_new();

        main_form.loop_chat = g_main_loop_new(c, FALSE);
        s = g_timeout_source_new(1000);
        g_source_set_callback(s, G_SOURCE_FUNC(update_chat), update, end_of_timer_chat);
        g_source_attach(s, c);
        g_source_unref(s);
        g_main_loop_run(main_form.loop_chat);
    }
    else
    {
        close(update->socket);
        free(update);
        update = NULL;
    }
    return NULL;
}

void end_of_timer_chat(gpointer dat)
{
    g_thread_join(main_form.update_thread);
    update_t *c_data = (update_t *)dat;
    g_main_loop_quit(main_form.loop_chat);
    close(c_data->socket);
    free(dat);
}
