#include "ncrapi/robotSet.hpp"
#if (SIM_MODE == 1)
#include "lvgl/lvgl.h"
#include "pros/rtos.hpp"
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif (__linux)
#include <pthread.h>
#include <unistd.h>
#else
#endif
namespace pros {

namespace c {
uint32_t millis(void)
{
    return lv_tick_get();
}
void delay(const uint32_t milliseconds)
{
#if defined(_WIN32) || defined(_WIN64)
    Sleep(milliseconds);
#else
    usleep(milliseconds); /*Just to let the system breath*/
#endif
}
} // namespace c
} // namespace pros
#endif