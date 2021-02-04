#include "chat.h"

gboolean open_contacts(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
    if (main_form.current_panel_id != 3  && main_form.is_allow_access_next_panel)
    {
        main_form.is_allow_access_next_panel = false;
        main_form.current_panel_id = 3;
        free_chat_items(chats_f.chat_items);      
        gtk_widget_destroy(main_form.right_content);
        gtk_widget_destroy(main_form.left_content);
        clear_styles_from_left_panel(left_panel_img);
        edit_styles_for_widget(left_panel_img->contact, "* {background: #88c5ce;}");
        show_contacts(main_form.main_grid);
        show_right_panel_is_clear(main_form.main_grid);
        main_form.is_allow_access_next_panel = true;
    }
    return false;
}
