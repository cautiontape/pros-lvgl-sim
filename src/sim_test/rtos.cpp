#include "ncrapi/robotSet.hpp"
#if (SIM_MODE == 1)
#include "lvgl/lvgl.h"
#include "pros/rtos.hpp"

namespace pros {
namespace competition {
/**
 * Get the current status of the competition control.
 *
 * \return The competition control status as a mask of bits with
 * COMPETITION_{ENABLED,AUTONOMOUS,CONNECTED}.
 */
std::uint8_t get_status(void)
{
    return 0;
}

std::uint8_t is_autonomous(void)
{
    return 0;
}
std::uint8_t is_connected(void)
{
    return 0;
}
std::uint8_t is_disabled(void)
{
    return 0;
}
} // namespace competition
namespace c {
uint32_t millis(void)
{
    return lv_tick_get();
}
} // namespace c
} // namespace pros
#endif