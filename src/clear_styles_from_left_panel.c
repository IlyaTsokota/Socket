#include "chat.h"

void clear_styles_from_left_panel(left_panel_img_t *left_panel_img)
{
    edit_styles_for_widget(left_panel_img->chat, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->setting, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->contact, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->lock, "* {background: #b787ff;}");
}