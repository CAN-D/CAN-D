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
 * @file    pwm_lld.c
 * @brief   SPC5xx PWM low level driver code.
 *
 * @addtogroup PWM
 * @{
 */

#include "pwm_lld.h"

#if (LLD_USE_PWM == TRUE) || defined(__DOXYGEN__)

#include "spc5_emios.h"

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   PWMD1 driver identifier.
 * @note    The driver PWMD1 allocates the unified channels eMIOS0_CH0-31 if
 *          counter bus A is selected or the unified channels eMIOS0_CH1-7 if
 *          counter bus B is selected.
 */
#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)) && !defined(__DOXYGEN__)
PWMDriver PWMD1;
#endif

/**
 * @brief   PWMD2 driver identifier.
 * @note    The driver PWMD2 allocates the unified channels eMIOS0_CH9-15 if
 *          counter bus C is selected.
 */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD2;
#endif

/**
 * @brief   PWMD3 driver identifier.
 * @note    The driver PWMD3 allocates the unified channels eMIOS0_CH17-23 if
 *          counter bus D is selected.
 */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD3;
#endif

/**
 * @brief   PWMD4 driver identifier.
 * @note    The driver PWMD4 allocates the unified channels eMIOS0_CH25-31 if
 *          counter bus E is selected.
 */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD4;
#endif

/**
 * @brief   PWMD5 driver identifier.
 * @note    The driver PWMD5 allocates the unified channels eMIOS1_CH0-31 if
 *          counter bus A is selected or the unified channels eMIOS1_CH1-7 if
 *          counter bus B is selected.
 */
#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)) && !defined(__DOXYGEN__)
PWMDriver PWMD5;
#endif

/**
 * @brief   PWMD6 driver identifier.
 * @note    The driver PWMD6 allocates the unified channels eMIOS1_CH9-15 if
 *          counter bus C is selected.
 */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD6;
#endif

/**
 * @brief   PWMD7 driver identifier.
 * @note    The driver PWMD7 allocates the unified channels eMIOS1_CH17-23 if
 *          counter bus D is selected.
 */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD7;
#endif

/**
 * @brief   PWMD8 driver identifier.
 * @note    The driver PWMD8 allocates the unified channels eMIOS1_CH25-31 if
 *          counter bus E is selected.
 */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE) && !defined(__DOXYGEN__)
PWMDriver PWMD8;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/**
 * @brief               IRQ handler for the channels used as period (i.e.
 *                      CH0, CH8, CH16 and CH24 when Counter_Bus_B_C_D_E is
 *                      selected, CH23 when Counter_Bus_A is selected).
 *
 * @param[in] pwmp      pointer to the @p PWMDriver object
 * @param[in] emios_ch  eMIOS channel number
 */
void pwm_lld_serve_period_interrupt(PWMDriver *pwmp, pwmchannel_t emios_ch) {

  uint32_t sr;

  sr = pwmp->emiosp->CH[emios_ch].CSR.R;
  if ((sr & EMIOSS_OVFL) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_OVFLC;
  }
  if ((sr & EMIOSS_OVR) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_OVRC;
  }
  if ((sr & EMIOSS_FLAG) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_FLAGC;
    if (pwmp->config->callback != NULL) {
      pwmp->config->callback(pwmp);
    }
  }

}

/**
 * @brief               IRQ handler for the PWM channels.
 *
 * @param[in] pwmp      pointer to the @p PWMDriver object
 * @param[in] emios_ch  eMIOS channel number
 */
