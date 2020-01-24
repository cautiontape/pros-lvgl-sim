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
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif
#include <iostream>
static lv_indev_t *kb_indev;
extern "C" {
LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
}
void init();
void autonomous();