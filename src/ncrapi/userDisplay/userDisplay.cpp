#include "ncrapi/userDisplay/userDisplay.hpp"
UserDisplay::UserDisplay()
{
    lv_obj_t *slider1 = lv_slider_create(lv_scr_act(), NULL);
    lv_obj_set_x(slider1, 30);
    lv_obj_set_y(slider1, 10);
    lv_obj_set_size(slider1, 200, 50);
}