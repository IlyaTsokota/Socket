#include "chat.h"

gboolean open_chats(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
  if (main_form.current_panel_id != 2 && main_form.is_allow_access_next_panel)
  {
    main_form.is_allow_access_next_panel = false;
    main_form.current_panel_id = 2;
    // free_contact_widgets(contacts_t.widgets);
    hide_gtk_widgets(main_form.left_content);
    // hide_gtk_widgets(main_form.right_content);
    clear_styles_from_left_panel(left_panel_img);
    set_chat_name_top();
    edit_styles_for_widget(left_panel_img->chat, "* {background: #88c5ce;}");
    gtk_widget_show_all(main_form.left_content[0]);
    gtk_widget_show_all(main_form.right_content[0]);
        gtk_widget_show(main_form.chat_info_event_box);

    main_form.is_allow_access_next_panel = true;
  }
  return false;
}
