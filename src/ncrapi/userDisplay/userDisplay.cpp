#include "ncrapi/userDisplay/userDisplay.hpp"
UserDisplay::UserDisplay()
{
    lv_obj_t *img1 = lv_img_create(lv_disp_get_scr_act(NULL), NULL);
    lv_img_set_src(img1, &logo);
    lv_obj_set_pos(img1, 10, 10);
}