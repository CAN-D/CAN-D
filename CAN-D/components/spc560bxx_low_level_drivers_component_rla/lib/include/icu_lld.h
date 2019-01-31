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
 * @file    icu_lld.h
 * @brief   SPC5xx ICU low level driver header.
 *
 * @addtogroup ICU
 * @{
 */

#ifndef _ICU_LLD_H_
#define _ICU_LLD_H_

#include "spc5_lld.h"
#include "lldconf.h"

#if (LLD_USE_ICU == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   ICUD1 driver enable switch.
 * @details If set to @p TRUE the support for ICUD1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH0) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH0             FALSE
#endif

/**
 * @brief   ICUD2 driver enable switch.
 * @details If set to @p TRUE the support for ICUD2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH1) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH1             FALSE
#endif

/**
 * @brief   ICUD3 driver enable switch.
 * @details If set to @p TRUE the support for ICUD3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH2) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH2             FALSE
#endif

/**
 * @brief   ICUD4 driver enable switch.
 * @details If set to @p TRUE the support for ICUD4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH3) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH3             FALSE
#endif

/**
 * @brief   ICUD5 driver enable switch.
 * @details If set to @p TRUE the support for ICUD5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH4) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH4             FALSE
#endif

/**
 * @brief   ICUD6 driver enable switch.
 * @details If set to @p TRUE the support for ICUD6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH5) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH5             FALSE
#endif

/**
 * @brief   ICUD7 driver enable switch.
 * @details If set to @p TRUE the support for ICUD7 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH6) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH6             FALSE
#endif

/**
 * @brief   ICUD8 driver enable switch.
 * @details If set to @p TRUE the support for ICUD8 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH7) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH7             FALSE
#endif

/**
 * @brief   ICUD9 driver enable switch.
 * @details If set to @p TRUE the support for ICUD9 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH8) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH8             FALSE
#endif

/**
 * @brief   ICUD10 driver enable switch.
 * @details If set to @p TRUE the support for ICUD10 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH16) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH16            FALSE
#endif

/**
 * @brief   ICUD11 driver enable switch.
 * @details If set to @p TRUE the support for ICUD11 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS0_CH24) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS0_CH24            FALSE
#endif

/**
 * @brief   ICUD1 and ICUD2 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F0F1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F0F1_PRIORITY       7
#endif

/**
 * @brief   ICUD3 and ICUD4 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F2F3_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F2F3_PRIORITY       7
#endif

/**
 * @brief   ICUD5 and ICUD6 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F4F5_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F4F5_PRIORITY       7
#endif

/**
 * @brief   ICUD7 and ICUD8 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F6F7_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F6F7_PRIORITY       7
#endif

/**
 * @brief   ICUD9 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F8F9_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F8F9_PRIORITY       7
#endif

/**
 * @brief   ICUD10 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F16F17_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F16F17_PRIORITY     7
#endif

/**
 * @brief   ICUD11 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS0_GFR_F24F25_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS0_GFR_F24F25_PRIORITY     7
#endif

/**
 * @brief   ICUD12 driver enable switch.
 * @details If set to @p TRUE the support for ICUD12 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS1_CH0) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS1_CH0             FALSE
#endif

/**
 * @brief   ICUD13 driver enable switch.
 * @details If set to @p TRUE the support for ICUD13 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS1_CH8) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS1_CH8             FALSE
#endif

/**
 * @brief   ICUD14 driver enable switch.
 * @details If set to @p TRUE the support for ICUD14 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS1_CH16) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS1_CH16            FALSE
#endif

/**
 * @brief   ICUD15 driver enable switch.
 * @details If set to @p TRUE the support for ICUD15 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(SPC5_ICU_USE_EMIOS1_CH24) || defined(__DOXYGEN__)
#define SPC5_ICU_USE_EMIOS1_CH24            FALSE
#endif

/**
 * @brief   ICUD12 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F0F1_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F0F1_PRIORITY       7
#endif

/**
 * @brief   ICUD13 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F8F9_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F8F9_PRIORITY       7
#endif

/**
 * @brief   ICUD14 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F16F17_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F16F17_PRIORITY     7
#endif

/**
 * @brief   ICUD15 interrupt priority level setting.
 */
#if !defined(SPC5_EMIOS1_GFR_F24F25_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_EMIOS1_GFR_F24F25_PRIORITY     7
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if (SPC5_ICU_USE_EMIOS0_CH0  == TRUE) || (SPC5_ICU_USE_EMIOS0_CH1  == TRUE) || \
    (SPC5_ICU_USE_EMIOS0_CH2  == TRUE) || (SPC5_ICU_USE_EMIOS0_CH3  == TRUE) || \
    (SPC5_ICU_USE_EMIOS0_CH4  == TRUE) || (SPC5_ICU_USE_EMIOS0_CH5  == TRUE) || \
    (SPC5_ICU_USE_EMIOS0_CH6  == TRUE) || (SPC5_ICU_USE_EMIOS0_CH7  == TRUE) || \
    (SPC5_ICU_USE_EMIOS0_CH8  == TRUE) || (SPC5_ICU_USE_EMIOS0_CH16 == TRUE) || \
    (SPC5_ICU_USE_EMIOS0_CH24 == TRUE)
#define SPC5_ICU_USE_EMIOS0                  TRUE
#else
#define SPC5_ICU_USE_EMIOS0                  FALSE
#endif

