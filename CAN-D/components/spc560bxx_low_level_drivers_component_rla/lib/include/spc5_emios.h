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
 * @file    spc5_emios.h
 * @brief   SPC5xx ICU-PWM low level drivers common header.
 *
 * @addtogroup SPC5xx_eMIOS
 * @{
 */

#ifndef _SPC5_EMIOS_H_
#define _SPC5_EMIOS_H_

#include "pwm_lld.h"
#include "icu_lld.h"

#if (LLD_USE_ICU == TRUE) || (LLD_USE_PWM == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define EMIOSMCR_MDIS                       (1UL << 30U)
#define EMIOSMCR_FRZ                        (1UL << 29U)
#define EMIOSMCR_GTBE                       (1UL << 28U)
#define EMIOSMCR_GPREN                      (1UL << 26U)
#define EMIOSMCR_GPRE(n)                    ((uint32_t)(n) << 8U)

#define EMIOSC_FREN                         (1UL << 31U)
#define EMIOSC_UCPRE(n)                     ((uint32_t)(n) << 26U)
#define EMIOSC_UCPREN                       (1UL << 25U)
#define EMIOSC_DMA                          (1UL << 24U)
#define EMIOSC_IF(n)                        ((uint32_t)(n) << 19U)
#define EMIOSC_FCK                          (1UL << 18U)
#define EMIOSC_FEN                          (1UL << 17U)
#define EMIOSC_FORCMA                       (1UL << 13U)
#define EMIOSC_FORCMB                       (1UL << 12U)
#define EMIOSC_BSL(n)                       ((uint32_t)(n) << 9U)
#define EMIOSC_EDSEL                        (1UL << 8U)
#define EMIOSC_EDPOL                        (1UL << 7U)
#define EMIOSC_MODE(n)                      ((uint32_t)(n) << 0)

#define EMIOS_BSL_COUNTER_BUS_A             0UL
#define EMIOS_BSL_COUNTER_BUS_2             1UL
#define EMIOS_BSL_INTERNAL_COUNTER          3UL

#define EMIOS_CCR_MODE_GPIO_IN              0
#define EMIOS_CCR_MODE_GPIO_OUT             1U
#define EMIOS_CCR_MODE_SAIC                 2U
#define EMIOS_CCR_MODE_SAOC                 3U
#define EMIOS_CCR_MODE_IPWM                 4U
#define EMIOS_CCR_MODE_IPM                  5U
#define EMIOS_CCR_MODE_DAOC_B_MATCH         6U
#define EMIOS_CCR_MODE_DAOC_BOTH_MATCH      7U
#define EMIOS_CCR_MODE_MC_CMS               16U
#define EMIOS_CCR_MODE_MC_CME               17U
#define EMIOS_CCR_MODE_MC_UP_DOWN           18U
#define EMIOS_CCR_MODE_OPWMT                38U
#define EMIOS_CCR_MODE_MCB_UP               80U
#define EMIOS_CCR_MODE_MCB_UP_DOWN          84U
#define EMIOS_CCR_MODE_OPWFMB               88U
#define EMIOS_CCR_MODE_OPWMCB_TE            92U
#define EMIOS_CCR_MODE_OPWMCB_LE            93U
#define EMIOS_CCR_MODE_OPWMB                96U

#define EMIOSS_OVR                          (1UL << 31U)
#define EMIOSS_OVRC                         (1UL << 31U)
#define EMIOSS_OVFL                         (1UL << 15U)
#define EMIOSS_OVFLC                        (1UL << 15U)
#define EMIOSS_FLAG                         (1UL << 0)
#define EMIOSS_FLAGC                        (1UL << 0)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

#if SPC5_HAS_EMIOS0
/**
 * @brief   eMIOS0 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_EMIOS0_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_START_PCTL              (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eMIOS0 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_EMIOS0_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_STOP_PCTL               (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#endif

/**
 * @brief   eMIOS0 PWM functionality enable switch.
 * @details If set to @p TRUE the support for eMIOS0 PWM is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS0) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0                  FALSE
#endif

/**
 * @brief   eMIOS0 PWM counter bus A enable switch.
 */
#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS_A) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_A      FALSE
#endif

/**
 * @brief   eMIOS0 PWM counter bus B enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS_B) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_B      FALSE
#endif

/**
 * @brief   eMIOS0 PWM counter bus C enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS_C) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_C      FALSE
#endif

/**
 * @brief   eMIOS0 PWM counter bus D enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS_D) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_D      FALSE
#endif

/**
 * @brief   eMIOS0 PWM counter bus E enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS0_COUNT_BUS_E) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS_E      FALSE
#endif

/**
 * @brief   eMIOS0 ICU functionality enable switch.
 * @details If set to @p TRUE the support for eMIOS0 ICU is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0                  FALSE
#endif
#endif

#if SPC5_HAS_EMIOS1
/**
 * @brief   eMIOS1 peripheral configuration when started.
 * @note    The default configuration is 1 (always run) in run mode and
 *          2 (only halt) in low power mode.
 */
#if !defined(SPC5_EMIOS1_START_PCTL) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_START_PCTL              (SPC5_ME_PCTL_RUN(1) |  \
                                             SPC5_ME_PCTL_LP(2))
