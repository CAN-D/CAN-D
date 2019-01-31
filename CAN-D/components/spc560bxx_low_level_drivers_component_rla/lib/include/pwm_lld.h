/*
    SPC5 RLA - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    pwm_lld.h
 * @brief   SPC5xx PWM low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#ifndef _PWM_LLD_H_
#define _PWM_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_PWM == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    PWM output mode macros
 * @{
 */

/**
 * @name    PWM output mode macros
 * @{
 */
/**
 * @brief   Standard output modes mask.
 */
#define PWM_OUTPUT_MASK                         0x0F

/**
 * @brief   Output not driven, callback only.
 */
#define PWM_OUTPUT_DISABLED                     0x00

/**
 * @brief   Positive PWM logic, active is logic level one.
 */
#define PWM_OUTPUT_ACTIVE_HIGH                  0x01

/**
 * @brief   Inverse PWM logic, active is logic level zero.
 */
#define PWM_OUTPUT_ACTIVE_LOW                   0x02
/** @} */

/**
 * @brief   Number of PWM channels per PWM driver 
 *          when Counter Bus A is selected.
 */
#define PWM_COUNT_BUS_A_CH_NUM                  31U

/**
 * @brief   Number of PWM channels per PWM driver 
 *          when Counter Bus B_C_D_E is selected.
 */
#define PWM_COUNT_BUS_BCDE_CH_NUM               7U

/**
 * @brief   Edge-Aligned PWM functional mode.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_ALIGN_EDGE                          0x00U

/**
 * @brief   Center-Aligned PWM functional mode.
 * @note    This is an SPC5-specific setting.
 */
#define PWM_ALIGN_CENTER                        0x01U

/**
 * @brief   PWM Counter Bus modes.
 */
#define EMIOS_PWM_DISABLED                      0x00U
#define EMIOS_PWM_COUNTER_BUS_A                 0x01U
#define EMIOS_PWM_COUNTER_BUS_B_C_D_E           0x02U

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   EMIOS0 PWM counter bus switch.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS       EMIOS_PWM_DISABLED
#endif

