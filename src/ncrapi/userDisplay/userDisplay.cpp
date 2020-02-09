#include "ncrapi/ncrapi.hpp"
#include "pros/misc.hpp"
#include <iomanip>


namespace ncrapi {

UserDisplay::UserDisplay()
{
    /*初始化外星人主题*/
    theme = lv_theme_alien_init(100, &ncr_font10);
    //设置 tabview样式
    theme->style.tabview.indic->body.padding.inner = 1;    /*滚动条宽*/
    theme->style.tabview.btn.rel->text.font = &ncr_font10; //重新设置字体
    theme->style.tabview.indic->body.padding.bottom = 1;
    theme->style.tabview.indic->body.padding.top = 1;
    theme->style.tabview.indic->body.padding.left = 1;
    theme->style.tabview.indic->body.padding.right = 1;
    theme->style.tabview.btn.rel->body.padding.left = 1;   //释放按钮的垂直填充应用于所有按钮
    theme->style.tabview.btn.rel->body.padding.right = 1;  //释放按钮的垂直填充应用于所有按钮
    theme->style.tabview.btn.rel->body.padding.top = 1;    //释放按钮的垂直填充应用于所有按钮
    theme->style.tabview.btn.rel->body.padding.bottom = 1; //释放按钮的垂直填充应用于所有按钮
    theme->style.tabview.bg->body.padding.left = 1;        //背景上下填充
    theme->style.tabview.bg->body.padding.right = 1;       //背景左右填充
    theme->style.tabview.bg->body.padding.top = 1;         //背景上下填充
    theme->style.tabview.bg->body.padding.bottom = 1;      //背景左右填充
    theme->style.tabview.bg->body.border.width = 1;
    theme->style.tabview.bg->body.padding.inner = 8; /*滚动条宽*/
    lv_theme_set_current(theme);
    //全局样式
    lv_style_copy(&mainStyle, &lv_style_pretty_color); //拷贝当前按钮样式
    mainStyle.text.font = &ncr_font10;
    mainStyle.body.padding.left = 5;
    mainStyle.body.padding.right = 5;
    mainStyle.body.padding.top = 5;
    mainStyle.body.padding.bottom = 5;
    mainStyle.body.grad_color = LV_COLOR_BLACK; //渐变色黑色

    //创建控制台
    createTerminal(lv_scr_act());
    //设置LOGO
    logoObj = lv_img_create(terminal, nullptr);
    lv_img_set_src(logoObj, &logo);
    lv_anim_t a;
    lv_obj_set_x(logoObj, LV_HOR_RES_MAX - lv_obj_get_width(logoObj));
    lv_anim_set_exec_cb(&a, logoObj, (lv_anim_exec_xcb_t)lv_obj_set_y); /*Set the animator function and variable to animate*/
    lv_anim_set_time(&a, 5000, 0);
    lv_anim_set_values(&a, -lv_obj_get_height(logoObj), (LV_VER_RES_MAX - lv_obj_get_height(logoObj)) / 2); /*Set start and end values. E.g. 0, 150*/
    lv_anim_set_path_cb(&a, lv_anim_path_bounce);                                                           /*Set path from `lv_anim_path_...` functions or a custom one.*/
    a.repeat = 0;
    lv_anim_set_ready_cb(&a, (lv_anim_ready_cb_t)lv_anim_del); /*Set a callback to call then animation is ready. (Optional)*/
    lv_anim_create(&a);                                        /*Start the animation*/

    //应用全局样式
    logger->info({I18N_USERDISPALY_CLASS I18N_CREATE_SUCCESSFUL});
}
void UserDisplay::createTerminal(lv_obj_t *parent)
{
    std::vector<std::string> Level = {I18N_ERROR, I18N_WARNNING};
    //创建终端
    terminal = lv_tabview_create(parent, nullptr);
    lv_obj_set_size(terminal, LV_HOR_RES, LV_VER_RES); //设置页面大小
    for (auto &it : Level)
    {
        lv_obj_t *tabs = lv_tabview_add_tab(terminal, it.c_str());
        terminalLabs.push_back(lv_label_create(tabs, nullptr));
        lv_label_set_text(terminalLabs.back(), "");
        lv_label_set_recolor(terminalLabs.back(), true);
    }
    terminalStyle = *lv_obj_get_style(terminal);
    lv_obj_set_style(terminal, &terminalStyle);
    lv_obj_t *clearBtn = lv_btn_create(terminal, nullptr);
    lv_obj_set_size(clearBtn, 50, 25);
    lv_obj_align(clearBtn, terminal, LV_ALIGN_IN_TOP_RIGHT, -10, 30);
    lv_obj_t *btnLab = lv_label_create(clearBtn, nullptr);
    lv_label_set_text(btnLab, "clear");
    lv_obj_set_event_cb(clearBtn, clearAction); //设置动作的通用函数

    lv_obj_set_parent(terminal, lv_obj_get_parent(terminal));
    //设置TERMINAL上的按钮
    lv_obj_t *hidenBtn = lv_btn_create(terminal, nullptr);
    lv_obj_set_size(hidenBtn, LV_HOR_RES, 30);
    lv_obj_set_pos(hidenBtn, 0, LV_VER_RES - 30);
    lv_obj_set_event_cb(hidenBtn, hidenAction); //设置动作的通用函数
    //error warnning 指示灯
    logger->errorLabs = lv_label_create(terminal, nullptr);
    lv_obj_set_pos(logger->errorLabs, LV_HOR_RES / 2 - 10, LV_VER_RES - 25);
    lv_label_set_recolor(logger->errorLabs, true);
    lv_label_set_text(logger->errorLabs, "#FF0000 0#");
    logger->warnningLabs = lv_label_create(terminal, nullptr);
    lv_obj_set_pos(logger->warnningLabs, LV_HOR_RES / 2 + 15, LV_VER_RES - 25);
    lv_label_set_recolor(logger->warnningLabs, true);
    lv_label_set_text(logger->warnningLabs, "#CCFF00 0#");

    //循环时间条
    loopLab = lv_label_create(terminal, nullptr);
    lv_obj_set_pos(loopLab, LV_HOR_RES / 2 + 50, LV_VER_RES - 25);
    lv_label_set_text(loopLab, "");
}
void UserDisplay::createUserObj(obj_flag objname, const char *terminalText, lv_obj_t *parent, const char *labText)
{
    if (displayObj[objname] == nullptr)
    {
        if (parent == nullptr)
        {
            displayObj[objname] = lv_obj_create(lv_scr_act(), nullptr);
            lv_obj_set_size(displayObj[objname], LV_HOR_RES, LV_VER_RES - 30); //设置页面大小
            lv_obj_set_y(displayObj[objname], 30);                             //设置位置
            lv_obj_set_parent(terminal, lv_obj_get_parent(terminal));
        }
        else
        {
            displayObj[objname] = lv_obj_create(parent, nullptr);
            lv_obj_set_size(displayObj[objname], lv_obj_get_width(parent), lv_obj_get_height(parent));
            createExitBtn(objname); //退出按钮
        }
        lv_obj_set_style(displayObj[objname], &mainStyle); //设置样式
        logger->info({I18N_USERDISPALY_CLASS ":", terminalText, I18N_CREATE_SUCCESSFUL});
    }
    else
        logger->debug({I18N_USERDISPALY_CLASS ":", terminalText, I18N_ALREADYEXIST});

    if (labText != nullptr)
    {
        lv_obj_t *lab = lv_label_create(displayObj[objname], nullptr);
        lv_label_set_text(lab, labText);
    }
}
/**
 * 使用LVGLTASK函数创建一个线程
 * @param taskName 线程名称
 * @param task 线程函数
 * @param loopTime  循环时间
 * @param terminalText 线程名称
 */
void UserDisplay::createUserTask(task_flag taskName, lv_task_cb_t task, uint32_t loopTime, const char *terminalText, void *pragma)
{
    if (displayTask[taskName] == nullptr)
    {
        displayTask[taskName] = lv_task_create(task, loopTime, LV_TASK_PRIO_LOW, pragma);
        logger->info({I18N_USERDISPALY_CLASS I18N_THREAD ":", terminalText, I18N_CREATE_SUCCESSFUL});
    }
    else
        logger->warnning({I18N_USERDISPALY_CLASS I18N_THREAD ":", terminalText, I18N_ALREADYEXIST});
}
void UserDisplay::init()
{

    if (!sysData->jsonVal["自动赛"]["红方&蓝方"]) //设置默认颜色
    {
        theme->style.tabview.bg->body.main_color = LV_COLOR_RED;
        mainStyle.body.main_color = LV_COLOR_RED;
    }
    else
    {
        theme->style.tabview.bg->body.main_color = LV_COLOR_BLUE;
        mainStyle.body.main_color = LV_COLOR_BLUE;
    }
    lv_obj_t *robotInfoLab = lv_label_create(terminal, nullptr);
    lv_obj_set_pos(robotInfoLab, 10, LV_VER_RES - 25);
    std::string userInfo = sysData->jsonVal["系统信息"]["用户"].get<std::string>() + " " + sysData->jsonVal["系统信息"]["队伍编号"].get<std::string>() + " 版本号:" + NCR_VERSION_STRING;
    lv_label_set_text(robotInfoLab, userInfo.c_str());
    //创建mbox
    lv_obj_t *mbox = lv_mbox_create(lv_scr_act(), nullptr);
    lv_mbox_set_text(mbox, I18N_USERDISPALY_MBOX);
    static const char *btns[] = {I18N_RED_ALLIANCE, I18N_BLUD_ALLIANCE, ""}; /*Button description. '\221' lv_btnm like control char*/
    lv_mbox_add_btns(mbox, btns);
    lv_obj_set_width(mbox, 250);
    lv_obj_align(mbox, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 20); /*Align to the corner*/
    lv_obj_set_event_cb(mbox, mBoxAction);
    lv_theme_set_current(theme);
}
/**
 * 删除所有线程 
 */
void UserDisplay::delTasks()
{
    unsigned int flag = 1;
    for (auto &it : displayTask)
    {
        if (it != nullptr)
        {
            lv_task_del(it);
            it = nullptr;
            logger->info({I18N_DELETE I18N_USERDISPALY_CLASS I18N_THREAD ":", std::to_string(flag)});
            flag++;
        }
    }
}
/**
 * 删除所有对象 
 */
void UserDisplay::delObjs()
{
    unsigned int flag = 1;
    for (auto &it : displayObj)
    {
        if (it != nullptr)
        {
            lv_obj_del(it);
            it = nullptr;
            logger->info({I18N_DELETE I18N_USERDISPALY_CLASS ":", std::to_string(flag)});
            flag++;
        }
    }
}
void UserDisplay::createCompe(lv_obj_t *parent)
{
    if (parent == nullptr)
    {
        delTasks();
        delObjs();
        createUserObj(OBJ_COMPETITION, I18N_COMPETITION_INIT);
    }
    else
        createUserObj(OBJ_COMPETITION, I18N_COMPETITION_INIT, parent);
    if (lv_obj_get_y(userDisplay->terminal) == 0)
        lv_obj_set_y(userDisplay->terminal, -210);
    //创建标签栏
    lv_obj_t *tab = lv_tabview_create(displayObj[OBJ_COMPETITION], nullptr);
    lv_obj_set_size(tab, lv_obj_get_width(displayObj[OBJ_COMPETITION]), lv_obj_get_height(displayObj[OBJ_COMPETITION]));
    lv_obj_t *redTab = lv_tabview_add_tab(tab, I18N_RED_ALLIANCE);
    lv_obj_t *blueTab = lv_tabview_add_tab(tab, I18N_BLUD_ALLIANCE);
    lv_obj_t *skillTab = lv_tabview_add_tab(tab, I18N_SKILL_AUTO);
    //根据系统设置标签
    lv_tabview_set_tab_act(tab, sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE].get<uint16_t>(), LV_ANIM_OFF); //设置默认红方还是蓝方
    //进去后默认颜色
    if (!sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE]) //红方0
    {
        userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_RED;
        userDisplay->mainStyle.body.main_color = LV_COLOR_RED;
    }
    else
    {
        userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_BLUE;
        userDisplay->mainStyle.body.main_color = LV_COLOR_BLUE;
    }
    /*当选项卡按下后进行的操作*/
    lv_obj_set_event_cb(tab, compTabChoseAction);

    std::vector<std::pair<lv_obj_t *, lv_obj_t *>> compSw; //
    int nums = sysData->jsonVal[I18N_AUTO].size() - 2;     //计算单位数量 一开始默认有两个不显示的 注意计数从1开始 0不算
    int posX = 10, posY = 30;
    //创建各种开关和文本条 附带位置设置
    for (auto &it : sysData->jsonVal[I18N_AUTO].items())
    {
        if (it.key() != (I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE) && it.key() != (I18N_AUTO "&" I18N_SKILL_AUTO))
        {
            compSw.push_back(std::make_pair(lv_label_create(displayObj[OBJ_COMPETITION], nullptr), lv_sw_create(displayObj[OBJ_COMPETITION], nullptr))); //创建文本条和开关
            lv_label_set_text(compSw.back().first, it.key().c_str());                                                                                    /*设置文字*/
            lv_obj_set_size(compSw.back().second, 60, lv_obj_get_height(compSw.back().first));                                                           //这里的30要跟POSY 初值对应
            if (it.value().get<bool>())
                lv_sw_on(compSw.back().second, LV_ANIM_OFF); //设置按钮默认值
            else
                lv_sw_off(compSw.back().second, LV_ANIM_OFF); //设置按钮默认值
            //位置设置
            lv_obj_set_pos(compSw.back().first, posX, posY);                                        //设置lab文字的位置
            lv_obj_align(compSw.back().second, compSw.back().first, LV_ALIGN_OUT_RIGHT_MID, 10, 0); //设置开关的位置
            lv_obj_set_event_cb(compSw.back().second, swAction);                                    //设置按钮的动作
            lv_obj_set_user_data(compSw.back().second, &it.value());                                //关联按钮和json
            if (lv_obj_get_x(compSw.back().second) > 230)                                           //key表示偶数换行 it.szie()表示每行总共有2个数一个KEY 一个VAL
            {
                posX = 10;
                posY += (lv_obj_get_height(compSw.back().second) * 2);
            }
            else
                posX = lv_obj_get_width(displayObj[OBJ_COMPETITION]) / 2 + 30;
        }
    }
    //确认按钮设置
    lv_obj_t *confirmBtn = lv_btn_create(displayObj[OBJ_COMPETITION], nullptr); //创建确认开关
    lv_obj_t *confirmLab = lv_label_create(confirmBtn, nullptr);                //创建确认开关文本 这里设置按钮为父级
    lv_label_set_text(confirmLab, "Y\nE\nS");
    lv_obj_set_size(confirmBtn, 40, 100); //大小设置
    //设置确定按钮和其文本框的位置
    lv_obj_align(confirmBtn, displayObj[OBJ_COMPETITION], LV_ALIGN_CENTER, 0, 0);

    //确认按钮的动作
    if (parent == nullptr)
        lv_obj_set_event_cb(confirmBtn, compConfirmAction);
    else
        ; //lv_obj_set_event_cb(confirmBtn, compConfirmAction);
    //调用按钮页面
    //TODO 技能赛的动作
}
/**
 * 创建遥控模块页面 
 */
