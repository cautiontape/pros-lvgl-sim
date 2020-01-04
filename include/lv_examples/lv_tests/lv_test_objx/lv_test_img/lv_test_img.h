/**
 * @file lv_test_img.h
 *
 */

#ifndef LV_TEST_IMG_H
#define LV_TEST_IMG_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_ex_conf.h"
#include "lvgl.h"

#else
#include "../../../../lv_ex_conf.h"
#include "../../../../lvgl/lvgl.h"

#endif

#if LV_USE_IMG && LV_USE_TESTS

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

LV_IMG_DECLARE(logo)
LV_IMG_DECLARE(field)

/**
 * Create images to test their functionalities
 */
void lv_test_img_1(void);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_IMG*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_USE_IMG && LV_USE_TESTS*/