/**
 * @brief   EMIOS0 PWM CH0 enable switch.
 * @details If set to @p TRUE the support for PWM CHO is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH0) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH0             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH2 enable switch.
 * @details If set to @p TRUE the support for PWM CH2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH2) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH2             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH3 enable switch.
 * @details If set to @p TRUE the support for PWM CH3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH3) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH3             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH4 enable switch.
 * @details If set to @p TRUE the support for PWM CH4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH4) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH4             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH5 enable switch.
 * @details If set to @p TRUE the support for PWM CH5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH5) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH5             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH6 enable switch.
 * @details If set to @p TRUE the support for PWM CH6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH6) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH6             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH7 enable switch.
 * @details If set to @p TRUE the support for PWM CH7 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH7) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH7             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH8 enable switch.
 * @details If set to @p TRUE the support for PWM CH8 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH8) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH8             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH9 enable switch.
 * @details If set to @p TRUE the support for PWM CH9 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH9) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH9             FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH10 enable switch.
 * @details If set to @p TRUE the support for PWM CH10 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH10) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH10            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH11 enable switch.
 * @details If set to @p TRUE the support for PWM CH11 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH11) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH11            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH12 enable switch.
 * @details If set to @p TRUE the support for PWM CH12 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH12) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH12            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH13 enable switch.
 * @details If set to @p TRUE the support for PWM CH13 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH13) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH13            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH14 enable switch.
 * @details If set to @p TRUE the support for PWM CH14 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH14) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH14            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH15 enable switch.
 * @details If set to @p TRUE the support for PWM CH15 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH15) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH15            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH16 enable switch.
 * @details If set to @p TRUE the support for PWM CH16 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH16) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH16            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH17 enable switch.
 * @details If set to @p TRUE the support for PWM CH17 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH17) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH17            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH18 enable switch.
 * @details If set to @p TRUE the support for PWM CH18 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH18) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH18            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH19 enable switch.
 * @details If set to @p TRUE the support for PWM CH19 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH19) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH19            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH20 enable switch.
 * @details If set to @p TRUE the support for PWM CH20 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH20) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH20            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH21 enable switch.
 * @details If set to @p TRUE the support for PWM CH21 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH21) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH21            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH22 enable switch.
 * @details If set to @p TRUE the support for PWM CH22 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH22) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH22            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH23 enable switch.
 * @details If set to @p TRUE the support for PWM CH23 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH23) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH23            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH24 enable switch.
 * @details If set to @p TRUE the support for PWM CH24 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH24) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH24            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH25 enable switch.
 * @details If set to @p TRUE the support for PWM CH25 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH25) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH25            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH26 enable switch.
 * @details If set to @p TRUE the support for PWM CH26 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH26) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH26            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH27 enable switch.
 * @details If set to @p TRUE the support for PWM CH27 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH27) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH27            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH28 enable switch.
 * @details If set to @p TRUE the support for PWM CH28 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH28) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH28            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH29 enable switch.
 * @details If set to @p TRUE the support for PWM CH29 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH29) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH29            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH30 enable switch.
 * @details If set to @p TRUE the support for PWM CH30 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH30) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH30            FALSE
#endif

/**
 * @brief   EMIOS0 PWM CH31 enable switch.
 * @details If set to @p TRUE the support for PWM CH31 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_CH31) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_CH31            FALSE
#endif

/**
 * @brief   EMIOS0 CH0-CH1 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F0F1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F0F1_PRIORITY       7
#endif

/**
 * @brief   EMIOS0 CH2-CH3 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F2F3_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F2F3_PRIORITY       7
#endif

/**
 * @brief   EMIOS0 CH4-CH5 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F4F5_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F4F5_PRIORITY       7
#endif

/**
 * @brief   EMIOS0 CH6-CH7 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F6F7_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F6F7_PRIORITY       7
#endif

/**
 * @brief   EMIOS0 CH8-CH9 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F8F9_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F8F9_PRIORITY       7
#endif

/**
 * @brief   EMIOS0 CH10-CH11 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F10F11_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F10F11_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH12-CH13 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F12F13_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F12F13_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH14-CH15 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F14F15_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F14F15_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH16-CH17 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F16F17_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F16F17_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH18-CH19 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F18F19_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F18F19_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH20-CH21 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F20F21_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F20F21_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH22-CH23 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F22F23_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F22F23_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH24-CH25 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F24F25_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F24F25_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH26-CH27 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F26F27_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F26F27_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH28-CH29 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F28F29_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F28F29_PRIORITY     7
#endif

/**
 * @brief   EMIOS0 CH30-CH31 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F30F31_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F30F31_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 PWM counter bus switch.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS       EMIOS_PWM_DISABLED
#endif

/**
 * @brief   EMIOS1 PWM CH0 enable switch.
 * @details If set to @p TRUE the support for PWM CHO is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH0) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH0             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH2 enable switch.
 * @details If set to @p TRUE the support for PWM CH2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH2) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH2             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH3 enable switch.
 * @details If set to @p TRUE the support for PWM CH3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH3) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH3             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH4 enable switch.
 * @details If set to @p TRUE the support for PWM CH4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH4) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH4             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH5 enable switch.
 * @details If set to @p TRUE the support for PWM CH5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH5) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH5             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH6 enable switch.
 * @details If set to @p TRUE the support for PWM CH6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH6) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH6             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH7 enable switch.
 * @details If set to @p TRUE the support for PWM CH7 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH7) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH7             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH8 enable switch.
 * @details If set to @p TRUE the support for PWM CH8 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH8) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH8             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH9 enable switch.
 * @details If set to @p TRUE the support for PWM CH9 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH9) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH9             FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH10 enable switch.
 * @details If set to @p TRUE the support for PWM CH10 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH10) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH10            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH11 enable switch.
 * @details If set to @p TRUE the support for PWM CH11 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH11) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH11            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH12 enable switch.
 * @details If set to @p TRUE the support for PWM CH12 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH12) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH12            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH13 enable switch.
 * @details If set to @p TRUE the support for PWM CH13 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH13) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH13            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH14 enable switch.
 * @details If set to @p TRUE the support for PWM CH14 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH14) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH14            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH15 enable switch.
 * @details If set to @p TRUE the support for PWM CH15 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH15) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH15            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH16 enable switch.
 * @details If set to @p TRUE the support for PWM CH16 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH16) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH16            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH17 enable switch.
 * @details If set to @p TRUE the support for PWM CH17 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH17) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH17            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH18 enable switch.
 * @details If set to @p TRUE the support for PWM CH18 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH18) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH18            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH19 enable switch.
 * @details If set to @p TRUE the support for PWM CH19 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH19) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH19            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH20 enable switch.
 * @details If set to @p TRUE the support for PWM CH20 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH20) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH20            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH21 enable switch.
 * @details If set to @p TRUE the support for PWM CH21 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH21) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH21            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH22 enable switch.
 * @details If set to @p TRUE the support for PWM CH22 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH22) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH22            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH23 enable switch.
 * @details If set to @p TRUE the support for PWM CH23 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH23) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH23            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH24 enable switch.
 * @details If set to @p TRUE the support for PWM CH24 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH24) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH24            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH25 enable switch.
 * @details If set to @p TRUE the support for PWM CH25 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH25) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH25            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH26 enable switch.
 * @details If set to @p TRUE the support for PWM CH26 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH26) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH26            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH27 enable switch.
 * @details If set to @p TRUE the support for PWM CH27 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH27) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH27            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH28 enable switch.
 * @details If set to @p TRUE the support for PWM CH28 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH28) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH28            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH29 enable switch.
 * @details If set to @p TRUE the support for PWM CH29 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH29) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH29            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH30 enable switch.
 * @details If set to @p TRUE the support for PWM CH30 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH30) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH30            FALSE
#endif

/**
 * @brief   EMIOS1 PWM CH31 enable switch.
 * @details If set to @p TRUE the support for PWM CH31 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_CH31) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_CH31            FALSE
#endif

/**
 * @brief   EMIOS1 CH0-CH1 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F0F1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F0F1_PRIORITY       7
#endif

/**
 * @brief   EMIOS1 CH2-CH3 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F2F3_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F2F3_PRIORITY       7
#endif

/**
 * @brief   EMIOS1 CH4-CH5 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F4F5_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F4F5_PRIORITY       7
#endif

/**
 * @brief   EMIOS1 CH6-CH7 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F6F7_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F6F7_PRIORITY       7
#endif

/**
 * @brief   EMIOS1 CH8-CH9 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F8F9_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F8F9_PRIORITY       7
#endif

/**
 * @brief   EMIOS1 CH10-CH11 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F10F11_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F10F11_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH12-CH13 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F12F13_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F12F13_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH14-CH15 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F14F15_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F14F15_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH16-CH17 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F16F17_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F16F17_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH18-CH19 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F18F19_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F18F19_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH20-CH21 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F20F21_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F20F21_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH22-CH23 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F22F23_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F22F23_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH24-CH25 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F24F25_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F24F25_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH26-CH27 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F26F27_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F26F27_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH28-CH29 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F28F29_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F28F29_PRIORITY     7
#endif

/**
 * @brief   EMIOS1 CH30-CH31 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F30F31_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F30F31_PRIORITY     7
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS == EMIOS_PWM_DISABLED)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_A     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_B     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_C     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_D     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_E     FALSE
#elif (SPC5_PWM_USE_EMIOS0_COUNT_BUS == EMIOS_PWM_COUNTER_BUS_A)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_A     TRUE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_B     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_C     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_D     FALSE
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_E     FALSE
#else
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_A     FALSE
#if (SPC5_PWM_USE_EMIOS0_CH1 == TRUE)  || (SPC5_PWM_USE_EMIOS0_CH2 == TRUE)  || \
    (SPC5_PWM_USE_EMIOS0_CH3 == TRUE)  || (SPC5_PWM_USE_EMIOS0_CH4 == TRUE)  || \
	(SPC5_PWM_USE_EMIOS0_CH5 == TRUE)  || (SPC5_PWM_USE_EMIOS0_CH6 == TRUE)  || \
	(SPC5_PWM_USE_EMIOS0_CH7 == TRUE)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_B     TRUE
#else
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_B     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS0_CH9 == TRUE)  || (SPC5_PWM_USE_EMIOS0_CH10 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH11 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH12 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH13 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH14 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH15 == TRUE)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_C     TRUE
#else
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_C     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS0_CH17 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH18 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH19 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH20 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH21 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH22 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH23 == TRUE)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_D     TRUE
#else
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_D     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS0_CH25 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH26 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH27 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH28 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH29 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH30 == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_CH31 == TRUE)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_E     TRUE
#else
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_E     FALSE
#endif
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS == EMIOS_PWM_DISABLED)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_A     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_B     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_C     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_D     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_E     FALSE
#elif (SPC5_PWM_USE_EMIOS1_COUNT_BUS == EMIOS_PWM_COUNTER_BUS_A)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_A     TRUE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_B     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_C     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_D     FALSE
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_E     FALSE
#else
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_A     FALSE
#if (SPC5_PWM_USE_EMIOS1_CH1 == TRUE)  || (SPC5_PWM_USE_EMIOS1_CH2 == TRUE)  || \
    (SPC5_PWM_USE_EMIOS1_CH3 == TRUE)  || (SPC5_PWM_USE_EMIOS1_CH4 == TRUE)  || \
	(SPC5_PWM_USE_EMIOS1_CH5 == TRUE)  || (SPC5_PWM_USE_EMIOS1_CH6 == TRUE)  || \
	(SPC5_PWM_USE_EMIOS1_CH7 == TRUE)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_B     TRUE
#else
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_B     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS1_CH9 == TRUE)  || (SPC5_PWM_USE_EMIOS1_CH10 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH11 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH12 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH13 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH14 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH15 == TRUE)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_C     TRUE
#else
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_C     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS1_CH17 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH18 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH19 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH20 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH21 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH22 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH23 == TRUE)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_D     TRUE
#else
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_D     FALSE
#endif
#if (SPC5_PWM_USE_EMIOS1_CH25 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH26 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH27 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH28 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH29 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH30 == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_CH31 == TRUE)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_E     TRUE
#else
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_E     FALSE
#endif
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE) || \
	(SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
#define SPC5_PWM_USE_EMIOS0                 TRUE
#else
#define SPC5_PWM_USE_EMIOS0                 FALSE
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE) || \
	(SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
#define SPC5_PWM_USE_EMIOS1                 TRUE
#else
#define SPC5_PWM_USE_EMIOS1                 FALSE
#endif

#if (SPC5_HAS_EMIOS0 == FALSE) && (SPC5_PWM_USE_EMIOS0 == TRUE)
#error "EMIOS0 not present in the selected device"
#endif

#if (SPC5_HAS_EMIOS1 == FALSE) && (SPC5_PWM_USE_EMIOS1 == TRUE)
#error "EMIOS1 not present in the selected device"
#endif

#if (SPC5_PWM_USE_EMIOS0 == FALSE) && (SPC5_PWM_USE_EMIOS1 == FALSE)
#error "PWM driver activated but no Channels assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing a PWM driver.
 */
