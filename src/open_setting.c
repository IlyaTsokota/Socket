#include "chat.h"

gboolean open_setting(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{

    if (main_form.current_panel_id != 1 && main_form.is_allow_access_next_panel)
    {
        gtk_widget_hide(main_form.chat_info_event_box);

        main_form.is_allow_access_next_panel = false;
        main_form.current_panel_id = 1;
        // free_chat_items(chats_f.chat_items);
        // free_contact_widgets(contacts_t.widgets);
        hide_gtk_widgets(main_form.left_content);
        hide_gtk_widgets(main_form.right_content);
        clear_styles_from_left_panel(left_panel_img);
        edit_styles_for_widget(left_panel_img->setting,  "* {background: #88c5ce;}");
        show_setting(main_form.main_grid);
        gtk_label_set_text(GTK_LABEL(main_form.setting_login), data.user_login);
        clear_styles_from_setting_elements();
        show_right_panel_is_clear(main_form.main_grid);
        gtk_widget_show_all(main_form.left_content[2]);
        gtk_widget_show_all(main_form.right_content[1]);
        main_form.is_allow_access_next_panel = true;
    }
    return false;
}
