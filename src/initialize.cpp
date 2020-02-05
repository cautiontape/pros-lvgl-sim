#include "main.hpp"
std::unique_ptr<ncrapi::Logger> logger = nullptr; //系统日志
std::unique_ptr<ncrapi::UserDisplay> userDisplay = nullptr;

void initialize()
{
#if defined(_WIN32)
    std::cout << "win32" << std::endl;
#elif defined(_WIN64)
    std::cout << "win64" << std::endl;
#elif defined(__linux)
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
#elif defined(__ARM_EABI__)
    std::cout << "arm-none-eabi" << std::endl;
#else
    std::cout << "unkonw compiler" << std::endl;
#endif
    //系统日志初始化
    logger = std::make_unique<ncrapi::Logger>();
    //显示初始化
    userDisplay = std::make_unique<ncrapi::UserDisplay>();
}
void competition_initialize()
{
    // userDisplay->createCompe();
}
/**
 * 场控没开自动赛 没开手动 完全禁止的时候使用的函数
  */
void disabled()
{
    // userDisplay->delTasks();
    // userDisplay->delObjs();
    // userDisplay->createUserObj(OBJ_DISABLED, "obj_disabled", nullptr, "场控关闭状态");
    // for (auto &it : sysData->obj)
    //     it->setMode(0); //将所有部件都重置为0模式
    // if (autoTask != nullptr)
    // {
    //     if (autoTask->get_state() != 4)
    //     {
    //         autoTask->remove();
    //         delete autoTask;
    //         logger->debug({"自动赛线程 自动赛外 删除成功!"});
    //     }
    //     autoTask = nullptr;
    // }
}