typedef struct PWMDriver PWMDriver;

/**
 * @brief   PWM notification callback type.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 */
typedef void (*pwmcallback_t)(PWMDriver *pwmp);

/**
 * @brief   PWM mode type.
 */
typedef uint32_t pwmmode_t;

/**
 * @brief   PWM channel type.
 */
typedef uint8_t pwmchannel_t;

/**
 * @brief   PWM counter type.
 */
typedef uint32_t pwmcnt_t;

/**
 * @brief   PWM driver channel configuration structure.
 * @note    Some architectures may not be able to support the channel mode
 *          or the callback, in this case the fields are ignored.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  pwmmode_t                 mode;
  /**
   * @brief Channel callback pointer.
   * @note  This callback is invoked on the channel compare event. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /* End of the mandatory fields.*/
} PWMChannelConfig;

/**
 * @brief   Driver configuration structure.
 * @note    Implementations may extend this structure to contain more,
 *          architecture dependent, fields.
 */
typedef struct {
  /**
   * @brief Counter prescaler.
   */
  uint8_t                   psc;
  /**
   * @brief PWM period in ticks.
   */
  pwmcnt_t                  period;
  /**
   * @brief Periodic callback pointer.
   * @note  This callback is invoked on PWM counter reset. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /**
   * @brief Channels configurations.
   */
  PWMChannelConfig          channels[PWM_COUNT_BUS_A_CH_NUM];
  /* End of the mandatory fields.*/
  /**
   * @brief PWM functional mode.
   */
  pwmmode_t                 mode;
} PWMConfig;

