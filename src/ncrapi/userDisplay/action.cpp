#include "ncrapi/system/logger.hpp"
#include "ncrapi/system/sysBase.hpp"
#include "ncrapi/userDisplay/userDisplay.hpp"

namespace ncrapi {
void UserDisplay::hidenAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn; /*Unused*/
    if (event == LV_EVENT_PRESSED)
    {
        logger->clearCount();
        if (lv_obj_get_y(userDisplay->terminal) == 0)
            lv_obj_set_y(userDisplay->terminal, -210);
        else
        {
            lv_obj_set_y(userDisplay->terminal, 0);
            lv_anim_t b;
            lv_anim_set_exec_cb(&b, userDisplay->terminal, (lv_anim_exec_xcb_t)lv_obj_set_y); /*Set the animator function and variable to animate*/
            lv_anim_set_time(&b, 500, 0);
            lv_anim_set_values(&b, -210, 0);              /*Set start and end values. E.g. 0, 150*/
            lv_anim_set_path_cb(&b, lv_anim_path_linear); /*Set path from `lv_anim_path_...` functions or a custom one.*/
            b.repeat = 0;
            lv_anim_set_ready_cb(&b, (lv_anim_ready_cb_t)lv_anim_del); /*Set a callback to call then animation is ready. (Optional)*/
            lv_anim_create(&b);
            lv_label_set_text(userDisplay->terminalLabs[0], logger->terminalStr[0].c_str());
            lv_label_set_text(userDisplay->terminalLabs[1], logger->terminalStr[1].c_str());
        }
    }
}
void UserDisplay::clearAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn;
    if (event == LV_EVENT_PRESSED)
    {
        logger->terminalStr[lv_tabview_get_tab_act(userDisplay->terminal)].clear();
        lv_label_set_text(userDisplay->terminalLabs[lv_tabview_get_tab_act(userDisplay->terminal)], "");
    }
}
/**
 * 标签栏按下后的动作
 * @param tab 标签
 * @param x   几号标签
 */
void UserDisplay::compTabChoseAction(lv_obj_t *tab, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        switch (lv_tabview_get_tab_act(tab))
        {
            case 0:
                sysData->jsonVal["自动赛"]["红方&蓝方"] = false;     //红方0
                sysData->jsonVal["自动赛"]["自动赛&纯自动"] = false; //红方0
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_RED;
                userDisplay->mainStyle.body.main_color = LV_COLOR_RED;
                break;
            case 1:
                sysData->jsonVal["自动赛"]["红方&蓝方"] = true;      //红方0
                sysData->jsonVal["自动赛"]["自动赛&纯自动"] = false; //蓝方
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_BLUE;
                userDisplay->mainStyle.body.main_color = LV_COLOR_BLUE;
                break;
            case 2:
                sysData->jsonVal["自动赛"]["自动赛&纯自动"] = true; //红方0
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_BLACK;
                userDisplay->mainStyle.body.main_color = LV_COLOR_BLACK;
                break;
            default:
                logger->error({"竞赛场控页面选项卡页面返回错误"});
                break;
        }
        //应用全局样式
        lv_theme_set_current(userDisplay->theme);
    }
}
//compe的SW的动作
void UserDisplay::swAction(lv_obj_t *sw, lv_event_t event) //SW的动作
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        // json *tempData = static_cast<json *>(lv_obj_get_free_ptr(sw));
        // *tempData = lv_sw_get_state(sw);
    }
}
/**
 * 自动赛选择时候的确认按钮的动作
 * @param  btn 要实现动作的按钮的指针
 * @return     返回不知道啥....
 */

// void UserDisplay::confirmBtnIncomp(lv_obj_t *btn, lv_event_t event)
// {
//     (void)btn;
//     sysData->saveData();
//     //获取开关状态
//     std::string str;
//     for (auto &it : sysData->jsonVal["自动赛"].items())
//     {
//         std::string tempStr = it.key();
//         auto pos = tempStr.find("&"); //查找间隔符号
//         if (pos != std::string::npos)
//         {
//             if (it.value())
//                 tempStr.erase(0, pos + 1);
//             else
//                 tempStr.erase(pos, tempStr.length());
//             str += (tempStr + "\n");
//         }
//         else
//             logger->error({"自动赛json选项设置错误 请用&间隔"});
//     }
//     // 创建确认页面
//     lv_obj_t *confirm = lv_obj_create(userDisplay->displayObj[OBJ_COMPETITION], nullptr);
//     lv_obj_set_size(confirm, lv_obj_get_width(userDisplay->displayObj[OBJ_COMPETITION]), lv_obj_get_height(userDisplay->displayObj[OBJ_COMPETITION]));
//     lv_obj_set_style(confirm, &userDisplay->mainStyle);
//     userDisplay->createStartObj(confirm);
//     //显示自动赛选项
//     lv_obj_t *autoinfoLab = lv_label_create(userDisplay->displayObj[BTNM_START], nullptr); //创建LAB条
//     userDisplay->ostr.clear();                                                             //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
//     userDisplay->ostr.str("");                                                             //2：调用str("")将缓冲区清零，清除脏数据
//     userDisplay->ostr << str << std::endl;
//     lv_label_set_text(autoinfoLab, userDisplay->ostr.str().c_str());
//     lv_obj_align(autoinfoLab, userDisplay->displayObj[BTNM_START], LV_ALIGN_IN_TOP_MID, 0, 0);
//     return LV_RES_INV;
// }
// void UserDisplay::confirmBtnInOdom(lv_obj_t *btn, lv_event_t event)
// {
//     (void)btn;
//     sysData->saveData();
//     lv_obj_del(userDisplay->displayObj[OBJ_COMPETITION]);
//     userDisplay->displayObj[OBJ_COMPETITION] = nullptr;
//     return LV_RES_INV;
// }

