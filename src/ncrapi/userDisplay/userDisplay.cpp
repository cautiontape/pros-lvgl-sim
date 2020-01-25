#include "ncrapi/userDisplay/userDisplay.hpp"
#include "sim_test/test_config.hpp"
namespace ncrapi {
void btn_event_cb(lv_obj_t *btn, lv_event_t event)
{
    switch (event)
    {
        case LV_EVENT_PRESSED:
            printf("Pressed\n");
            break;

        case LV_EVENT_SHORT_CLICKED:
            printf("Short clicked\n");
            break;

        case LV_EVENT_CLICKED:
            printf("Clicked\n");
            break;

        case LV_EVENT_LONG_PRESSED:
            printf("Long press\n");
            break;

        case LV_EVENT_LONG_PRESSED_REPEAT:
            printf("Long press repeat\n");
            break;

        case LV_EVENT_RELEASED:
            printf("Released\n");
            break;
    }
}
UserDisplay::UserDisplay()
{
    lv_obj_t *slider1 = lv_slider_create(lv_scr_act(), NULL);
    lv_obj_set_x(slider1, 30);
    lv_obj_set_y(slider1, 10);
    lv_obj_set_size(slider1, 200, 50);
    lv_slider_set_value(slider1, 70, LV_ANIM_ON);
    static lv_style_t style1;                        /*Declare a new style. Should be `static`*/
    lv_style_copy(&style1, &lv_style_plain);         /*Copy a buil-in style*/
    style1.body.main_color = LV_COLOR_RED;           /*Main color*/
    style1.body.grad_color = lv_color_hex(0xffd83c); /*Gradient color (orange)*/
    style1.body.radius = 3;
    style1.text.color = lv_color_hex3(0x0F0); /*Label color (green)*/
    style1.text.font = &ncr_font10;           /*Change font*/
    lv_slider_set_style(slider1, LV_SLIDER_STYLE_BG, &style1);
    lv_slider_set_style(slider1, LV_SLIDER_STYLE_INDIC, &style1);
    lv_slider_set_style(slider1, LV_SLIDER_STYLE_KNOB, &style1);
    lv_obj_set_event_cb(slider1, btn_event_cb); //设置动作的通用函数

    lv_obj_t *btn = lv_btn_create(lv_scr_act(), NULL); /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                       /*Set its position*/
    lv_obj_set_size(btn, 100, 50);                     /*Set its size*/
    lv_obj_set_event_cb(btn, btn_event_cb);            /*Assign a callback to the button*/

    lv_obj_t *label = lv_label_create(btn, NULL); /*Add a label to the button*/
    lv_label_set_style(label, LV_LABEL_STYLE_MAIN, &style1);
    lv_label_set_text(label, "按钮1");              /*Set the labels text*/
    static lv_style_t style_btn_rel;                /*A variable to store the released style*/
    lv_style_copy(&style_btn_rel, &lv_style_plain); /*Initialize from a built-in style*/
    style_btn_rel.body.border.color = lv_color_hex3(0x269);
    style_btn_rel.body.border.width = 1;
    style_btn_rel.body.main_color = lv_color_hex3(0xADF);
    style_btn_rel.body.grad_color = lv_color_hex3(0x46B);
    style_btn_rel.body.shadow.width = 4;
    style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
    style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
    style_btn_rel.text.color = lv_color_hex3(0xDEF);

    static lv_style_t style_btn_pr;               /*A variable to store the pressed style*/
    lv_style_copy(&style_btn_pr, &style_btn_rel); /*Initialize from the released style*/
    style_btn_pr.body.border.color = lv_color_hex3(0x46B);
    style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
    style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
    style_btn_pr.body.shadow.width = 2;
    style_btn_pr.text.color = lv_color_hex3(0xBCD);

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_btn_rel); /*Set the button's released style*/
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &style_btn_pr);   /*Set the button's pressed style*/

    lv_obj_t *icon = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(icon, &logo);
    lv_anim_t a;
    lv_obj_set_x(icon, LV_HOR_RES_MAX - lv_obj_get_width(icon));
    lv_anim_set_exec_cb(&a, icon, (lv_anim_exec_xcb_t)lv_obj_set_y); /*Set the animator function and variable to animate*/
    lv_anim_set_time(&a, 5000, 0);
    lv_anim_set_values(&a, -lv_obj_get_height(icon), (LV_VER_RES_MAX - lv_obj_get_height(icon)) / 2); /*Set start and end values. E.g. 0, 150*/
    lv_anim_set_path_cb(&a, lv_anim_path_bounce);                                                     /*Set path from `lv_anim_path_...` functions or a custom one.*/
    a.repeat = 0;
    lv_anim_set_ready_cb(&a, (lv_anim_ready_cb_t)lv_anim_del); /*Set a callback to call then animation is ready. (Optional)*/
    //lv_anim_set_repeat(&a, wait_time);            /*Enable repeat of teh animation with `wait_time` delay. Can be compiled with playback*/
    lv_anim_create(&a); /*Start the animation*/
}
} // namespace ncrapi