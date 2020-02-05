#include "main.hpp"
std::unique_ptr<ncrapi::Logger> logger = nullptr; //系统日志
std::unique_ptr<ncrapi::UserDisplay> userDisplay = nullptr;

void initialize()
{

    //系统日志初始化
    logger = std::make_unique<ncrapi::Logger>();
    //显示初始化
    userDisplay = std::make_unique<ncrapi::UserDisplay>();
#if defined(__clang__) || defined(_MSC_VER)
    Sleep(5000); /*Just to let the system breath*/
#elif defined(__GNUC__)
    usleep(1000);
#else
#endif
    lv_obj_del(userDisplay->logoObj);
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
