#include "sim_test/test_config.hpp"

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
    return (1 << 2);
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
uint32_t millis(void)
{
#if defined(_WIN32) || defined(_WIN64)
    return GetTickCount();
#elif defined(__linux)
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
}
} // namespace pros
  /**
 * Print the memory usage periodically
 * @param param
 */
void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n", (int)mon.total_size - mon.free_size,
           mon.used_pct,
           mon.frag_pct,
           (int)mon.free_biggest_size);
}
/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
int tick_thread(void *data)
{
    (void)data;

    while (1)
    {
        SDL_Delay(5);   /*Sleep for 5 millisecond*/
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}
void hal_init(void)
{
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    /*Create a display buffer*/
    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[480 * 10];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, 480 * 10);

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush; /*Used when `LV_VDB_SIZE != 0` in lv_conf.h (buffered drawing)*/
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read; /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

    /*Set a cursor for the mouse*/
    lv_obj_t *cursor_obj = lv_img_create(lv_disp_get_scr_act(NULL), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);                        /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);                          /*Connect the image  object to the driver*/

    /* Tick init.
     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about how much time were elapsed
     * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);

    /* Optional:
     * Create a memory monitor task which prints the memory usage in periodically.*/
    lv_task_create(memory_monitor, 3000, LV_TASK_PRIO_MID, NULL);
}
#if defined(_WIN32) || defined(_WIN64)
DWORD WINAPI task1(LPVOID pragma)
{
    (void)pragma;
    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        Sleep(10); /*Just to let the system breath*/
    }
}
#else
void *task1(void *pragma)
{
    (void)pragma;
    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5 * 1000); /*Just to let the system breath*/
    }
}
#endif