#endif

/**
 * @brief   eMIOS1 peripheral configuration when stopped.
 * @note    The default configuration is 0 (never run) in run mode and
 *          0 (never run) in low power mode.
 */
#if !defined(SPC5_EMIOS1_STOP_PCTL) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_STOP_PCTL               (SPC5_ME_PCTL_RUN(0) |  \
                                             SPC5_ME_PCTL_LP(0))
#endif

/**
 * @brief   eMIOS1 PWM functionality enable switch.
 * @details If set to @p TRUE the support for eMIOS1 PWM is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_PWM_USE_EMIOS1) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1                  FALSE
#endif

/**
 * @brief   eMIOS1 PWM counter bus A enable switch.
 */
#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS_A) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_A      FALSE
#endif

/**
 * @brief   eMIOS1 PWM counter bus B enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS_B) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_B      FALSE
#endif

/**
 * @brief   eMIOS1 PWM counter bus C enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS_C) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_C      FALSE
#endif

/**
 * @brief   eMIOS1 PWM counter bus D enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS_D) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_D      FALSE
#endif

/**
 * @brief   eMIOS1 PWM counter bus E enable switch.
 */

#if !defined(SPC5_PWM_USE_EMIOS1_COUNT_BUS_E) || defined(__DOXYGEN__)
#define SPC5_PWM_USE_EMIOS1_COUNT_BUS_E      FALSE
#endif

/**
 * @brief   eMIOS1 ICU functionality enable switch.
 * @details If set to @p TRUE the support for eMIOS1 ICU is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS1) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS1                  FALSE
#endif
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH0 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F0F1_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH3 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH2 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH3 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F2F3_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH5 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH4 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH5 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F4F5_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH7 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH6 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH7 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F6F7_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH8 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH9 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F8F9_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH10 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH11 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F10F11_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH12 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH13 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F12F13_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH14 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH15 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F14F15_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH16 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH17 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F16F17_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH18 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH19 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F18F19_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH20 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH21 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F20F21_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH22 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH23 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F22F23_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH24 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH25 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F24F25_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH26 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH27 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F26F27_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH28 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH29 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F28F29_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS0_CH30 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH31 == TRUE)
IRQ_HANDLER(SPC5_EMIOS0_GFR_F30F31_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH0 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F0F1_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH2 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH3 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F2F3_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH4 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH5 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F4F5_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH6 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH7 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F6F7_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH8 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH9 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F8F9_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH10 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH11 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F10F11_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH12 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH13 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F12F13_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH14 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH15 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F14F15_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH16 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH17 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F16F17_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH18 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH19 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F18F19_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH20 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH21 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F20F21_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH22 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH23 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F22F23_HANDLER);
#endif

#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH24 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH25 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F24F25_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH26 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH27 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F26F27_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH28 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH29 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F28F29_HANDLER);
#endif

#if (SPC5_PWM_USE_EMIOS1_CH30 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH31 == TRUE)
IRQ_HANDLER(SPC5_EMIOS1_GFR_F30F31_HANDLER);
#endif

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (SPC5_HAS_EMIOS0 == TRUE)
void reset_emios0_active_ch_group(void);
uint32_t get_emios0_active_ch_group(void);
void increase_emios0_active_ch_group(void);
void decrease_emios0_active_ch_group(void);
#if (LLD_USE_ICU == TRUE)
void icu_active_emios0_clock(ICUDriver *icup);
void icu_deactive_emios0_clock(ICUDriver *icup);
#endif
#if (LLD_USE_PWM == TRUE)
void pwm_active_emios0_clock(PWMDriver *pwmp);
void pwm_deactive_emios0_clock(PWMDriver *pwmp);
#endif
#endif
#if (SPC5_HAS_EMIOS1 == TRUE)
void reset_emios1_active_ch_group(void);
uint32_t get_emios1_active_ch_group(void);
void increase_emios1_active_ch_group(void);
void decrease_emios1_active_ch_group(void);
#if (LLD_USE_ICU == TRUE)
void icu_active_emios1_clock(ICUDriver *icup);
void icu_deactive_emios1_clock(ICUDriver *icup);
#endif
#if (LLD_USE_PWM == TRUE)
void pwm_active_emios1_clock(PWMDriver *pwmp);
void pwm_deactive_emios1_clock(PWMDriver *pwmp);
#endif
#endif

#endif /* LLD_USE_ICU || LLD_USE_PWM */

#endif /* _SPC5_EMIOS_H_ */

/** @} */
