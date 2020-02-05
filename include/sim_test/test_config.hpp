#pragma once
#include "lvgl/lvgl.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>

extern "C" {

LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(field);
LV_FONT_DECLARE(ncr_font10);
}

#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#define TEST_MODE 1
#elif (__linux)
#include <pthread.h>
#include <unistd.h>
#define TEST_MODE 1
#elif defined(__ARM_EABI__)
#define TEST_MODE 0
#else
std::cout << "unkonw compiler" << std::endl;
#endif

#if (TEST_MODE == 0)

#include "pros/adi.h"
#include "pros/colors.h"
#include "pros/imu.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/vision.h"

#ifdef __cplusplus
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "pros/vision.hpp"
#endif
#else
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/keyboard.h"
#include "lv_drivers/indev/mouse.h"
#include <SDL2/SDL.h>

namespace pros {
namespace competition {
std::uint8_t get_status(void);

std::uint8_t is_autonomous(void);
std::uint8_t is_connected(void);
std::uint8_t is_disabled(void);
} // namespace competition
#define COMPETITION_CONNECTED (1 << 2)
uint32_t millis(void);
} // namespace pros

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
DWORD WINAPI taskKeyBoard(LPVOID pragma);
#else
void *taskLVGL(void *pragma);
void *taskKeyBoard(void *pragma);

#endif

#endif