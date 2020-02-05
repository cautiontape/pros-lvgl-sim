#pragma once
#include "lvgl/lvgl.h"
#include "ncrapi/util/timer.hpp"
#include <memory>
#include <string>
namespace ncrapi {

class Logger
{
  public:
    typedef enum LEVEL {
        ERROR,
        WARNNING,
        DEBUG,
        INFO

    } LEVEL;
    Logger();
    /**
     * @brief 打印红色错误信息到控制台和机器人内置控制台
     * 
     * @param val 具体格式是logger->error({"要打印的东西",std::to_string(变量名)});
     */
    void error(std::initializer_list<std::string> val);
    /**
     * @brief 打印黄色警告信息到控制台和机器人内置控制台
     * 
     * @param val 具体格式是logger->error({"要打印的东西",std::to_string(变量名)});
     */
    void warnning(std::initializer_list<std::string> val);
    /**
     * @brief 打印蓝色调试信息到控制台和机器人内置控制台
     * 
     * @param val 具体格式是logger->error({"要打印的东西",std::to_string(变量名)});
     */
    void debug(std::initializer_list<std::string> val);
    /**
     * @brief 打印白色普通信息到控制台和机器人内置控制台
     * 
     * @param val 具体格式是logger->error({"要打印的东西",std::to_string(变量名)});
     */
    void info(std::initializer_list<std::string> val);
    /**
     * @brief 清理error和warnning的计数器
     * 
     */
    void clearCount();
    /**
     * @brief DEBUG模块的线程
     * 
     */
    void loop();
    std::string terminalStr[2];
    lv_obj_t *errorLabs = nullptr, *warnningLabs = nullptr; //控制台上的显示错误数量的lab

  private:
    bool isComp = false;
    void output(std::initializer_list<std::string> &val);
    std::string _str;
    size_t _errorCount = 0, _warnningCount = 0;
};
} // namespace ncrapi
extern std::unique_ptr<ncrapi::Logger> logger;
// static void taskLogger(void *para)
// {
//     logger->loop();
// }