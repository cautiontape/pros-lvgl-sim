#pragma once
#include "lvgl/lvgl.h"
#include "ncrapi/system/json.hpp"
#include "pros/vision.h"
#include <array>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
extern "C" {
LV_IMG_DECLARE(logo);
LV_IMG_DECLARE(field);
LV_FONT_DECLARE(ncr_font10);
}
typedef enum obj_flag {
    OBJ_BTNM_SON, //起始页面下的选项
    BTNM_START,   //按钮阵列 为了防止重复删除 这个也要放前面

    OBJ_COMPETITION,
    OBJ_DISABLED,
    OBJ_AUTONOMOUS,
    OBJ_OPCONTROL,
} obj_flag;

typedef enum task_flag {
    TASK_LOOP, //记录遥控模式下LOOP的TASK
    TASK_OTHER //其他模式下的线程
} task_flag;
namespace ncrapi {

class UserDisplay
{
  public:
    lv_obj_t *terminal; //终端
    std::vector<lv_obj_t *> terminalLabs;
    //样式
    lv_theme_t *theme;
    lv_style_t mainStyle;
    lv_style_t terminalStyle;

    std::array<lv_obj_t *, 6> displayObj = {nullptr};   //对象
    std::array<lv_task_t *, 2> displayTask = {nullptr}; //线程
    //标题栏
    lv_obj_t *otherLab = nullptr;
    lv_obj_t *loopLab = nullptr;
    lv_obj_t *logoObj = nullptr;
    //时间变量
    uint32_t loopTime = 0;
    uint32_t maxLoopTime = 0;
    uint32_t minLoopTime = 20;

    //自动赛选项按钮

    UserDisplay();
    void delObjs();
    void delTasks();
    void drawRectangle(lv_obj_t *obj, const int i, const pros::vision_object &data, lv_style_t *style);
    void createUserObj(obj_flag objname, const char *terminalText, lv_obj_t *parent = nullptr, const char *labText = nullptr);
    void createUserTask(task_flag taskName, lv_task_cb_t task, uint32_t loopTime, const char *terminalText, void *pragma = nullptr);
    void createCompe(lv_obj_t *parent = nullptr); //自动赛选择页面
    void createOpObj();
    static void loopTask(void *param);     //获取时间的线程
    void createTerminal(lv_obj_t *parent); //创建控制台
    void createStartObj(lv_obj_t *parent);
    void createVersion(lv_obj_t *parent);                                                                                                            //1
    void createConfig(lv_obj_t *parent);                                                                                                             //2
    void createVision(lv_obj_t *parent);                                                                                                             //3
    void createMaintenanceInfo(lv_obj_t *parent);                                                                                                    //4
    void createSysInfo(lv_obj_t *parent);                                                                                                            //5
    void createPidTest(lv_obj_t *parent);                                                                                                            //6
    void createOdom(lv_obj_t *parent);                                                                                                               //7
    void createCustomTest(lv_obj_t *parent);                                                                                                         //8
    void createExitBtn(obj_flag objname, const int x = LV_HOR_RES - 80, const int y = LV_VER_RES - 60, const int width = 50, const int high = 25);   //创建退出按钮
    void createSaveBtn(obj_flag objname, const int x = LV_HOR_RES - 140, const int y = LV_VER_RES - 60, const int width = 50, const int high = 25);  //创建保存按钮
    void createResetBtn(obj_flag objname, const int x = LV_HOR_RES - 140, const int y = LV_VER_RES - 60, const int width = 50, const int high = 25); //创建重制传感器按钮
    //void createMbox(obj_flag objname, const char *txt1, const char *txt2, const char *txt3, lv_btnm_action_t action);                                //创建一个消息框
    void init();
    static void hidenAction(lv_obj_t *btn, lv_event_t event); //隐藏按钮

    static void clearAction(lv_obj_t *btn, lv_event_t event);         //控制台清楚按钮
    static void compTabChoseAction(lv_obj_t *btn, lv_event_t event);  //用于自动赛选择的静态函数
    static void swAction(lv_obj_t *sw, lv_event_t event);             //COMP的SW开关
    static void compConfirmAction(lv_obj_t *btn, lv_event_t event);   //用于自动赛确认页面的静态函数
    static void confirmBtnInOdom(lv_obj_t *btn, lv_event_t event);    //用于ODOM自动赛选择的静态动作函数
    static void closeAction(lv_obj_t *btn, lv_event_t event);         //退出按钮的动作
    static void resetAction(lv_obj_t *btn, lv_event_t event);         //重置按钮的动作
    static void saveAction(lv_obj_t *btn, lv_event_t event);          //保存按钮的动作
    static lv_res_t startBtnmAction(lv_obj_t *btnm, const char *txt); //启动页面动作
    static lv_res_t upDownAction(lv_obj_t *btnm, const char *txt);    //upDownBtn的动作

    json _tempData;
    std::ostringstream ostr;

  private:
};
} // namespace ncrapi
extern std::unique_ptr<ncrapi::UserDisplay> userDisplay;