void pwm_lld_serve_channel_interrupt(PWMDriver *pwmp, pwmchannel_t emios_ch) {

  uint32_t sr;
  pwmchannel_t conf_ch;

  sr = pwmp->emiosp->CH[emios_ch].CSR.R;
  if ((sr & EMIOSS_OVFL) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_OVFLC;
  }
  if ((sr & EMIOSS_OVR) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_OVRC;
  }
  if ((sr & EMIOSS_FLAG) != 0U) {
    pwmp->emiosp->CH[emios_ch].CSR.R |= EMIOSS_FLAGC;
    if (pwmp->period_ch == 23U) {
	  /* Skip period channel (23).*/
      if (emios_ch < 23U) {
        conf_ch = emios_ch;
      } else {
        conf_ch = emios_ch - 1U;
      }
    } else {
      conf_ch = (emios_ch%8U) - 1U;
    }
    if (pwmp->config->channels[conf_ch].callback != NULL) {
      pwmp->config->channels[conf_ch].callback(pwmp);
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
 * @brief   Low level PWM driver initialization.
 *
 * @init
 */
void pwm_lld_init(void) {
  /* eMIOSx channels initially all not in use.*/
#if (SPC5_HAS_EMIOS0 == TRUE)
  reset_emios0_active_ch_group();
#endif
#if (SPC5_HAS_EMIOS1 == TRUE)
  reset_emios1_active_ch_group();
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  /* Driver initialization.*/
  PWMD1.config = NULL;
  PWMD1.emiosp = &EMIOS_0;
  PWMD1.period_ch = 23U;
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  /* Driver initialization.*/
  PWMD1.config = NULL;
  PWMD1.emiosp = &EMIOS_0;
  PWMD1.period_ch = 0U;
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  /* Driver initialization.*/
  PWMD2.config = NULL;
  PWMD2.emiosp = &EMIOS_0;
  PWMD2.period_ch = 8U;
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  /* Driver initialization.*/
  PWMD3.config = NULL;
  PWMD3.emiosp = &EMIOS_0;
  PWMD3.period_ch = 16U;
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  /* Driver initialization.*/
  PWMD4.config = NULL;
  PWMD4.emiosp = &EMIOS_0;
  PWMD4.period_ch = 24U;
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_E */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  /* Driver initialization.*/
  PWMD5.config = NULL;
  PWMD5.emiosp = &EMIOS_1;
  PWMD5.period_ch = 23U;
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  /* Driver initialization.*/
  PWMD5.config = NULL;
  PWMD5.emiosp = &EMIOS_1;
  PWMD5.period_ch = 0U;
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  /* Driver initialization.*/
  PWMD6.config = NULL;
  PWMD6.emiosp = &EMIOS_1;
  PWMD6.period_ch = 8U;
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  /* Driver initialization.*/
  PWMD7.config = NULL;
  PWMD7.emiosp = &EMIOS_1;
  PWMD7.period_ch = 16U;
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  /* Driver initialization.*/
  PWMD8.config = NULL;
  PWMD8.emiosp = &EMIOS_1;
  PWMD8.period_ch = 24U;
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_E */

#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE))
  INTC.PSR[SPC5_EMIOS0_GFR_F0F1_NUMBER].R = SPC5_EMIOS0_GFR_F0F1_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F2F3_NUMBER].R = SPC5_EMIOS0_GFR_F2F3_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F4F5_NUMBER].R = SPC5_EMIOS0_GFR_F4F5_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F6F7_NUMBER].R = SPC5_EMIOS0_GFR_F6F7_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE))
  INTC.PSR[SPC5_EMIOS0_GFR_F8F9_NUMBER].R = SPC5_EMIOS0_GFR_F8F9_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F10F11_NUMBER].R = SPC5_EMIOS0_GFR_F10F11_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F12F13_NUMBER].R = SPC5_EMIOS0_GFR_F12F13_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F14F15_NUMBER].R = SPC5_EMIOS0_GFR_F14F15_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE))
  INTC.PSR[SPC5_EMIOS0_GFR_F16F17_NUMBER].R = SPC5_EMIOS0_GFR_F16F17_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F18F19_NUMBER].R = SPC5_EMIOS0_GFR_F18F19_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F20F21_NUMBER].R = SPC5_EMIOS0_GFR_F20F21_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F22F23_NUMBER].R = SPC5_EMIOS0_GFR_F22F23_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE))
  INTC.PSR[SPC5_EMIOS0_GFR_F24F25_NUMBER].R = SPC5_EMIOS0_GFR_F24F25_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F26F27_NUMBER].R = SPC5_EMIOS0_GFR_F26F27_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F28F29_NUMBER].R = SPC5_EMIOS0_GFR_F28F29_PRIORITY;
  INTC.PSR[SPC5_EMIOS0_GFR_F30F31_NUMBER].R = SPC5_EMIOS0_GFR_F30F31_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE))
  INTC.PSR[SPC5_EMIOS1_GFR_F0F1_NUMBER].R = SPC5_EMIOS1_GFR_F0F1_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F2F3_NUMBER].R = SPC5_EMIOS1_GFR_F2F3_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F4F5_NUMBER].R = SPC5_EMIOS1_GFR_F4F5_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F6F7_NUMBER].R = SPC5_EMIOS1_GFR_F6F7_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE))
  INTC.PSR[SPC5_EMIOS1_GFR_F8F9_NUMBER].R = SPC5_EMIOS1_GFR_F8F9_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F10F11_NUMBER].R = SPC5_EMIOS1_GFR_F10F11_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F12F13_NUMBER].R = SPC5_EMIOS1_GFR_F12F13_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F14F15_NUMBER].R = SPC5_EMIOS1_GFR_F14F15_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE))
  INTC.PSR[SPC5_EMIOS1_GFR_F16F17_NUMBER].R = SPC5_EMIOS1_GFR_F16F17_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F18F19_NUMBER].R = SPC5_EMIOS1_GFR_F18F19_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F20F21_NUMBER].R = SPC5_EMIOS1_GFR_F20F21_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F22F23_NUMBER].R = SPC5_EMIOS1_GFR_F22F23_PRIORITY;