void UserDisplay::createOpObj()
{
    delTasks();
    delObjs();
    createUserObj(OBJ_OPCONTROL, I18N_OPCONTROL);
    if (!pros::competition::is_connected()) //没插场控
        createStartObj(displayObj[OBJ_OPCONTROL]);
    createUserTask(TASK_LOOP, loopTask, 100, I18N_CYCLE_TIME_BAR);
}
void UserDisplay::createStartObj(lv_obj_t *parent)
{
    // if (visionData != nullptr)
    //     visionData->setSig(sysData->jsonVal, sysData->jsonVal["视觉信息"]["数据"].get<int>());
    static const char *startBtnm[] = {I18N_SYSTEM_INFO, I18N_BTNM_CUSTOM_TEST, "\n",
                                      I18N_BTNM_GOBAL_CONFIG_SET, I18N_BTNM_MAINTENANCE_INFO, "\n",
                                      I18N_BTNM_PID_SET, I18N_BTNM_VISION_SET, "\n",
                                      I18N_BTNM_ODOM_SET, I18N_BTNM_VERSION, ""};
    if (displayObj[BTNM_START] == nullptr)
        displayObj[BTNM_START] = lv_btnm_create(parent, nullptr); //创建按钮集群

    lv_btnm_set_map(displayObj[BTNM_START], startBtnm);
    lv_obj_set_size(displayObj[BTNM_START], lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_set_event_cb(displayObj[BTNM_START], startBtnmAction);
}

void UserDisplay::createExitBtn(obj_flag objname, const int x, const int y, const int width, const int high) //创建退出按钮
{
    lv_obj_t *exitBtn = lv_btn_create(displayObj[objname], nullptr);
    lv_obj_set_pos(exitBtn, x, y);
    lv_obj_set_size(exitBtn, width, high);
    lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
    lv_label_set_text(exitLab, "exit");
    lv_obj_set_event_cb(exitBtn, closeAction); //设置动作的通用函数
}
void UserDisplay::createSaveBtn(obj_flag objname, const int x, const int y, const int width, const int high) //创建退出按钮
{
    lv_obj_t *saveBtn = lv_btn_create(displayObj[objname], nullptr);
    lv_obj_set_pos(saveBtn, x, y);
    lv_obj_set_size(saveBtn, width, high);
    lv_obj_t *saveLab = lv_label_create(saveBtn, nullptr);
    lv_label_set_text(saveLab, "save");
    lv_obj_set_event_cb(saveBtn, saveAction); //设置动作的通用函数
    lv_obj_set_user_data(saveBtn, &_tempData);
}

void UserDisplay::createResetBtn(obj_flag objname, const int x, const int y, const int width, const int high)
{
    //退出重制传感器按钮
    lv_obj_t *resetBtn = lv_btn_create(displayObj[objname], nullptr);
    lv_obj_set_pos(resetBtn, x, y);
    lv_obj_set_size(resetBtn, width, high);
    lv_obj_t *resetLab = lv_label_create(resetBtn, nullptr);
    lv_label_set_text(resetLab, "reset");
    lv_obj_set_event_cb(resetBtn, resetAction); //设置动作的通用函数
}
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
                sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE] = false; //红方0
                sysData->jsonVal[I18N_AUTO][I18N_AUTO "&" I18N_SKILL_AUTO] = false;            //红方0
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_RED;
                userDisplay->mainStyle.body.main_color = LV_COLOR_RED;
                break;
            case 1:
                sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE] = true; //红方0
                sysData->jsonVal[I18N_AUTO][I18N_AUTO "&" I18N_SKILL_AUTO] = false;           //蓝方
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_BLUE;
                userDisplay->mainStyle.body.main_color = LV_COLOR_BLUE;
                break;
            case 2:
                sysData->jsonVal[I18N_AUTO][I18N_AUTO "&" I18N_SKILL_AUTO] = true; //红方0
                userDisplay->theme->style.tabview.bg->body.main_color = LV_COLOR_BLACK;
                userDisplay->mainStyle.body.main_color = LV_COLOR_BLACK;
                break;
            default:
                logger->error({I18N_COMPETITION_TAB_CHOSE_ERROR});
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
        json *tempData = static_cast<json *>(lv_obj_get_user_data(sw));
        *tempData = lv_sw_get_state(sw);
    }
}
/**
 * 自动赛选择时候的确认按钮的动作
 * @param  btn 要实现动作的按钮的指针
 * @return     返回不知道啥....
 */