#if (SPC5_ICU_USE_EMIOS1_CH0  == TRUE) || (SPC5_ICU_USE_EMIOS1_CH8  == TRUE) || \
    (SPC5_ICU_USE_EMIOS1_CH16 == TRUE) || (SPC5_ICU_USE_EMIOS1_CH24 == TRUE)
#define SPC5_ICU_USE_EMIOS1                  TRUE
#else
#define SPC5_ICU_USE_EMIOS1                  FALSE
#endif

#if (SPC5_HAS_EMIOS0 == FALSE) && (SPC5_ICU_USE_EMIOS0 == TRUE)
#error "EMIOS0 not present in the selected device"
#endif

#if (SPC5_HAS_EMIOS1 == FALSE) && (SPC5_ICU_USE_EMIOS1 == TRUE)
#error "EMIOS1 not present in the selected device"
#endif

#if (SPC5_ICU_USE_EMIOS0 == FALSE) && (SPC5_ICU_USE_EMIOS1 == FALSE)
#error "ICU driver activated but no Channels assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing an ICU driver.
 */
typedef struct ICUDriver ICUDriver;

/**
 * @brief   ICU notification callback type.
 *
 * @param[in] icup      pointer to a @p ICUDriver object
 */
typedef void (*icucallback_t)(ICUDriver *icup);

/**
 * @brief ICU driver mode.
 */
typedef enum {
  ICU_INPUT_ACTIVE_HIGH = 0,        /**< Trigger on rising edge.            */
  ICU_INPUT_ACTIVE_LOW = 1          /**< Trigger on falling edge.           */
} icumode_t;

/**
 * @brief   ICU frequency type.
 */
typedef uint32_t icufreq_t;

/**
 * @brief   ICU counter type.
 */
typedef uint16_t icucnt_t;

/**
 * @brief   ICU pulse edge type.
 */
typedef int16_t icupe_t;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
  /**
   * @brief   Driver mode.
   */
  icumode_t                 mode;
  /**
   * @brief Counter prescaler.
   */
  uint8_t                   psc;
  /**
   * @brief   Callback for pulse width measurement.
   */
  icucallback_t             width_cb;
  /**
   * @brief   Callback for cycle period measurement.
   */
  icucallback_t             period_cb;
  /**
   * @brief   Callback for timer overflow.
   */
  icucallback_t             overflow_cb;
  /* End of the mandatory fields.*/
} ICUConfig;

/**
 * @brief   Pulse edge structure.
 * @note    It contains for each channel the temporary counter A2 
 *          values used to calculate the period and width of the 
 *          related input pulse.
 */
typedef struct {
  /**
   * @brief   Counter A2 value on the first pulse edge.
   * @note    First rising edge for ICU_INPUT_ACTIVE_HIGH,
   *          first falling edge for ICU_INPUT_ACTIVE_LOW.
   */
  icupe_t                   a2_1;
  /**
   * @brief   Counter A2 value on the second pulse edge.
   * @note    First falling edge for ICU_INPUT_ACTIVE_HIGH,
   *          first rising edge for ICU_INPUT_ACTIVE_LOW.
   */
  icupe_t                   a2_2;
  /**
   * @brief   Counter A2 value on the first pulse edge.
   * @note    Second rising edge for ICU_INPUT_ACTIVE_HIGH,
   *          second falling edge for ICU_INPUT_ACTIVE_LOW.
   */
  icupe_t                   a2_3;
} ICUPulseEdges;

/**
 * @brief   Structure representing an ICU driver.
 */
struct ICUDriver {
  /**
   * @brief eMIOSx channel number.
   */
  uint32_t                  emios_ch;
  /**
   * @brief Current configuration data.
   */
  const ICUConfig           *config;
  /**
   * @brief CH Counter clock.
   */
  uint32_t clock;
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the eMIOSx registers block.
   */
  volatile struct EMIOS_tag *emiosp;
  /**
   * @brief Last pulse edges.
   */
  ICUPulseEdges             pe;
  /**
   * @brief Last width capture value.
   */
  uint16_t                  width;
  /**
   * @brief Last period capture value.
   */
  uint16_t                  period;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the width of the latest pulse.
 * @details The pulse width is defined as number of ticks between the start
 *          edge and the stop edge.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @return              The number of ticks.
 *
 * @notapi
 */
#define icu_lld_get_width(icup) ((icup)->width)

/**
 * @brief   Returns the period of the latest cycle.
 * @details The period is defined as number of ticks between a start edge
 *          and the next start edge.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @return              The number of ticks.
 *
 * @notapi
 */
#define icu_lld_get_period(icup) ((icup)->period)
/** @} */

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD1;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH1 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD2;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD3;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH3 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD4;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD5;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH5 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD6;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD7;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH7 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD8;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD9;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD10;
#endif

#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD11;
#endif

#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD12;
#endif

#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD13;
#endif

#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD14;
#endif

#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE) && !defined(__DOXYGEN__)
extern ICUDriver ICUD15;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void icu_lld_init(void);
  void icu_lld_start(ICUDriver *icup, const ICUConfig *config);
  void icu_lld_stop(ICUDriver *icup);
  void icu_lld_enable(ICUDriver *icup);
  void icu_lld_disable(ICUDriver *icup);
  void icu_lld_serve_interrupt(ICUDriver *icup);
#ifdef __cplusplus
}
#endif

#endif /* LLD_USE_ICU */

#endif /* _ICU_LLD_H_ */

/** @} */
