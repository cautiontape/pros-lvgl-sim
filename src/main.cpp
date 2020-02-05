#include "main.hpp"
#if (TEST_MODE == 1)
int main(int argc, char **argv)
{
    /*Initialize LittlevGL*/
    lv_init();
    /*Initialize the HAL (display, input devices, tick) for LittlevGL*/
    hal_init();
#if defined(_WIN32) || defined(_WIN64)
    HANDLE ret1 = CreateThread(nullptr, 0, taskLVGL, nullptr, 0, nullptr);
    HANDLE ret2 = CreateThread(nullptr, 0, taskKeyBoard, nullptr, 0, nullptr);
    // Sleep(5000); /*Just to let the system breath*/
#else
    pthread_t id; //pthread_t多线程标识符
    int ret1 = pthread_create(&id, nullptr, taskLVGL, nullptr);
    int ret2 = pthread_create(&id, nullptr, taskKeyBoard, nullptr);
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