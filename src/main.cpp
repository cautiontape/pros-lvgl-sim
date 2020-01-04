#include "main.hpp"
#include "lv_examples\lv_tests\lv_test_objx\lv_test_img\lv_test_img.h"
int main(int argc, char **argv)
{
    // system("chcp 65001");
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();
#if defined(_WIN32)
    std::cout << "win32" << std::endl;
#elif defined(_WIN64)
    std::cout << "win64" << std::endl;
#elif defined(_linux)
    std::cout << "linux" << std::endl;
#else
    std::cout << "unkonw system" << std::endl;
#endif
#if defined(__GNUC__)
    std::cout << "gcc" << std::endl;
#elif defined(__clang__)
    std::cout << "clang" << std::endl;
#elif defined(_MSC_VER)
    std::cout << "msvc" << std::endl;
#else
    std::cout << "unkonw compiler" << std::endl;
#endif
    std::cout << "你好 大红色笔" << std::endl;
    lv_test_img_1();
    // demo_create();
    // benchmark_create();
    // lv_test_theme_1(lv_theme_night_init(210, NULL));
    // lv_test_theme_1(lv_theme_night_init(100, NULL));
    // lv_test_theme_1(lv_theme_material_init(210, NULL));
    // lv_test_theme_1(lv_theme_alien_init(210, NULL));
    // lv_test_theme_1(lv_theme_zen_init(210, NULL));
    // lv_test_theme_1(lv_theme_nemo_init(210, NULL));
    // lv_test_theme_1(lv_theme_mono_init(210, NULL));
    // lv_test_theme_1(lv_theme_default_init(210, NULL));
    // lv_tutorial_keyboard(kb_indev);
    while (1)
    {
        /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        Sleep(10); /*Just to let the system breathe */
    }

    return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
static void hal_init(void)
{
    /* Add a display
   * Use the 'monitor' driver which creates window on PC's monitor to simulate a
   * display*/
    monitor_init();

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/

    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);

    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
   * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb =
        mouse_read; /*This function will be called periodically (by the library)
                     to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    /* If the PC keyboard driver is enabled in`lv_drv_conf.h`
   * add this as an input device. It might be used in some examples. */
#if USE_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    kb_indev = lv_indev_drv_register(&kb_drv);
#endif

    /* Tick init.
   * You have to call 'lv_tick_inc()' in every milliseconds
   * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

/**
 * A task to measure the elapsed time for LittlevGL
 * @param data unused
 * @return never return
 */
static int tick_thread(void *data)
{
    while (1)
    {
        lv_tick_inc(5);
        SDL_Delay(5); /*Sleep for 1 millisecond*/
    }

    return 0;
}
