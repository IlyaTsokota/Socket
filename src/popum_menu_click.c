#include "chat.h"

void view_popup_menu(GtkWidget *widget, GdkEventButton *event, GtkWidget *userdata)
{
    GtkWidget *menu, *edit, *reply, *forward, *kkk;

    menu = gtk_menu_new();

    reply = gtk_menu_item_new_with_label("Reply");
    forward = gtk_menu_item_new_with_label("Forward");
    char *ms_id = (char *)gtk_widget_get_name(widget);
    if (main_form.curr_ms_id != NULL)
    {
        free( main_form.curr_ms_id );
        main_form.curr_ms_id = NULL;
    }
    
    main_form.curr_ms_id = strdup(ms_id);
    main_form.cur_msg = userdata;
    if (GTK_IS_LABEL(userdata) && gtk_widget_get_halign(widget) == GTK_ALIGN_END)
    {
        edit = gtk_menu_item_new_with_label("Edit");
        gtk_menu_shell_append(GTK_MENU_SHELL(menu), edit);
        g_signal_connect(G_OBJECT(edit), "activate", G_CALLBACK(edit_message), userdata);
    }

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), reply);
    g_signal_connect(G_OBJECT(reply), "activate", G_CALLBACK(reply_message), NULL);

    // g_signal_connect(G_OBJECT(signInLabel), "clicked", G_CALLBACK(open_login_form), regOne);

    gtk_menu_shell_append(GTK_MENU_SHELL(menu), forward);
    g_signal_connect(G_OBJECT(forward), "activate", G_CALLBACK(on_popup_clicked), NULL);

    // g_signal_connect(G_OBJECT(signInLabel), "clicked", G_CALLBACK(open_login_form), regOne);

    gtk_widget_show_all(menu);
    gtk_menu_popup_at_widget(GTK_MENU(menu), userdata, GDK_GRAVITY_SOUTH_WEST, GDK_GRAVITY_NORTH_WEST, (GdkEvent *)event);
}

// gboolean
// view_onButtonPressed(GtkWidget *treeview, GdkEventButton *event, gpointer userdata)
// {

//     return FALSE;
// }
