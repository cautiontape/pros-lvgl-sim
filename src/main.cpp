#include "main.hpp"
#include <conio.h>
#if (TEST_MODE == 1)

int main(int argc, char **argv)
{
    /*Initialize LittlevGL*/
    lv_init();
    /*Initialize the HAL (display, input devices, tick) for LittlevGL*/
    hal_init();
#if defined(_WIN32) || defined(_WIN64)
    HANDLE ret1 = CreateThread(nullptr, 0, taskLVGL, nullptr, 0, nullptr);
    // Sleep(5000); /*Just to let the system breath*/
#else
    pthread_t id; //pthread_t多线程标识符
    int ret1 = pthread_create(&id, nullptr, taskLVGL, nullptr);
    // usleep(1000); /*Just to let the system breath*/
#endif
    lv_indev_drv_t real_kb_drv;
    keyboard_init();
    real_kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    real_kb_drv.read_cb = keyboard_read;
    lv_indev_data_t kbDate;
    keyboard_read(&real_kb_drv, &kbDate);
    uint32_t lastKbVal = kbDate.key;
    while (1)
    {
        keyboard_read(&real_kb_drv, &kbDate);
        std::cout << "now:" << kbDate.key << "last:" << lastKbVal << std::endl;
        if (lastKbVal != kbDate.key)
            switch (kbDate.key)
            {

                case 49:
                    initialize();
                    lastKbVal = 49;
                    break;
                case 50:
                    autonomous();
                    lastKbVal = 50;
                    break;
                case 51:
                    competition_initialize();
                    lastKbVal = 51;
                    break;
                case 52:
                    disabled();
                    lastKbVal = 52;
                    break;
                default:
                    break;
            }
#if defined(_WIN32) || defined(_WIN64)
        Sleep(10); /*Just to let the system breath*/
#else
        usleep(5 * 1000);
#endif
    }
    return 0;
}
#else
void opcontrol()
{
}
#endif