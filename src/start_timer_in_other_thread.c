#include "chat.h"

void start_timer_in_other_thread()
{
    // g_timeout_add(10000, refresh_chat, NULL);
    // GError *error = NULL;
    GThread *t = g_thread_new("hentai_miami", thread_by_refresh_data, NULL);
}

gpointer thread_by_refresh_data(gpointer data)
{
    GMainContext *c;
    GMainContext *d;
    GMainLoop *l;
    GSource *s;

    c = g_main_context_new();
    d = g_main_context_default();

    g_message("local: %p", c);
    g_message("default: %p", d);

#if 1
    l = g_main_loop_new(c, FALSE);
    s = g_timeout_source_new(10000);
    g_source_set_callback(s, refresh_chat, l, end_of_timer);
    g_source_attach(s, c);
    g_source_unref(s);
#else
    l = g_main_loop_new(d, FALSE);
    g_timeout_add_full(G_PRIORITY_DEFAULT, 10000, refresh_chat, l, end_of_timer);
#endif

    g_main_loop_run(l);
    g_message("done");

    return NULL;
}

void end_of_timer(gpointer data)
{
    g_main_loop_quit((GMainLoop *)data);
}