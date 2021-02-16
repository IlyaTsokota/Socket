#include "chat.h"

gboolean open_chats(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{

    hide_gtk_widgets(main_form.left_content);
    clear_styles_from_left_panel(left_panel_img);
    edit_styles_for_widget(left_panel_img->chat, "* {background: #88c5ce;}");
    gtk_widget_show_all(main_form.left_content[0]);
    gtk_widget_show_all(main_form.right_content[0]);
    set_chat_name_top();

  
  return false;
}
