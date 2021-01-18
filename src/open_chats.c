#include "chat.h"

gboolean open_chats(GtkWidget *widget, GdkEventButton *event,left_panel_img_t *left_panel_img)
{
    gtk_widget_destroy(main_form.right_content);
    gtk_widget_destroy(main_form.left_content);
    clear_styles_from_left_panel(left_panel_img);
    edit_styles_for_widget(left_panel_img->chat, "* {background: #fff;}");
    show_chats(main_form.main_grid);
    show_opened_chat(main_form.main_grid, "1");
    return false;
}
