#pragma once
#include "lvgl/lvgl.h"
#include <iostream>
extern "C" {
LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(field);
LV_FONT_DECLARE(ncr_font10);
}
class UserDisplay
{
  public:
    UserDisplay();
};