void UserDisplay::compConfirmAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn;
    if (event == LV_EVENT_PRESSED)
    {
        sysData->saveData();
        //获取开关状态
        std::string str;
        for (auto &it : sysData->jsonVal[I18N_AUTO].items())
        {
            std::string tempStr = it.key();
            auto pos = tempStr.find("&"); //查找间隔符号
            if (pos != std::string::npos)
            {
                if (it.value())
                    tempStr.erase(0, pos + 1);
                else
                    tempStr.erase(pos, tempStr.length());
                str += (tempStr + "\n");
            }
            else
                logger->error({I18N_COMPETITION_CONFIRM_ERROR});
        }
        // 创建确认页面
        lv_obj_t *confirm = lv_obj_create(userDisplay->displayObj[OBJ_COMPETITION], nullptr);
        lv_obj_set_size(confirm, lv_obj_get_width(userDisplay->displayObj[OBJ_COMPETITION]), lv_obj_get_height(userDisplay->displayObj[OBJ_COMPETITION]));
        lv_obj_set_style(confirm, &userDisplay->mainStyle);
        userDisplay->createStartObj(confirm);
        //显示自动赛选项
        lv_obj_t *autoinfoLab = lv_label_create(userDisplay->displayObj[BTNM_START], nullptr); //创建LAB条
        userDisplay->ostr.clear();                                                             //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
        userDisplay->ostr.str("");                                                             //2：调用str("")将缓冲区清零，清除脏数据
        userDisplay->ostr << str << std::endl;
        lv_label_set_text(autoinfoLab, userDisplay->ostr.str().c_str());
        lv_obj_align(autoinfoLab, userDisplay->displayObj[BTNM_START], LV_ALIGN_IN_TOP_MID, 0, 0);
    }
}
void UserDisplay::mBoxAction(lv_obj_t *mbox, lv_event_t event)
{
    if (event == LV_EVENT_PRESSED)
    {
        std::string btn = lv_mbox_get_active_btn_text(mbox);
        if (btn == I18N_RED_ALLIANCE)
        {
            sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE] = false;
            lv_mbox_set_text(mbox, btn.c_str());
        }
        else
        {
            sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE] = true;
            lv_mbox_set_text(mbox, btn.c_str());
        }
    }
}

