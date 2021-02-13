#include "chat.h"

void clear_styles_from_left_panel(left_panel_img_t *left_panel_img)
{
    char *style = strcmp(data.theme, "Dark") == 0 ? strdup("* {background:#b787ff;}")
                                                  : strdup("* {background: #457d99;}");
    edit_styles_for_widget(left_panel_img->chat, style);
    edit_styles_for_widget(left_panel_img->setting, style);
    edit_styles_for_widget(left_panel_img->contact, style);
    edit_styles_for_widget(left_panel_img->lock, style);
    free(style);
}

void clear_styles_from_setting_elements()
{
    char *path_img[6];
    if (strcmp(data.theme, "Dark") == 0)
    {
        path_img[0] = "./share/resources/img/theme.png";
        path_img[1] = "./share/resources/img/shield.png";
        path_img[2] = "./share/resources/img/bell.png";
        path_img[3] = "./share/resources/img/language.png";
        path_img[4] = "./share/resources/img/info.png";
        path_img[5] = "./share/resources/img/privacy.png";
    }
    else
    {
        path_img[0] = "./share/resources/img/theme-l.png";
        path_img[1] = "./share/resources/img/shield-l.png";
        path_img[2] = "./share/resources/img/bell-l.png";
        path_img[3] = "./share/resources/img/language-l.png";
        path_img[4] = "./share/resources/img/info-l.png";
        path_img[5] = "./share/resources/img/privacy-l.png";
    }
    char *color = strcmp(data.theme, "Dark") == 0 ? strdup("* {color: #c5c5c5;}")
                                                  : strdup("* {color: #1d3947;}");

    edit_styles_for_widget(setting_elements.theme_text, color);

    GdkPixbuf *theme_img = gdk_pixbuf_new_from_file(path_img[0], NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.theme_img), theme_img);
    if (!data.isBottomed)
    {
        edit_styles_for_widget(setting_elements.double_bottom_text, color);
        GdkPixbuf *double_bottom_img = gdk_pixbuf_new_from_file(path_img[5], NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.double_bottom_img), double_bottom_img);

        edit_styles_for_widget(setting_elements.privacy_text, color);
        GdkPixbuf *privacy_img = gdk_pixbuf_new_from_file(path_img[1], NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.privacy_img), privacy_img);
    }

    edit_styles_for_widget(setting_elements.notifications_text, color);
    GdkPixbuf *notification_img = gdk_pixbuf_new_from_file(path_img[2], NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.notifications_img), notification_img);

    edit_styles_for_widget(setting_elements.language_text, color);
    GdkPixbuf *language_img = gdk_pixbuf_new_from_file(path_img[3], NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.language_img), language_img);

    edit_styles_for_widget(setting_elements.edit_profile_text, color);
    GdkPixbuf *edit_profile_img = gdk_pixbuf_new_from_file(path_img[4], NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.edit_profile_img), edit_profile_img);

    free(color);
}
