#include "ncrapi/userDisplay/userDisplay.hpp"
#include "ncrapi/system/logger.hpp"
#include "sim_test/test_config.hpp"

namespace ncrapi {
void btn_event_cb(lv_obj_t *btn, lv_event_t event)
{
    switch (event)
    {
        case LV_EVENT_PRESSED:
            printf("Pressed\n");
            break;

        case LV_EVENT_SHORT_CLICKED:
            printf("Short clicked\n");
            break;

        case LV_EVENT_CLICKED:
            printf("Clicked\n");
            break;

        case LV_EVENT_LONG_PRESSED:
            printf("Long press\n");
            break;

        case LV_EVENT_LONG_PRESSED_REPEAT:
            printf("Long press repeat\n");
            break;

        case LV_EVENT_RELEASED:
            printf("Released\n");
            break;
    }
}
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
    logger->info({"图像类构造成功"});
}
void UserDisplay::createTerminal(lv_obj_t *parent)
{
    std::vector<std::string> Level = {"错误", "警告"};
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
    // if (displayObj[objname] == nullptr)
    // {
    //     if (parent == nullptr)
    //     {
    //         displayObj[objname] = lv_obj_create(lv_scr_act(), nullptr);
    //         lv_obj_set_size(displayObj[objname], LV_HOR_RES, LV_VER_RES - 30); //设置页面大小
    //         lv_obj_set_y(displayObj[objname], 30);                             //设置位置
    //         lv_obj_set_parent(terminal, lv_obj_get_parent(terminal));
    //     }
    //     else
    //     {
    //         displayObj[objname] = lv_obj_create(parent, nullptr);
    //         lv_obj_set_size(displayObj[objname], lv_obj_get_width(parent), lv_obj_get_height(parent));
    //         createExitBtn(objname); //退出按钮
    //     }

    //     lv_obj_set_style(displayObj[objname], &mainStyle); //设置样式
    //     logger->info({"图像类:", terminalText, " 构造成功"});
    // }
    // else
    //     logger->debug({"图像类:", terminalText, " 已经存在"});

    // if (labText != nullptr)
    // {
    //     lv_obj_t *lab = lv_label_create(displayObj[objname], nullptr);
    //     lv_label_set_text(lab, labText);
    // }
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
        logger->info({"图像类线程:", terminalText, " 构造成功"});
    }
    else
        logger->warnning({"图像类线程:", terminalText, " 已经存在"});
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
            std::cout << "删除图像类线程:" << flag << " 个" << std::endl;
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
            logger->info({"删除图像类:", std::to_string(flag), " 个"});
            flag++;
        }
    }
}

// void UserDisplay::createMbox(obj_flag objname, const char *txt1, const char *txt2, const char *txt3, lv_btnm_action_t action) //创建一个消息框
// {
//     lv_obj_t *mbox = lv_mbox_create(displayObj[objname], nullptr);
//     lv_mbox_set_text(mbox, txt1);
//     static const char *btns[] = {txt2, txt3, ""}; /*Button description. '\221' lv_btnm like control char*/
//     lv_mbox_add_btns(mbox, btns, nullptr);
//     lv_obj_set_width(mbox, 250);
//     lv_obj_align(mbox, displayObj[objname], LV_ALIGN_IN_LEFT_MID, 0, 20); /*Align to the corner*/
//     lv_mbox_set_action(mbox, action);
// }

// void UserDisplay::createExitBtn(obj_flag objname, const int x, const int y, const int width, const int high) //创建退出按钮
// {
//     lv_obj_t *exitBtn = lv_btn_create(displayObj[objname], nullptr);
//     lv_obj_set_pos(exitBtn, x, y);
//     lv_obj_set_size(exitBtn, width, high);
//     lv_obj_t *exitLab = lv_label_create(exitBtn, nullptr);
//     lv_label_set_text(exitLab, "exit");
//     lv_btn_set_action(exitBtn, LV_BTN_ACTION_CLICK, closeAction);
// }
// void UserDisplay::createSaveBtn(obj_flag objname, const int x, const int y, const int width, const int high) //创建退出按钮
// {
//     lv_obj_t *saveBtn = lv_btn_create(displayObj[objname], nullptr);
//     lv_obj_set_pos(saveBtn, x, y);
//     lv_obj_set_size(saveBtn, width, high);
//     lv_obj_t *saveLab = lv_label_create(saveBtn, nullptr);
//     lv_label_set_text(saveLab, "save");
//     lv_btn_set_action(saveBtn, LV_BTN_ACTION_CLICK, saveAction);
//     lv_obj_set_free_ptr(saveBtn, &_tempData);
// }

// void UserDisplay::createResetBtn(obj_flag objname, const int x, const int y, const int width, const int high)
// {
//     //退出重制传感器按钮
//     lv_obj_t *resetBtn = lv_btn_create(displayObj[objname], nullptr);
//     lv_obj_set_pos(resetBtn, x, y);
//     lv_obj_set_size(resetBtn, width, high);
//     lv_obj_t *resetLab = lv_label_create(resetBtn, nullptr);
//     lv_label_set_text(resetLab, "reset");
//     lv_btn_set_action(resetBtn, LV_BTN_ACTION_CLICK, resetAction);
// }
} // namespace ncrapi