void UserDisplay::confirmBtnInOdom(lv_obj_t *btn, lv_event_t event)
{
    (void)btn;
    if (event == LV_EVENT_PRESSED)
    {
        sysData->saveData();
        lv_obj_del(userDisplay->displayObj[OBJ_COMPETITION]);
        userDisplay->displayObj[OBJ_COMPETITION] = nullptr;
    }
}

void UserDisplay::closeAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn; /*Unused*/
    if (event == LV_EVENT_PRESSED)
    {
        if (userDisplay->displayObj[OBJ_BTNM_SON] != nullptr)
        {
            // if (!sysData->jsonVal[I18N_AUTO][I18N_RED_ALLIANCE "&" I18N_BLUD_ALLIANCE]) //设置默认颜色
            //     userDisplay->displayObj[OBJ_BTNM_SON]->style_p->body.main_color = (lv_color_t)LV_COLOR_RED;
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
}
void UserDisplay::resetAction(lv_obj_t *btn, lv_event_t event)
{
    (void)btn; /*Unused*/
    if (event == LV_EVENT_PRESSED)
    {
        for (auto &it : sysData->obj)
            it->resetAllSensors();
    }
}
void UserDisplay::saveAction(lv_obj_t *btn, lv_event_t event)
{
    if (event == LV_EVENT_PRESSED)
    {
        // chassis->isStopPid(true); //不要停止PID
        json *tempData = static_cast<json *>(lv_obj_get_user_data(btn));
        sysData->jsonVal = *tempData;
        sysData->saveData();
    }
}

/**
 * 按钮阵列的动作
 * @param  btnm 按钮阵列
 * @param  txt  按钮的名字
 * @return      系统值
 */
void UserDisplay::startBtnmAction(lv_obj_t *btnm, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        std::string btn = lv_btnm_get_active_btn_text(btnm);
        if (btn == I18N_SYSTEM_INFO)
            ;
        else if (btn == I18N_BTNM_GOBAL_CONFIG_SET)
            ;
        else if (btn == I18N_BTNM_MAINTENANCE_INFO)
            ;
        else if (btn == I18N_BTNM_VISION_SET)
            ;
        else if (btn == I18N_BTNM_VERSION)
            ;
        else if (btn == I18N_BTNM_CUSTOM_TEST)
            ;
        else if (btn == I18N_BTNM_PID_SET)
            ;
        else if (btn == I18N_BTNM_ODOM_SET)
            ;
        else
            ;
        logger->info({"chose ", btn});
    }
}
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

void UserDisplay::loopTask(_lv_task_t *param)
{
    (void)param;               /*Unused*/
    userDisplay->ostr.clear(); //1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit);
    userDisplay->ostr.str(""); //2：调用str("")将缓冲区清零，清除脏数据
    userDisplay->ostr << "loop:" << userDisplay->loopTime << "max:" << userDisplay->maxLoopTime << "min:" << userDisplay->minLoopTime << std::endl;
    lv_label_set_text(userDisplay->loopLab, userDisplay->ostr.str().c_str());
}
} // namespace ncrapi