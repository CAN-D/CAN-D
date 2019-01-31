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
 * @file    icu_lld.c
 * @brief   SPC5xx ICU low level driver code.
 *
 * @addtogroup ICU
 * @{
 */

#include "icu_lld.h"

#if (LLD_USE_ICU == TRUE) || defined(__DOXYGEN__)

#include "spc5_emios.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   ICUD1 driver identifier.
 * @note    The driver ICUD1 allocates the unified channel eMIOS0_CH0
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD1;
#endif

/**
 * @brief   ICUD2 driver identifier.
 * @note    The driver ICUD2 allocates the unified channel eMIOS0_CH1
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH1 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD2;
#endif

/**
 * @brief   ICUD3 driver identifier.
 * @note    The driver ICUD3 allocates the unified channel eMIOS0_CH2
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD3;
#endif

/**
 * @brief   ICUD4 driver identifier.
 * @note    The driver ICUD4 allocates the unified channel eMIOS0_CH3
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH3 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD4;
#endif

/**
 * @brief   ICUD5 driver identifier.
 * @note    The driver ICUD5 allocates the unified channel eMIOS0_CH4
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD5;
#endif

/**
 * @brief   ICUD6 driver identifier.
 * @note    The driver ICUD6 allocates the unified channel eMIOS0_CH5
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH5 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD6;
#endif

/**
 * @brief   ICUD7 driver identifier.
 * @note    The driver ICUD7 allocates the unified channel eMIOS0_CH6
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD7;
#endif

/**
 * @brief   ICUD8 driver identifier.
 * @note    The driver ICUD8 allocates the unified channel eMIOS0_CH7
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH7 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD8;
#endif

/**
 * @brief   ICUD9 driver identifier.
 * @note    The driver ICUD9 allocates the unified channel eMIOS0_CH8
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD9;
#endif

/**
 * @brief   ICUD10 driver identifier.
 * @note    The driver ICUD10 allocates the unified channel eMIOS0_CH16
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD10;
#endif

/**
 * @brief   ICUD11 driver identifier.
 * @note    The driver ICUD11 allocates the unified channel eMIOS0_CH24
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD11;
#endif

/**
 * @brief   ICUD12 driver identifier.
 * @note    The driver ICUD12 allocates the unified channel eMIOS1_CH0
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD12;
#endif

/**
 * @brief   ICUD13 driver identifier.
 * @note    The driver ICUD13 allocates the unified channel eMIOS1_CH8
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD13;
#endif

/**
 * @brief   ICUD14 driver identifier.
 * @note    The driver ICUD14 allocates the unified channel eMIOS1_CH16
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD14;
#endif

/**
 * @brief   ICUD15 driver identifier.
 * @note    The driver ICUD15 allocates the unified channel eMIOS1_CH24
 *          when enabled.
 */
#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE) || defined(__DOXYGEN__)
ICUDriver ICUD15;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief               ICU IRQ handler.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 */
void icu_lld_serve_interrupt(ICUDriver *icup) {
  uint32_t gfr = icup->emiosp->GFR.R;
  int16_t period, width;

  if ((gfr & (1UL << icup->emios_ch)) != 0U) {
    uint32_t sr = icup->emiosp->CH[icup->emios_ch].CSR.R;

    if (((sr & EMIOSS_OVFL) != 0U) && (icup->config->overflow_cb != NULL)) {
      icup->emiosp->CH[icup->emios_ch].CSR.R |= EMIOSS_OVFLC;
      icup->config->overflow_cb(icup);
    }
    if ((sr & EMIOSS_FLAG) != 0U) {
      icup->emiosp->CH[icup->emios_ch].CSR.R |= EMIOSS_FLAGC;
      if (icup->config->mode == ICU_INPUT_ACTIVE_HIGH) {
        if ((icup->emiosp->CH[icup->emios_ch].CSR.B.UCIN == 1U)  &&        \
            (icup->config->period_cb != NULL)) {
          icup->pe.a2_3 = (int16_t)icup->emiosp->CH[icup->emios_ch].CADR.R;
          period = (icup->pe.a2_3 - icup->pe.a2_1);
          icup->period = (uint16_t)(period);
          icup->config->period_cb(icup);
          icup->pe.a2_1 = icup->pe.a2_3;
        } else if ((icup->emiosp->CH[icup->emios_ch].CSR.B.UCIN == 0UL) && \
            (icup->config->width_cb != NULL)) {
          icup->pe.a2_2 = (int16_t)icup->emiosp->CH[icup->emios_ch].CADR.R;
          width = (icup->pe.a2_2 - icup->pe.a2_1);
          icup->width = (uint16_t)(width);
          icup->config->width_cb(icup); 
        } else {
          ; /*close if...else if as per MISRA rules*/
        }
      } else if (icup->config->mode == ICU_INPUT_ACTIVE_LOW) {
        if ((icup->emiosp->CH[icup->emios_ch].CSR.B.UCIN == 1U) &&         \
            (icup->config->width_cb != NULL)) {
          icup->pe.a2_2 = (int16_t)icup->emiosp->CH[icup->emios_ch].CADR.R;
          width = (icup->pe.a2_2 - icup->pe.a2_1);
          icup->width = (uint16_t)(width);
          icup->config->width_cb(icup); 
        } else if ((icup->emiosp->CH[icup->emios_ch].CSR.B.UCIN == 0UL) && \
            (icup->config->period_cb != NULL)) {
          icup->pe.a2_3 = (int16_t)icup->emiosp->CH[icup->emios_ch].CADR.R;
          period = (icup->pe.a2_3 - icup->pe.a2_1);
          icup->period = (uint16_t)(period);
          icup->config->period_cb(icup);
          icup->pe.a2_1 = icup->pe.a2_3;
        } else {
          ; /*close if...else if as per MISRA rules*/
        }
      } else {
        ; /*close if...else if as per MISRA rules*/
      }
    }
    if ((sr & EMIOSS_OVR) != 0U) {
      icup->emiosp->CH[icup->emios_ch].CSR.R |= EMIOSS_OVRC;
    }
  }
}

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level ICU driver initialization.
 *
 * @init
 */
void icu_lld_init(void) {

  /* eMIOSx channels initially all not in use.*/
#if (SPC5_HAS_EMIOS0 == TRUE)
  reset_emios0_active_ch_group();
#endif
#if (SPC5_HAS_EMIOS1 == TRUE)
  reset_emios1_active_ch_group();
#endif

#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE)
  /* Driver initialization.*/
  ICUD1.config = NULL;
  ICUD1.emiosp = &EMIOS_0;
  ICUD1.emios_ch = 0U;
  ICUD1.pe.a2_1 = 0;
  ICUD1.pe.a2_2 = 0;
  ICUD1.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH0 */

#if (SPC5_ICU_USE_EMIOS0_CH1 == TRUE)
  /* Driver initialization.*/
  ICUD2.config = NULL;
  ICUD2.emiosp = &EMIOS_0;
  ICUD2.emios_ch = 1U;
  ICUD2.pe.a2_1 = 0;
  ICUD2.pe.a2_2 = 0;
  ICUD2.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH1 */

#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE)
  /* Driver initialization.*/
  ICUD3.config = NULL;
  ICUD3.emiosp = &EMIOS_0;
  ICUD3.emios_ch = 2U;
  ICUD3.pe.a2_1 = 0;
  ICUD3.pe.a2_2 = 0;
  ICUD3.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH2 */

#if (SPC5_ICU_USE_EMIOS0_CH3 == TRUE)
  /* Driver initialization.*/
  ICUD4.config = NULL;
  ICUD4.emiosp = &EMIOS_0;
  ICUD4.emios_ch = 3U;
  ICUD4.pe.a2_1 = 0;
  ICUD4.pe.a2_2 = 0;
  ICUD4.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH3 */

#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE)
  /* Driver initialization.*/
  ICUD5.config = NULL;
  ICUD5.emiosp = &EMIOS_0;
  ICUD5.emios_ch = 4U;
  ICUD5.pe.a2_1 = 0;
  ICUD5.pe.a2_2 = 0;
  ICUD5.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH4 */

#if (SPC5_ICU_USE_EMIOS0_CH5 == TRUE)
  /* Driver initialization.*/
  ICUD6.config = NULL;
  ICUD6.emiosp = &EMIOS_0;
  ICUD6.emios_ch = 5U;
  ICUD6.pe.a2_1 = 0;
  ICUD6.pe.a2_2 = 0;
  ICUD6.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH5 */

#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE)
  /* Driver initialization.*/
  ICUD7.config = NULL;
  ICUD7.emiosp = &EMIOS_0;
  ICUD7.emios_ch = 6U;
  ICUD7.pe.a2_1 = 0;
  ICUD7.pe.a2_2 = 0;
  ICUD7.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH6 */

#if (SPC5_ICU_USE_EMIOS0_CH7 == TRUE)
  /* Driver initialization.*/
  ICUD8.config = NULL;
  ICUD8.emiosp = &EMIOS_0;
  ICUD8.emios_ch = 7U;
  ICUD8.pe.a2_1 = 0;
  ICUD8.pe.a2_2 = 0;
  ICUD8.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH7 */

#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE)
  /* Driver initialization.*/
  ICUD9.config = NULL;
  ICUD9.emiosp = &EMIOS_0;
  ICUD9.emios_ch = 8U;
  ICUD9.pe.a2_1 = 0;
  ICUD9.pe.a2_2 = 0;
  ICUD9.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH8 */

#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE)
  /* Driver initialization.*/
  ICUD10.config = NULL;
  ICUD10.emiosp = &EMIOS_0;
  ICUD10.emios_ch = 16U;
  ICUD10.pe.a2_1 = 0;
  ICUD10.pe.a2_2 = 0;
  ICUD10.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH16 */

#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE)
  /* Driver initialization.*/
  ICUD11.config = NULL;
  ICUD11.emiosp = &EMIOS_0;
  ICUD11.emios_ch = 24U;
  ICUD11.pe.a2_1 = 0;
  ICUD11.pe.a2_2 = 0;
  ICUD11.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS0_CH24 */

#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE)
  /* Driver initialization.*/
  ICUD12.config = NULL;
  ICUD12.emiosp = &EMIOS_1;
  ICUD12.emios_ch = 0U;
  ICUD12.pe.a2_1 = 0;
  ICUD12.pe.a2_2 = 0;
  ICUD12.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS1_CH0 */

#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE)
  /* Driver initialization.*/
  ICUD13.config = NULL;
  ICUD13.emiosp = &EMIOS_1;
  ICUD13.emios_ch = 8U;
  ICUD13.pe.a2_1 = 0;
  ICUD13.pe.a2_2 = 0;
  ICUD13.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS1_CH8 */

#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE)
  /* Driver initialization.*/
  ICUD14.config = NULL;
  ICUD14.emiosp = &EMIOS_1;
  ICUD14.emios_ch = 16U;
  ICUD14.pe.a2_1 = 0;
  ICUD14.pe.a2_2 = 0;
  ICUD14.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS1_CH16 */

#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE)
  /* Driver initialization.*/
  ICUD15.config = NULL;
  ICUD15.emiosp = &EMIOS_1;
  ICUD15.emios_ch = 24U;
  ICUD15.pe.a2_1 = 0;
  ICUD15.pe.a2_2 = 0;
  ICUD15.pe.a2_3 = 0;
#endif /* SPC5_ICU_USE_EMIOS1_CH24 */

#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE || SPC5_ICU_USE_EMIOS0_CH1 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F0F1_NUMBER].R = SPC5_EMIOS0_GFR_F0F1_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH0 || SPC5_ICU_USE_EMIOS0_CH1 */

#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE || SPC5_ICU_USE_EMIOS0_CH3 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F2F3_NUMBER].R = SPC5_EMIOS0_GFR_F2F3_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH2 || SPC5_ICU_USE_EMIOS0_CH3 */	

#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE || SPC5_ICU_USE_EMIOS0_CH5 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F4F5_NUMBER].R = SPC5_EMIOS0_GFR_F4F5_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH4 || SPC5_ICU_USE_EMIOS0_CH5 */	

#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE || SPC5_ICU_USE_EMIOS0_CH7 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F6F7_NUMBER].R = SPC5_EMIOS0_GFR_F6F7_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH6 || SPC5_ICU_USE_EMIOS0_CH7 */

#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F8F9_NUMBER].R = SPC5_EMIOS0_GFR_F8F9_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH8 */

#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F16F17_NUMBER].R = SPC5_EMIOS0_GFR_F16F17_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH16 */

#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE)
  INTC.PSR[SPC5_EMIOS0_GFR_F24F25_NUMBER].R = SPC5_EMIOS0_GFR_F24F25_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS0_CH24 */

#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE)
  INTC.PSR[SPC5_EMIOS1_GFR_F0F1_NUMBER].R = SPC5_EMIOS1_GFR_F0F1_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS1_CH0 */

#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE)
  INTC.PSR[SPC5_EMIOS1_GFR_F8F9_NUMBER].R = SPC5_EMIOS1_GFR_F8F9_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS1_CH8 */

#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE)
  INTC.PSR[SPC5_EMIOS1_GFR_F16F17_NUMBER].R = SPC5_EMIOS1_GFR_F16F17_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS1_CH16 */

#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE)
  INTC.PSR[SPC5_EMIOS1_GFR_F24F25_NUMBER].R = SPC5_EMIOS1_GFR_F24F25_PRIORITY;
#endif /* SPC5_ICU_USE_EMIOS1_CH24 */
}

/**
 * @brief   Configures and activates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 * @param[in] config    pointer to the @p ICUConfig object
 *
 * @api
 */
void icu_lld_start(ICUDriver *icup, const ICUConfig *config) {
  
  osalEnterCritical();
  
  icup->config = config;

  /* Update the number of active ICU channels.*/
  if (icup->emiosp == &EMIOS_0) {
    increase_emios0_active_ch_group();
  } else if (icup->emiosp == &EMIOS_1) {
    increase_emios1_active_ch_group();
  } else {
    ; /* close if...else if as per MISRA rules */
  }

  /* Set eMIOS0 Clock.*/
#if (SPC5_ICU_USE_EMIOS0 == TRUE)
  if (icup->emiosp == &EMIOS_0) {
    icu_active_emios0_clock(icup);
  }
#endif

  /* Set eMIOS1 Clock.*/
#if (SPC5_ICU_USE_EMIOS1 == TRUE)
  if (icup->emiosp == &EMIOS_1) {
    icu_active_emios1_clock(icup);
  }
#endif

  /* Configures the peripheral.*/

  /* Channel enables.*/
  icup->emiosp->UCDIS.R &= ~(1UL << icup->emios_ch);

  /* Clear pending IRQs (if any).*/
  icup->emiosp->CH[icup->emios_ch].CSR.R = EMIOSS_OVRC |
      EMIOSS_OVFLC | EMIOSS_FLAGC;

  icup->emiosp->CH[icup->emios_ch].CCR.B.UCPEN = 0;
  icup->emiosp->CH[icup->emios_ch].CCR.R |=
      EMIOSC_BSL(EMIOS_BSL_INTERNAL_COUNTER) |
      EMIOSC_EDSEL | EMIOS_CCR_MODE_SAIC;
  icup->emiosp->CH[icup->emios_ch].CCR.B.UCPRE = (uint8_t)(icup->config->psc - 1UL);
  icup->emiosp->CH[icup->emios_ch].CCR.R |= EMIOSC_UCPREN;

  /* Set source polarity.*/
  if(icup->config->mode == ICU_INPUT_ACTIVE_HIGH){
    icup->emiosp->CH[icup->emios_ch].CCR.R |= EMIOSC_EDPOL;
  } else {
    icup->emiosp->CH[icup->emios_ch].CCR.R &= ~EMIOSC_EDPOL;
  }

  /* Channel disables.*/
  icup->emiosp->UCDIS.R |= (1UL << icup->emios_ch);

  osalExitCritical();
}

/**
 * @brief   Deactivates the ICU peripheral.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icu_lld_stop(ICUDriver *icup) {

  osalEnterCritical();

  /* Reset UC Control Register.*/
  icup->emiosp->CH[icup->emios_ch].CCR.R = 0;

  /* Update the number of active ICU channels.*/
  if (icup->emiosp == &EMIOS_0) {
    decrease_emios0_active_ch_group();
  } else if (icup->emiosp == &EMIOS_1) {
    decrease_emios1_active_ch_group();
  } else {
    ; /* close if...else if as per MISRA rules */
  }

  /* eMIOS0 clock deactivation.*/
#if (SPC5_ICU_USE_EMIOS0 == TRUE)
  if (icup->emiosp == &EMIOS_0) {
    icu_deactive_emios0_clock(icup);
  }
#endif

  /* eMIOS1 clock deactivation.*/
#if (SPC5_ICU_USE_EMIOS1 == TRUE)
  if (icup->emiosp == &EMIOS_1) {
    icu_deactive_emios1_clock(icup);
  }
#endif

  osalExitCritical();
}

