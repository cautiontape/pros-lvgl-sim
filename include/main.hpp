#pragma once
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mouse.h"
#include "ncrapi/userDisplay/userDisplay.hpp"
#include <SDL2/SDL.h>
#include <memory>

static lv_indev_t *kb_indev;

void init();
void autonomous();