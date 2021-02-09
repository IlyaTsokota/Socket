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
   
    s = g_timeout_source_new(10000);
    g_source_set_callback(s, G_SOURCE_FUNC(refresh_chat), update , end_of_timer);
    g_source_attach(s, c);
    g_source_unref(s);
    g_main_loop_run(main_form.loop);
    
    return NULL;
}

void end_of_timer(gpointer dat)
{
    g_thread_join(main_form.update_thread);
    update_t *c_data = (update_t *)dat;
    g_main_loop_quit( main_form.loop );
    free(dat);
}
