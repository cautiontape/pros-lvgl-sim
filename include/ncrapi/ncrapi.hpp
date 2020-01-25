#pragma once
// #include "ncrapi/chassis/chassisAutoAiming.hpp"
// #include "ncrapi/generic//roulette.hpp"
// #include "ncrapi/generic/intake.hpp"
// #include "ncrapi/generic/jack.hpp"
// #include "ncrapi/generic/lift.hpp"
// #include "ncrapi/robotSet.hpp"
// #include "ncrapi/system/sysUser.hpp"
// #include "ncrapi/system/visionData.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"
#include "sim_test/test_config.hpp"

#define NCR_VERSION_STRING "9.7.1"

// //通用部件
// extern std::shared_ptr<pros::Controller> joy1;
// extern std::shared_ptr<pros::Controller> joy2;
// extern std::shared_ptr<ncrapi::ChassisOdom> chassis; //底盘
// extern std::shared_ptr<ncrapi::Lift> lift;           //升降
// extern std::shared_ptr<ncrapi::Jack> jack;           //千斤顶
// extern std::shared_ptr<ncrapi::CapIntake> intake;    //夹子
// extern std::shared_ptr<ncrapi::Roulette> roulette;   //吸吐
// extern pros::Task *autoTask;

// static void taskAuto(void *para)
// {
//     uint32_t now = pros::millis();
//     while (true)
//     {
// #if defined(No_4)
//         lift->holding();
//         intake->holding();
// #elif defined(No_1) || defined(No_6) || defined(No_9)
//         jack->holding();
//         roulette->holding();
// #else
//         jack->holding();
//         roulette->holding();
//         lift->holding();
// #endif
//         pros::Task::delay_until(&now, 10);
//     }
// }
// /**
//   * 用于机器人姿态计算的多线程启动函数
//  * @param para NULL
//  */
// static void taskOdom(void *para)
// {
//     chassis->odomLoop();
// }
// void skillAuto(const json &jsonVal, ncrapi::Timer &autoTimer);
// void userauto(const json &jsonVal, ncrapi::Timer &autoTimer);
// void cutomTest();