/**
 * @brief   Enables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icu_lld_enable(ICUDriver *icup) {

  osalEnterCritical();

  /* Channel enables.*/
  icup->emiosp->UCDIS.R &= ~(1UL << icup->emios_ch);

  /* Clear pending IRQs (if any).*/
  icup->emiosp->CH[icup->emios_ch].CSR.R = EMIOSS_OVRC |
      EMIOSS_OVFLC | EMIOSS_FLAGC;

  /* Active interrupts.*/
  if (icup->config->period_cb != NULL || icup->config->width_cb != NULL ||  \
      icup->config->overflow_cb != NULL) {
    icup->emiosp->CH[icup->emios_ch].CCR.B.FEN = 1U;
  }

  osalExitCritical();
}

/**
 * @brief   Disables the input capture.
 *
 * @param[in] icup      pointer to the @p ICUDriver object
 *
 * @api
 */
void icu_lld_disable(ICUDriver *icup) {

  osalEnterCritical();

  /* Clear pending IRQs (if any).*/
  icup->emiosp->CH[icup->emios_ch].CSR.R = EMIOSS_OVRC |
        EMIOSS_OVFLC | EMIOSS_FLAGC;

  /* Disable interrupts.*/
  icup->emiosp->CH[icup->emios_ch].CCR.B.FEN = 0;

  /* Channel disables.*/
  icup->emiosp->UCDIS.R |= (1UL << icup->emios_ch);

  osalExitCritical();
}

#endif /* LLD_USE_ICU */

/** @} */
