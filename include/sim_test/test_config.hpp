#pragma once
#include "lvgl/lvgl.h"
#include "ncrapi/robotSet.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif (__linux)
#include <pthread.h>
#include <unistd.h>
#else
std::cout << "unkonw compiler" << std::endl;
#endif

//#elif defined(__ARM_EABI__)//ARM编译器判断

#if (SIM_MODE == 1)
extern "C" {
LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
}
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mouse.h"
#include <SDL2/SDL.h>

/**
 * Print the memory usage periodically
 * @param param
 */
extern void memory_monitor(lv_task_t *param);
/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
extern int tick_thread(void *data);
extern void hal_init(void);
#if defined(_WIN32) || defined(_WIN64)
DWORD WINAPI taskLVGL(LPVOID pragma);
#else
void *taskLVGL(void *pragma);
#endif
#endif