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

    main_form.loop = g_main_loop_new(c, FALSE);
    s = g_timeout_source_new(1000);
    g_source_set_callback(s, G_SOURCE_FUNC(refresh_chat), NULL, end_of_timer);
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
    close(c_data->socket);
    free(c_data);
}

void start_timer_for_update_chat()
{
    main_form.update_thread_chat = g_thread_new("update_chat", thread_by_refresh_chat, NULL);
}

gpointer thread_by_refresh_chat(gpointer dat)
{

    GMainContext *c;
    GSource *s;
    c = g_main_context_new();

    main_form.loop_chat = g_main_loop_new(c, FALSE);
    s = g_timeout_source_new(1000);
    g_source_set_callback(s, G_SOURCE_FUNC(update_chat), NULL, end_of_timer);
    g_source_attach(s, c);
    g_source_unref(s);
    g_main_loop_run(main_form.loop_chat);

    return NULL;
}

void end_of_timer_chat(gpointer dat)
{
    g_thread_join(main_form.update_thread);
    update_t *c_data = (update_t *)dat;
    g_main_loop_quit(main_form.loop_chat);
    close(c_data->socket);
    free(c_data);
}

void start_timer_for_edit_messages()
{
    main_form.update_edit_msgs = g_thread_new("edit_messages", thread_by_edit_messages, NULL);
}

gpointer thread_by_edit_messages(gpointer dat)
{
    
      
        GMainContext *c;
        GSource *s;
        c = g_main_context_new();

        main_form.loop_edit_msgs = g_main_loop_new(c, FALSE);
        s = g_timeout_source_new(1000);
        g_source_set_callback(s, G_SOURCE_FUNC(update_edit_msgs), NULL, end_of_timer_edit_messages);
        g_source_attach(s, c);
        g_source_unref(s);
        g_main_loop_run(main_form.loop_edit_msgs);
  
    return NULL;
}

void end_of_timer_edit_messages(gpointer dat)
{
    g_thread_join(main_form.update_edit_msgs);
    update_t *c_data = (update_t *)dat;
    g_main_loop_quit(main_form.loop_edit_msgs);
    close(c_data->socket);
    free(c_data);
}