// void UserDisplay::swAction(lv_obj_t *sw, lv_event_t event) //SW的动作
// {
//     json *tempData = static_cast<json *>(lv_obj_get_free_ptr(sw));
//     *tempData = lv_sw_get_state(sw);
//     return LV_RES_OK;
// }
void UserDisplay::closeAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn; /*Unused*/
    if (userDisplay->displayObj[OBJ_BTNM_SON] != nullptr)
    {
        // if (!sysData->jsonVal["自动赛"]["红方&蓝方"]) //设置默认颜色
        //     userDisplay->displayObj[OBJ_BTNM_SON]->style_p->body.main_color = LV_COLOR_RED;
        // else
        //     userDisplay->displayObj[OBJ_BTNM_SON]->style_p->body.main_color = LV_COLOR_BLUE;
        lv_obj_del(userDisplay->displayObj[OBJ_BTNM_SON]);
        userDisplay->displayObj[OBJ_BTNM_SON] = nullptr;
    }
    if (userDisplay->displayTask[TASK_OTHER] != nullptr)
    {
        lv_task_del(userDisplay->displayTask[TASK_OTHER]);
        userDisplay->displayTask[TASK_OTHER] = nullptr;
    }
    // if (sysData->isOPcontrol == false)
    //     sysData->isOPcontrol = true;
    // if (sysData->test != 0)
    //     sysData->test = 0;
    // if (!sysData->pidDebugData.empty()) //如果不为空 择清零
    //     sysData->pidDebugData.clear();
}
// void UserDisplay::resetAction(lv_obj_t *btn, lv_event_t event)
// {
//     (void)btn; /*Unused*/
//     for (auto &it : sysData->obj)
//         it->resetAllSensors();
//     return LV_RES_OK;
// }
// void UserDisplay::saveAction(lv_obj_t *btn, lv_event_t event)
// {
//     chassis->isStopPid(true); //不要停止PID
//     json *tempData = static_cast<json *>(lv_obj_get_free_ptr(btn));
//     sysData->jsonVal = *tempData;
//     sysData->saveData();
//     return LV_RES_OK;
// }

// /**
//  * 按钮阵列的动作
//  * @param  btnm 按钮阵列
//  * @param  txt  按钮的名字
//  * @return      系统值
//  */
// lv_res_t UserDisplay::startBtnmAction(lv_obj_t *btnm, const char *txt)
// {
//     (void)btnm; /*Unused*/
//     if (!strcmp(txt, "系统信息"))
//         userDisplay->createSysInfo(userDisplay->displayObj[BTNM_START]); //1
//     else if (!strcmp(txt, "全局参数设置"))
//         userDisplay->createConfig(userDisplay->displayObj[BTNM_START]); //2 创建CONFIGSET页面
//     else if (!strcmp(txt, "维护信息"))
//         userDisplay->createMaintenanceInfo(userDisplay->displayObj[BTNM_START]); //3
//     else if (!strcmp(txt, "视觉传感器设置"))
//         userDisplay->createVision(userDisplay->displayObj[BTNM_START]); //4创建视觉页面
//     else if (!strcmp(txt, "版本号"))
//         userDisplay->createVersion(userDisplay->displayObj[BTNM_START]); //5
//     else if (!strcmp(txt, "自定义测试"))
//         userDisplay->createCustomTest(userDisplay->displayObj[BTNM_START]); //6
//     else if (!strcmp(txt, "PID调试"))
//         userDisplay->createPidTest(userDisplay->displayObj[BTNM_START]); //7
//     else if (!strcmp(txt, "ODOM测试"))
//         userDisplay->createOdom(userDisplay->displayObj[BTNM_START]); //8
//     logger->info({"选择 ", txt});
//     return LV_RES_INV;
// }
// lv_res_t UserDisplay::upDownAction(lv_obj_t *btnm, const char *txt)
// {
//     lv_obj_t *labPtr = static_cast<lv_obj_t *>(lv_obj_get_free_ptr(btnm));
//     json *valPtr = static_cast<json *>(lv_obj_get_free_ptr(labPtr)); //从btm获取关联的valus
//     static uint32_t time = 0;
//     static uint32_t flag = 1;
//     if (lv_tick_elaps(time) <= 200)
//         flag += 10;
//     else
//         flag = 1;
//     if (valPtr->is_number_integer())
//     {
//         int temp = *valPtr;
//         if (!strcmp(txt, "+"))
//             temp += 1;
//         else if (!strcmp(txt, "-"))
//             temp -= 1;
//         *valPtr = temp;
//     }
//     else if (valPtr->is_boolean())
//     {
//         bool temp = *valPtr;
//         if (!strcmp(txt, "+"))
//             temp = !temp;
//         else if (!strcmp(txt, "-"))
//             temp = !temp;
//         *valPtr = temp;
//     }
//     else if (valPtr->is_number_float())
//     {
//         double_t temp = *valPtr;
//         if (!strcmp(txt, "+"))
//             temp += 0.001 * flag;
//         else if (!strcmp(txt, "-"))
//             temp -= 0.001 * flag;
//         std::stringstream oss;     //主要为了去掉小数点后多余的0 默认3位
//         oss.setf(std::ios::fixed); //用定点格式显示浮点数,不会用科学计数法表示
//         oss.precision(3);          //由于用了定点格式，设置变为了保留4位小数
//         oss << temp;
//         oss >> *valPtr;
//     }
//     lv_label_set_text(labPtr, valPtr->dump().c_str());
//     time = lv_tick_get();
//     return LV_RES_OK;
// }

} // namespace ncrapi