#include "main.hpp"
#if (TEST_MODE == 1)
int main(int argc, char **argv)
{
    /*Initialize LittlevGL*/
    lv_init();
    /*Initialize the HAL (display, input devices, tick) for LittlevGL*/
    hal_init();
#if defined(_WIN32) || defined(_WIN64)
    HANDLE ret = CreateThread(nullptr, 0, task1, nullptr, 0, nullptr);
    // Sleep(5000); /*Just to let the system breath*/
#else
    pthread_t id; //pthread_t多线程标识符
    int ret = pthread_create(&id, nullptr, task1, nullptr);
    // usleep(1000); /*Just to let the system breath*/
#endif

    initialize();
    autonomous();
    while (1)
    {
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