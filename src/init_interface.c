#include "chat.h"

void init_interface()
{
    main_form.right_content = malloc(sizeof(GtkWidget *) * 15);
    main_form.right_content[14] = NULL;
    for (size_t i = 0; i < 14; i++)
    {
        main_form.right_content[i] = gtk_grid_new();
        gtk_widget_set_hexpand(main_form.right_content[i], true);
        gtk_widget_set_vexpand(main_form.right_content[i], true);
        set_style_context(main_form.right_content[i], "message-panel");
    }

    main_form.left_content = malloc(sizeof(GtkWidget *) * 4);
    main_form.left_content[3] = NULL;
    for (size_t i = 0; i < 3; i++)
    {
        main_form.left_content[i] = gtk_grid_new();
        gtk_widget_set_halign(main_form.left_content[i], GTK_ALIGN_START);
        gtk_widget_set_hexpand(main_form.left_content[i], false);
        gtk_widget_set_vexpand(main_form.left_content[i], true);
        set_style_context(main_form.left_content[i], "contacts-panel");
    }
}



void clear_interface()
{
    for (size_t i = 0; main_form.right_content[i]; i++)
    {
        gtk_widget_destroy(main_form.right_content[i]) ;
    }
    free(main_form.right_content);

    for (size_t i = 0; main_form.left_content[i]; i++)
    {
        gtk_widget_destroy(main_form.left_content[i]) ;
    }
    free(main_form.left_content);
}
