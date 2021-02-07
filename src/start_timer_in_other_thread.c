#include "chat.h"

void start_timer_in_other_thread()
{
    GThread *t = g_thread_new("hentai_miami", thread_by_refresh_data, NULL);
}

gpointer thread_by_refresh_data(gpointer data)
{
    GMainContext *c;
    GMainLoop *l;
    GSource *s;
    c = g_main_context_new();

    l = g_main_loop_new(c, FALSE);
    s = g_timeout_source_new(10000);
    g_source_set_callback(s, refresh_chat, l, end_of_timer);
    g_source_attach(s, c);
    g_source_unref(s);
    g_main_loop_run(l);
    
    return NULL;
}

void end_of_timer(gpointer data)
{
    g_main_loop_quit((GMainLoop *)data);
}