#endif

#if ((SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE) || \
     (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE))
  INTC.PSR[SPC5_EMIOS1_GFR_F24F25_NUMBER].R = SPC5_EMIOS1_GFR_F24F25_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F26F27_NUMBER].R = SPC5_EMIOS1_GFR_F26F27_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F28F29_NUMBER].R = SPC5_EMIOS1_GFR_F28F29_PRIORITY;
  INTC.PSR[SPC5_EMIOS1_GFR_F30F31_NUMBER].R = SPC5_EMIOS1_GFR_F30F31_PRIORITY;
#endif

}

/**
 * @brief   Configures and activates a channels group.
 *
 * @param[in] pwmp      pointer to the @p PWMDriver object
 *
 * @notapi
 */
static void pwm_lld_start_channels_group(PWMDriver *pwmp) {

  pwmchannel_t group_start_ch;
  pwmchannel_t group_end_ch;
  pwmchannel_t emios_ch;
  pwmchannel_t conf_ch = 0U;
  uint32_t emios_bus_select;

  /* Set the first group channel and the last group channel based on the
     selected counter bus type.*/
  if (pwmp->period_ch == 23U) {
    /* Counter Bus A */
    group_start_ch = 0U;
    group_end_ch = PWM_COUNT_BUS_A_CH_NUM;
    emios_bus_select = EMIOSC_BSL(EMIOS_BSL_COUNTER_BUS_A);
  } else {
    /* Counter Bus B, C, D, E */
    group_start_ch = pwmp->period_ch + 1U;
    group_end_ch = pwmp->period_ch + PWM_COUNT_BUS_BCDE_CH_NUM;
    emios_bus_select = EMIOSC_BSL(EMIOS_BSL_COUNTER_BUS_2);
  }

  /* Enable the channel used as period.*/
  pwmp->emiosp->UCDIS.R &= ~(1UL << pwmp->period_ch);

  /* Clear pending IRQs (if any).*/
  pwmp->emiosp->CH[pwmp->period_ch].CSR.R = EMIOSS_OVRC | EMIOSS_OVFLC |
      EMIOSS_FLAGC;

  /* Init channel used as period.*/
  pwmp->emiosp->CH[pwmp->period_ch].CCR.B.UCPEN = 0;
  pwmp->emiosp->CH[pwmp->period_ch].CCNTR.R = 1U;
  pwmp->emiosp->CH[pwmp->period_ch].CADR.R = pwmp->config->period;
  pwmp->emiosp->CH[pwmp->period_ch].CCR.R |= EMIOSC_BSL(EMIOS_BSL_INTERNAL_COUNTER);
  pwmp->emiosp->CH[pwmp->period_ch].CCR.R |= EMIOS_CCR_MODE_MCB_UP;
  pwmp->emiosp->CH[pwmp->period_ch].CCR.B.UCPRE = (uint8_t)(pwmp->config->psc - 1U);
  pwmp->emiosp->CH[pwmp->period_ch].CCR.R |= EMIOSC_UCPREN;

  /* Setup the other group channels.*/
  if (pwmp->config->mode == PWM_ALIGN_EDGE) {
    for (emios_ch = group_start_ch; emios_ch <= group_end_ch; emios_ch++) {
      /* Skip period channel (23).*/
      if (pwmp->period_ch == 23U && emios_ch == 23U) {
        continue;
      }
      switch (pwmp->config->channels[conf_ch].mode) {
      case PWM_OUTPUT_DISABLED:
        conf_ch++;
        break;
      case PWM_OUTPUT_ACTIVE_HIGH:

        /* Channel enables.*/
        pwmp->emiosp->UCDIS.R &= ~(1UL << emios_ch);
  
        /* Clear pending IRQs (if any).*/
        pwmp->emiosp->CH[emios_ch].CSR.R = EMIOSS_OVRC | EMIOSS_OVFLC |
            EMIOSS_FLAGC;
  
        pwmp->emiosp->CH[emios_ch].CCR.B.UCPEN = 0;
        pwmp->emiosp->CH[emios_ch].CADR.R = 0;
        pwmp->emiosp->CH[emios_ch].CBDR.R = 0;
  
        /* Set output polarity.*/
        pwmp->emiosp->CH[emios_ch].CCR.R |= EMIOSC_EDPOL;
  
        /* Set unified channel mode.*/
        pwmp->emiosp->CH[emios_ch].CCR.R |= emios_bus_select;
        pwmp->emiosp->CH[emios_ch].CCR.R |= EMIOS_CCR_MODE_OPWMB;
  
        pwmp->emiosp->CH[emios_ch].CCR.B.UCPRE = (uint8_t)(pwmp->config->psc - 1U);
        pwmp->emiosp->CH[emios_ch].CCR.R |= EMIOSC_UCPREN;
  
        /* Channel disables.*/
        pwmp->emiosp->UCDIS.R |= (1UL << emios_ch);

        conf_ch++;
        break;
      case PWM_OUTPUT_ACTIVE_LOW:

        /* Channel enables.*/
        pwmp->emiosp->UCDIS.R &= ~(1UL << emios_ch);
  
        /* Clear pending IRQs (if any).*/
        pwmp->emiosp->CH[emios_ch].CSR.R = EMIOSS_OVRC | EMIOSS_OVFLC |
            EMIOSS_FLAGC;
  
        pwmp->emiosp->CH[emios_ch].CCR.B.UCPEN = 0;
        pwmp->emiosp->CH[emios_ch].CADR.R = 1U;
        pwmp->emiosp->CH[emios_ch].CBDR.R = 0;
  
        /* Set output polarity.*/
        pwmp->emiosp->CH[emios_ch].CCR.R &= ~EMIOSC_EDPOL;
  
        /* Set unified channel mode.*/
        pwmp->emiosp->CH[emios_ch].CCR.R |= emios_bus_select;
        pwmp->emiosp->CH[emios_ch].CCR.R |= EMIOS_CCR_MODE_OPWMB;
  
        pwmp->emiosp->CH[emios_ch].CCR.B.UCPRE = (uint8_t)(pwmp->config->psc - 1U);
        pwmp->emiosp->CH[emios_ch].CCR.R |= EMIOSC_UCPREN;
  
        /* Channel disables.*/
        pwmp->emiosp->UCDIS.R |= (1UL << emios_ch);

        conf_ch++;
        break;
      default:
        /* Nothing to do. */
        break;
      }
    }

    /* Channel disables.*/
    pwmp->emiosp->UCDIS.R |= (1UL << pwmp->period_ch);

  }
}

