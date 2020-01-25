#pragma once
#include "lvgl/lvgl.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
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
#elif (_linux)
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
namespace pros {
namespace competition {
/**
 * Get the current status of the competition control.
 *
 * \return The competition control status as a mask of bits with
 * COMPETITION_{ENABLED,AUTONOMOUS,CONNECTED}.
 */
std::uint8_t get_status(void);
std::uint8_t is_autonomous(void);
std::uint8_t is_connected(void);
std::uint8_t is_disabled(void);
} // namespace competition
#define COMPETITION_CONNECTED (1 << 2)
uint32_t millis(void)
{
    return GetTickCount();
}
} // namespace pros
#endif