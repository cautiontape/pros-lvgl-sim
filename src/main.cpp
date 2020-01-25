#include "main.hpp"

int main(int argc, char **argv)
{

#if defined(_WIN32) || defined(_WIN64)
    //HANDLE ret = CreateThread(nullptr, 0, task1, nullptr, 0, nullptr);
    //Sleep(5000); /*Just to let the system breath*/
#else
    pthread_t id; //pthread_t多线程标识符
    int ret = pthread_create(&id, nullptr, task1, nullptr);
    usleep(1000); /*Just to let the system breath*/
#endif
    /*Initialize LittlevGL*/
    lv_init();
    /*Initialize the HAL (display, input devices, tick) for LittlevGL*/
    hal_init();
    initialize();
    autonomous();
    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
#if defined(_WIN32) || defined(_WIN64)
        Sleep(10); /*Just to let the system breath*/
#else
        usleep(5 * 1000);
#endif
    }
    return 0;
}