/**
 * @brief   Configures and activates the PWM peripheral.
 *
 * @param[in] pwmp      pointer to the @p PWMDriver object
 * @param[in] config    pointer to a @p PWMConfig object
 *
 * @api
 */
void pwm_lld_start(PWMDriver *pwmp, const PWMConfig *config) {

  osalEnterCritical();

  pwmp->config = config;
  pwmp->period = config->period;

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    increase_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_A */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    increase_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_B */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    increase_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_C */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  if (&PWMD3 == pwmp) {
    increase_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_D */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  if (&PWMD4 == pwmp) {
    increase_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_E */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    increase_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_A */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    increase_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_B */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    increase_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_C */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  if (&PWMD7 == pwmp) {
    increase_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_D */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  if (&PWMD8 == pwmp) {
    increase_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_E */

  /* Set eMIOS0 Clock.*/
#if (SPC5_PWM_USE_EMIOS0 == TRUE)
  if (pwmp->emiosp == &EMIOS_0) {
    pwm_active_emios0_clock(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0 */

  /* Set eMIOS1 Clock.*/
#if (SPC5_PWM_USE_EMIOS1 == TRUE)
  if (pwmp->emiosp == &EMIOS_1) {
    pwm_active_emios1_clock(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1 */

  /* Configures the peripheral.*/
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_A */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_B */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_C */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  if (&PWMD3 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_D */
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  if (&PWMD4 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_E */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_A */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_B */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_C */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  if (&PWMD7 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_D */
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  if (&PWMD8 == pwmp) {
    pwm_lld_start_channels_group(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_E */

  osalExitCritical();
}

/**
 * @brief   Deactivates the PWM peripheral.
 *
 * @param[in] pwmp      pointer to the @p PWMDriver object
 *
 * @api
 */
void pwm_lld_stop(PWMDriver *pwmp) {

  pwmchannel_t emios_ch;

  osalEnterCritical();

  /* Disables the peripheral.*/

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_A_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[emios_ch].CCR.R = 0;
    }
    decrease_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[emios_ch].CCR.R = 0;
    }
    decrease_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[8U + emios_ch].CCR.R = 0;
    }
    decrease_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D== TRUE)
  if (&PWMD3 == pwmp) {
    //* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[16U + emios_ch].CCR.R = 0;
    }
    decrease_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E== TRUE)
  if (&PWMD4 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[24U + emios_ch].CCR.R = 0;
    }
    decrease_emios0_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_E */
  
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_A_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[emios_ch].CCR.R = 0;
    }
    decrease_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[emios_ch].CCR.R = 0;
    }
    decrease_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[8U + emios_ch].CCR.R = 0;
    }
    decrease_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D== TRUE)
  if (&PWMD7 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[16U + emios_ch].CCR.R = 0;
    }
    decrease_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E== TRUE)
  if (&PWMD8 == pwmp) {
    /* Reset UC Control Register for all group channels.*/
    for (emios_ch = 0U; emios_ch < PWM_COUNT_BUS_BCDE_CH_NUM + 1U; emios_ch++) {
      pwmp->emiosp->CH[24U + emios_ch].CCR.R = 0;
    }
    decrease_emios1_active_ch_group();
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_E */

  /* eMIOS0 clock deactivation.*/
#if (SPC5_PWM_USE_EMIOS0 == TRUE)
  if (pwmp->emiosp == &EMIOS_0) {
    pwm_deactive_emios0_clock(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS0 */

  /* eMIOS1 clock deactivation.*/
#if (SPC5_PWM_USE_EMIOS1 == TRUE)
  if (pwmp->emiosp == &EMIOS_1) {
    pwm_deactive_emios1_clock(pwmp);
  }
#endif /* SPC5_PWM_USE_EMIOS1 */

  osalExitCritical();
}

/**
 * @brief   Changes the period of the PWM peripheral.
 * @details This function changes the period of a PWM unit that has already
 *          been activated using @p pwm_lld_start().
 * @pre     The PWM unit must have been activated using @p pwm_lld_start().
 * @post    The PWM unit period is changed to the new value.
 * @note    The function has effect at the next cycle start.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behaviour is not
 *          guaranteed.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] period    new period in ticks
 *
 * @api
 */
void pwm_lld_change_period(PWMDriver *pwmp, pwmcnt_t period) {

  osalEnterCritical();

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[23U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[0U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[8U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  if (&PWMD3 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[16U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  if (&PWMD4 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[24U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS0_COUNT_BUS_E */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[23U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_A */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[0U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_B */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[8U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_C */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  if (&PWMD7 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[16U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_D */

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  if (&PWMD8 == pwmp) {
    pwmp->period = period;
    pwmp->emiosp->CH[24U].CADR.R = period;
  }
#endif /* SPC5_PWM_USE_EMIOS1_COUNT_BUS_E */

  osalExitCritical();
}

/**
 * @brief   Enables a PWM channel within a specific channels group.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] pwm_ch    PWM channel identifier (0...PWM_COUNT_BUS_A_CH_NUM-1 if
 *                      Counter Bus A is selected, 0...PWM_COUNT_BUS_BCDE_CH_NUM-1
 *                      if Counter Bus B_C_D_E is selected)
 * @param[in] width     PWM pulse width as clock pulses number
 * @param[in] deadtime  PWM pulse deadtime as clock pulses number
 *
 * @notapi
 */
static void pwm_lld_enable_group_channel(PWMDriver *pwmp,
                                         pwmchannel_t pwm_ch,
                                         pwmcnt_t width,
                                         pwmcnt_t deadtime) {

  pwmchannel_t emios_ch;

  if (pwmp->period_ch == 23U) {
    /* Counter Bus A */
    if (pwm_ch < 23U) {
      emios_ch = pwm_ch;
    } else {
      emios_ch = pwm_ch + 1U;
    }
  } else {
    /* Counter Bus B, C, D, E */
    emios_ch = pwmp->period_ch + pwm_ch + 1U;
  }

  /* Channel enables.*/
  pwmp->emiosp->UCDIS.R &= ~(1UL << emios_ch);
  
  /* Clear pending IRQs (if any).*/
  pwmp->emiosp->CH[emios_ch].CSR.R = EMIOSS_OVRC | EMIOSS_OVFLC |
      EMIOSS_FLAGC;
  
  /* Set PWM deadtime and width.*/
  pwmp->emiosp->CH[emios_ch].CADR.R = deadtime;
  pwmp->emiosp->CH[emios_ch].CBDR.R = width + deadtime;
  
  /* Active interrupts.*/
  if (pwmp->config->channels[pwm_ch].callback != NULL) {
    pwmp->emiosp->CH[emios_ch].CCR.B.FEN = 1U;
  }
  
  /* Enables timer base channel if disable.*/
  if ((pwmp->emiosp->UCDIS.R & (1UL << pwmp->period_ch)) != 0U) {
    /* Channel enables.*/
    pwmp->emiosp->UCDIS.R &= ~(1UL << pwmp->period_ch);
  
    /* Active interrupts.*/
    if (pwmp->config->callback != NULL ) {
      pwmp->emiosp->CH[pwmp->period_ch].CCR.B.FEN = 1U;
    }
  }
}

/**
 * @brief   Enables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwm_lld_start().
 * @post    The channel is active using the specified configuration.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 * @note    If a period is shorter than (pulse width + deadtime) then the
 *          behaviour is not guaranteed.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] pwm_ch    PWM channel identifier (0...PWM_COUNT_BUS_A_CH_NUM-1 if
 *                      Counter Bus A is selected, 0...PWM_COUNT_BUS_BCDE_CH_NUM-1
 *                      if Counter Bus B_C_D_E is selected)
 * @param[in] width     PWM pulse width as clock pulses number
 * @param[in] deadtime  PWM pulse deadtime as clock pulses number
 *
 * @api
 */
void pwm_lld_enable_channel(PWMDriver *pwmp,
                            pwmchannel_t pwm_ch,
                            pwmcnt_t width,
                            pwmcnt_t deadtime) {

  osalEnterCritical();

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  if (&PWMD3 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  if (&PWMD4 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  if (&PWMD7 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  if (&PWMD8 == pwmp) {
    pwm_lld_enable_group_channel(pwmp, pwm_ch, width, deadtime);
  }
#endif

  osalExitCritical();
}

/**
 * @brief   Disables a PWM channel within a specific channels group.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] pwm_ch    PWM channel identifier (0...PWM_COUNT_BUS_A_CH_NUM-1 if
 *                      Counter Bus A is selected, 0...PWM_COUNT_BUS_BCDE_CH_NUM-1
 *                      if Counter Bus B_C_D_E is selected)
 *
 * @notapi
 */
static void pwm_lld_disable_group_channel(PWMDriver *pwmp,
                                          pwmchannel_t pwm_ch) {

  pwmchannel_t emios_ch;
  uint32_t ucdis_reg_value;

  if (pwmp->period_ch == 23U) {
    /* Counter Bus A */
    if (pwm_ch < 23U) {
      emios_ch = pwm_ch;
    } else {
      emios_ch = pwm_ch + 1U;
    }
  } else {
    /* Counter Bus B, C, D, E */
    emios_ch = pwm_ch%8U + 1U;
  }
  /* Clear pending IRQs (if any).*/
  pwmp->emiosp->CH[emios_ch].CSR.R = EMIOSS_OVRC |
        EMIOSS_OVFLC | EMIOSS_FLAGC;
  
  /* Disable interrupts.*/
  pwmp->emiosp->CH[emios_ch].CCR.B.FEN = 0;
  
  /* Disable channel.*/
  pwmp->emiosp->UCDIS.R |= (1UL << emios_ch);

  /* The ucdis_reg_value is a temporary variable used in the following
     if-structure to make it compatible with the misra rules.*/
  ucdis_reg_value = pwmp->emiosp->UCDIS.R;

  /* Disable timer base channel if all PWM channels are disabled.*/
  if (((pwmp->period_ch == 23U) && (ucdis_reg_value == 0xFF7FFFFFUL)) || 
      ((ucdis_reg_value & (0xFEUL << pwmp->period_ch)) == (0xFEUL << pwmp->period_ch))) {
    /* Deactive interrupts.*/
    pwmp->emiosp->CH[pwmp->period_ch].CCR.B.FEN = 0;
  
    /* Disable channel.*/
    pwmp->emiosp->UCDIS.R |= (1UL << pwmp->period_ch);
  }
}

/**
 * @brief   Disables a PWM channel.
 * @pre     The PWM unit must have been activated using @p pwm_lld_start().
 * @post    The channel is disabled and its output line returned to the
 *          idle state.
 * @note    Depending on the hardware implementation this function has
 *          effect starting on the next cycle (recommended implementation)
 *          or immediately (fallback implementation).
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] pwm_ch    PWM channel identifier (0...PWM_COUNT_BUS_A_CH_NUM-1 if
 *                      Counter Bus A is selected, 0...PWM_COUNT_BUS_BCDE_CH_NUM-1
 *                      if Counter Bus B_C_D_E is selected)
 *
 * @api
 */
void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t pwm_ch) {

  osalEnterCritical();

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
  if (&PWMD1 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
  if (&PWMD2 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
  if (&PWMD3 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
  if (&PWMD4 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
  if (&PWMD5 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
  if (&PWMD6 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
  if (&PWMD7 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
  if (&PWMD8 == pwmp) {
    pwm_lld_disable_group_channel(pwmp, pwm_ch);
  }
#endif

  osalExitCritical();
}

#endif /* LLD_USE_PWM */

/** @} */
