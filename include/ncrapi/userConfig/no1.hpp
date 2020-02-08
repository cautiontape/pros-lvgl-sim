#pragma once
#include "ncrapi/system/json.hpp"
const json userData = {
    {"json版本号", 1.3},
    {
        "系统信息",
        {
            {"机器人类型", "初号机"},
            {"队伍编号", "8982D"},
            {"用户", "bobo"},
            {"机器人长度", 456},
            {"机器人宽度", 456},
            {"赛场边长", 3445},
            {"轮间距", 315.0},
            {"车轮直径", 104},
            {"机器重量", 8.132},
        },
    },
    {
        "自动赛",
        {
            {"自动赛&纯自动", false},
            {"红方&蓝方", true},
            {"长边&短边", false},
            {"放&不放", false},
            {"视觉启用&不启用", false},

        },
    },
    {
        "视觉信息",
        {
            {"视觉传感器前", 17},
            {"曝光度", 20},
            {"最大识别高", 75},
            {"最大识别宽", 65},
            {"数据", 0},
            {"颜色范围", {
                             {"红色", {8.8, 10.0, 11.0, 10.0, 10.0, 6.9}},
                             {"蓝色", {9.5, 11.0, 11.0, 7.0, 7.1, 11.0}},
                             {"绿色", {11.0, 9.0, 8.0, 8.3, 10.0, 5.0}},
                             {"橙色", {9.5, 11.0, 11.0, 7.0, 7.1, 11.0}},
                             {"紫色", {8.8, 10.0, 11.0, 10.0, 10.0, 6.9}},
                         }},
        },
    },
    {
        "底盘",
        {
            {"马达", {
                         {"左前", {{"端口", 1}, {"正反", false}, {"齿轮", 1}}},
                         {"左后", {{"端口", 2}, {"正反", false}, {"齿轮", 1}}},
                         {"右前", {{"端口", 3}, {"正反", true}, {"齿轮", 1}}},
                         {"右后", {{"端口", 4}, {"正反", true}, {"齿轮", 1}}},
                         {"中间", {{"端口", 5}, {"正反", false}, {"齿轮", 0}}},
                     }},
            {"ADI", {
                        {"陀螺仪L", 1},
                        {"陀螺仪R", 2},
                    }},
            {"参数", {
                         {"陀螺仪比例", 0.936},
                         {"陀螺仪平衡", 0.01}, //如果左边360 右边350 正数 如果左边360 右边370 负数
                         {"左右矫正比例", 1.052},
                         {"遥控器矫正", 10},
                         {"最大旋转速度", 127},
                         {"模式", 0},
                     }},
            {"PID参数", {
                            {"模式0", {
                                          {"速度pid", {{"KP", 0.5}, {"KI", 0.001}, {"KD", 2.0}, {"KBIAS", 0}, {"LIMIT", 200}, {"Q", 0.01}, {"R", 0.02}}},
                                          {"前后pid", {{"KP", 0.5}, {"KI", 0.001}, {"KD", 2.0}, {"KBIAS", 0}, {"LIMIT", 200}, {"Q", 0.01}, {"R", 0.02}}},
                                          {"左右pid", {{"KP", 2.0}, {"KI", 0.01}, {"KD", 8.5}, {"KBIAS", 0}, {"LIMIT", 10}, {"Q", 0.01}, {"R", 0.02}}},
                                          {"自瞄pid", {{"KP", 0.55}, {"KI", 0.001}, {"KD", 0.5}, {"KBIAS", 0}, {"LIMIT", 40}, {"Q", 0.01}, {"R", 0.02}}},

                                      }},
                            {"模式1", {
                                          {"前后pid", {{"KP", 0.3}, {"KI", 0.005}, {"KD", 0.0}, {"KBIAS", 0}, {"LIMIT", 500}, {"Q", 0.01}, {"R", 0.02}}},
                                          {"左右pid", {{"KP", 0.79}, {"KI", 0.003}, {"KD", 0.0}, {"KBIAS", 0}, {"LIMIT", 10}, {"Q", 0.01}, {"R", 0.02}}},
                                          {"自瞄pid", {{"KP", 0.4}, {"KI", 0.001}, {"KD", 0.001}, {"KBIAS", 0}, {"LIMIT", 40}, {"Q", 0.01}, {"R", 0.02}}},
                                      }},
                        }},
        },
    },
    {
        "千斤顶",
        {
            {"马达", {
                         {"千斤顶", {{"端口", 6}, {"正反", false}, {"齿轮", 0}}},
                     }},
            {"ADI", {
                        {"千斤顶碰撞", 3},
                    }},
            {"参数", {
                         {"悬停值", 5},
                         {"行程", 800},
                         {"最小速度", 10},
                     }},
        },
    },
    {
        "吸吐",
        {
            {"马达", {
                         {"吸吐L", {{"端口", 9}, {"正反", false}, {"齿轮", 0}}},
                         {"吸吐R", {{"端口", 10}, {"正反", true}, {"齿轮", 0}}},
                     }},
            {"ADI", {
                        {"巡线", 4},
                    }},
            {"参数", {
                         {"检测值", 2600},
                         {"马达慢吐值", 40},
                         {"悬停值", 5},
                     }},
        },
    },

};
/**
 * @brief 前后速度矩阵数组
 * 
 */
const int frSpeed[128] = {
    0, 7, 14, 21, 22, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28,
    28, 29, 29, 29, 30, 30, 30, 30, 31, 31, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    121, 122, 123, 124, 125, 126, 127, 127};
/**
     * @brief 左右速度矩阵数组
     * 
     */
const int rotateSpeed[128] = {
    0, 13, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 30, 30, 30, 30, 31, 31,
    31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100,
    101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120,
    121, 122, 123, 124, 125, 126, 127, 127};