/**
 * @brief   Structure representing an PWM driver.
 * @note    Implementations may extend this structure to contain more,
 *          architecture dependent, fields.
 */
struct PWMDriver {
  /**
   * @brief Current configuration data.
   */
  const PWMConfig           *config;
  /**
   * @brief Current PWM period in ticks.
   */
  pwmcnt_t                  period;
#if defined(PWM_DRIVER_EXT_FIELDS)
  PWM_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the eMIOSx registers block.
   */
  volatile struct EMIOS_tag *emiosp;
  /**
   * @brief eMIOS channel used as period for the channels
   *        group related to the driver.
   */
  pwmchannel_t              period_ch;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @name    PWM duty cycle conversion
 * @{
 */
/**
 * @brief   Converts from period fraction to counter ticks.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] denominator denominator of the fraction
 * @param[in] numerator numerator of the fraction
 * @return              The counter ticks as fraction of the period.
 *
 * @api
 */
#define PWM_PERIOD_FRACTION(pwmp, denominator, numerator)                   \
  ((pwmcnt_t)((((pwmcnt_t)(pwmp)->period) *                                 \
               (pwmcnt_t)(numerator)) / (pwmcnt_t)(denominator)))

/**
 * @brief   Converts from degrees to pulse width.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] degrees   degrees as an integer between 0 and 36000
 * @return              The pulse width to be passed to @p pwm_lld_enable_channel().
 *
 * @api
 */
#define PWM_DEGREES_TO_WIDTH(pwmp, degrees)                                 \
  PWM_PERIOD_FRACTION(pwmp, 36000, degrees)

/**
 * @brief   Converts from percentage to pulse width.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] percentage percentage as an integer between 0 and 10000
 * @return              The pulse width to be passed to @p pwm_lld_enable_channel().
 *
 * @api
 */
#define PWM_PERCENTAGE_TO_WIDTH(pwmp, percentage)                           \
  PWM_PERIOD_FRACTION(pwmp, 10000, percentage)

/**
 * @brief   Converts from percentage to dead time.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] percentage percentage as an integer between 0 and 10000
 * @return              The dead time to be passed to @p pwm_lld_enable_channel().
 *
 * @api
 */
#define PWM_PERCENTAGE_TO_DEADTIME(pwmp, percentage)                        \
  PWM_PERIOD_FRACTION(pwmp, 10000, percentage)
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)) && !defined(__DOXYGEN__)
extern PWMDriver PWMD1;
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD2;
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD3;
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD4;
#endif

#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)) && !defined(__DOXYGEN__)
extern PWMDriver PWMD5;
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD6;
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD7;
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD8;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void pwm_lld_init(void);
  void pwm_lld_start(PWMDriver *pwmp, const PWMConfig *config);
  void pwm_lld_stop(PWMDriver *pwmp);
  void pwm_lld_change_period(PWMDriver *pwmp, pwmcnt_t period);
  void pwm_lld_enable_channel(PWMDriver *pwmp,
                              pwmchannel_t pwm_ch,
                              pwmcnt_t width,
                              pwmcnt_t deadtime);
  void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t pwm_ch);
  void pwm_lld_serve_period_interrupt(PWMDriver *pwmp, pwmchannel_t emios_ch);
  void pwm_lld_serve_channel_interrupt(PWMDriver *pwmp, pwmchannel_t emios_ch);
#ifdef __cplusplus
}
#endif

#endif /* LLD_USE_PWM */

#endif /* _PWM_LLD_H_ */

/** @} */
