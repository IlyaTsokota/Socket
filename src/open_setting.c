#include "chat.h"

gboolean open_setting(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
    gtk_widget_destroy(main_form.right_content);
    gtk_widget_destroy(main_form.left_content);
    clear_styles_from_left_panel(left_panel_img);
    edit_styles_for_widget(left_panel_img->setting, "* {background: #88c5ce;}");
    show_setting(main_form.main_grid);
    show_right_panel_is_clear(main_form.main_grid);
    return false;
}
