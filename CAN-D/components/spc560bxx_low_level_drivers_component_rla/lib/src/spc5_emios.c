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
 * @file    spc5_emios.c
 * @brief   SPC5xx ICU-PWM low level drivers common code.
 *
 * @addtogroup SPC5xx_eMIOS
 * @{
 */

#include "spc5_emios.h"

#if (LLD_USE_ICU == TRUE) || (LLD_USE_PWM == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Number of active eMIOSx Channels.
 */
#if (SPC5_HAS_EMIOS0 == TRUE)
static uint32_t emios0_active_ch_group;
#endif
#if (SPC5_HAS_EMIOS1 == TRUE)
static uint32_t emios1_active_ch_group;
#endif

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

#if (SPC5_HAS_EMIOS0 == TRUE)
#if (SPC5_PWM_USE_EMIOS0 == TRUE) || (SPC5_ICU_USE_EMIOS0 == TRUE)
static uint32_t get_emios0_gfr(void) {
  volatile struct EMIOS_tag *emiosp0;

  emiosp0 = &EMIOS_0;
  return emiosp0->GFR.R;
}
#endif /* SPC5_PWM_USE_EMIOS0 || SPC5_ICU_USE_EMIOS0 */

void reset_emios0_active_ch_group(void) {
  emios0_active_ch_group = 0;
}

uint32_t get_emios0_active_ch_group(void) {
  return emios0_active_ch_group;
}

void increase_emios0_active_ch_group(void) {
  emios0_active_ch_group++;
}

void decrease_emios0_active_ch_group(void) {
  emios0_active_ch_group--;
}

#if (LLD_USE_ICU == TRUE)
void icu_active_emios0_clock(ICUDriver *icup) {
  /* If this is the first Channel activated then the eMIOS0 is enabled.*/
  if (emios0_active_ch_group == 1U) {
    SPCSetPeripheralClockMode(SPC5_EMIOS0_PCTL,
                                 SPC5_EMIOS0_START_PCTL);

    /* Disable all unified channels.*/
    icup->emiosp->MCR.B.GPREN = 0U;
    icup->emiosp->MCR.R = EMIOSMCR_GPRE(SPC5_EMIOS0_GPRE_VALUE - 1UL);
    icup->emiosp->MCR.R |= EMIOSMCR_GPREN;

    icup->emiosp->MCR.B.GTBE = 1U;

    icup->emiosp->UCDIS.R = 0xFFFFFFFFUL;

  }
}

void icu_deactive_emios0_clock(ICUDriver *icup) {
  /* If it is the last active channels then the eMIOS0 is disabled.*/
  if (emios0_active_ch_group == 0U) {
    if (icup->emiosp->UCDIS.R == 0U) {
      SPCSetPeripheralClockMode(SPC5_EMIOS0_PCTL,
                                   SPC5_EMIOS0_STOP_PCTL);
    }
  }
}
#endif

#if (LLD_USE_PWM == TRUE)
void pwm_active_emios0_clock(PWMDriver *pwmp) {
  /* If this is the first Channel activated then the eMIOS0 is enabled.*/
  if (emios0_active_ch_group == 1U) {
    SPCSetPeripheralClockMode(SPC5_EMIOS0_PCTL,
                                 SPC5_EMIOS0_START_PCTL);

    /* Disable all unified channels.*/
    pwmp->emiosp->MCR.B.GPREN = 0U;
    pwmp->emiosp->MCR.R = EMIOSMCR_GPRE(SPC5_EMIOS0_GPRE_VALUE - 1UL);
    pwmp->emiosp->MCR.R |= EMIOSMCR_GPREN;

    pwmp->emiosp->MCR.B.GTBE = 1U;

    pwmp->emiosp->UCDIS.R = 0xFFFFFFFFUL;

  }
}

void pwm_deactive_emios0_clock(PWMDriver *pwmp) {
  /* If it is the last active channels then the eMIOS0 is disabled.*/
  if (emios0_active_ch_group == 0U) {
    if (pwmp->emiosp->UCDIS.R == 0U) {
      SPCSetPeripheralClockMode(SPC5_EMIOS0_PCTL,
                                   SPC5_EMIOS0_STOP_PCTL);
    }
  }
}
#endif
#endif

#if (SPC5_HAS_EMIOS1 == TRUE)
#if (SPC5_PWM_USE_EMIOS1 == TRUE) || (SPC5_ICU_USE_EMIOS1 == TRUE)
static uint32_t get_emios1_gfr(void) {
  volatile struct EMIOS_tag *emiosp1;

  emiosp1 = &EMIOS_1;
  return emiosp1->GFR.R;
}
#endif /* SPC5_PWM_USE_EMIOS1 || SPC5_ICU_USE_EMIOS1 */

void reset_emios1_active_ch_group(void) {
  emios1_active_ch_group = 0;
}

uint32_t get_emios1_active_ch_group(void) {
  return emios1_active_ch_group;
}

void increase_emios1_active_ch_group(void) {
  emios1_active_ch_group++;
}

void decrease_emios1_active_ch_group(void) {
  emios1_active_ch_group--;
}

#if (LLD_USE_ICU == TRUE)
void icu_active_emios1_clock(ICUDriver *icup) {
  /* If this is the first Channel activated then the eMIOS1 is enabled.*/
  if (emios1_active_ch_group == 1U) {
    SPCSetPeripheralClockMode(SPC5_EMIOS1_PCTL,
                                 SPC5_EMIOS1_START_PCTL);

    /* Disable all unified channels.*/
    icup->emiosp->MCR.B.GPREN = 0U;
    icup->emiosp->MCR.R = EMIOSMCR_GPRE(SPC5_EMIOS1_GPRE_VALUE - 1UL);
    icup->emiosp->MCR.R |= EMIOSMCR_GPREN;

    icup->emiosp->MCR.B.GTBE = 1U;

    icup->emiosp->UCDIS.R = 0xFFFFFFFFUL;

  }
}

void icu_deactive_emios1_clock(ICUDriver *icup) {
  /* If it is the last active channels then the eMIOS1 is disabled.*/
  if (emios1_active_ch_group == 0U) {
    if (icup->emiosp->UCDIS.R == 0U) {
      SPCSetPeripheralClockMode(SPC5_EMIOS1_PCTL,
                                   SPC5_EMIOS1_STOP_PCTL);
    }
  }
}
#endif

#if (LLD_USE_PWM == TRUE)
void pwm_active_emios1_clock(PWMDriver *pwmp) {
  /* If this is the first Channel activated then the eMIOS1 is enabled.*/
  if (emios1_active_ch_group == 1U) {
    SPCSetPeripheralClockMode(SPC5_EMIOS1_PCTL,
                                 SPC5_EMIOS1_START_PCTL);

    /* Disable all unified channels.*/
    pwmp->emiosp->MCR.B.GPREN = 0U;
    pwmp->emiosp->MCR.R = EMIOSMCR_GPRE(SPC5_EMIOS1_GPRE_VALUE - 1UL);
    pwmp->emiosp->MCR.R |= EMIOSMCR_GPREN;

    pwmp->emiosp->MCR.B.GTBE = 1U;

    pwmp->emiosp->UCDIS.R = 0xFFFFFFFFUL;

  }
}

void pwm_deactive_emios1_clock(PWMDriver *pwmp) {
  /* If it is the last active channels then the eMIOS1 is disabled.*/
  if (emios1_active_ch_group == 0U) {
    if (pwmp->emiosp->UCDIS.R == 0U) {
      SPCSetPeripheralClockMode(SPC5_EMIOS1_PCTL,
                                   SPC5_EMIOS1_STOP_PCTL);
    }
  }
}
#endif
#endif

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH0 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F0F1_HANDLER)
#error "SPC5_EMIOS0_GFR_F0F1_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 0 and 1 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F0F1_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 0U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH0 == TRUE)
    icu_lld_serve_interrupt(&ICUD1);
#elif (SPC5_PWM_USE_EMIOS0_CH0 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 0U);
#elif (SPC5_PWM_USE_EMIOS0_COUNT_BUS_B == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD1, 0U);
#endif
  }
  if ((gfr & (1UL << 1U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH1 == TRUE)
    icu_lld_serve_interrupt(&ICUD2);
#elif (SPC5_PWM_USE_EMIOS0_CH1 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 1U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH3 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH2 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH3 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F2F3_HANDLER)
#error "SPC5_EMIOS0_GFR_F2F3_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 2 and 3 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F2F3_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 2U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH2 == TRUE)
    icu_lld_serve_interrupt(&ICUD3);
#elif (SPC5_PWM_USE_EMIOS0_CH2 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 2U);
#endif
  }
  if ((gfr & (1UL << 3U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH3 == TRUE)
    icu_lld_serve_interrupt(&ICUD4);
#elif (SPC5_PWM_USE_EMIOS0_CH3 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 3U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH5 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH4 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH5 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F4F5_HANDLER)
#error "SPC5_EMIOS0_GFR_F4F5_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 4 and 5 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F4F5_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 4U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH4 == TRUE)
    icu_lld_serve_interrupt(&ICUD5);
#elif (SPC5_PWM_USE_EMIOS0_CH4 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 4U);
#endif
  }
  if ((gfr & (1UL << 5U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH5 == TRUE)
    icu_lld_serve_interrupt(&ICUD6);
#elif (SPC5_PWM_USE_EMIOS0_CH5 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 5U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE) || (SPC5_ICU_USE_EMIOS0_CH7 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH6 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH7 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F6F7_HANDLER)
#error "SPC5_EMIOS0_GFR_F6F7_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 6 and 7 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F6F7_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 6U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH6 == TRUE)
    icu_lld_serve_interrupt(&ICUD7);
#elif (SPC5_PWM_USE_EMIOS0_CH6 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 6U);
#endif
  }
  if ((gfr & (1UL << 7U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH7 == TRUE)
    icu_lld_serve_interrupt(&ICUD8);
#elif (SPC5_PWM_USE_EMIOS0_CH7 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 7U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH8 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH9 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F8F9_HANDLER)
#error "SPC5_EMIOS0_GFR_F8F9_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 8 and 9 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F8F9_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 8U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH8 == TRUE)
    icu_lld_serve_interrupt(&ICUD9);
#elif (SPC5_PWM_USE_EMIOS0_CH8 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 8U);
#elif (SPC5_PWM_USE_EMIOS0_COUNT_BUS_C == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD2, 8U);
#endif
  }
  if ((gfr & (1UL << 9U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH9 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 9U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 9U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH10 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH11 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F10F11_HANDLER)
#error "SPC5_EMIOS0_GFR_F10F11_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 10 and 11 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F10F11_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 10U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH10 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 10U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 10U);
#endif
#endif
  }
  if ((gfr & (1UL << 11U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH11 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 11U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 11U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH12 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH13 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F12F13_HANDLER)
#error "SPC5_EMIOS0_GFR_F12F13_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 12 and 13 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F12F13_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 12U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH12 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 12U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 12U);
#endif
#endif
  }
  if ((gfr & (1UL << 13U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH13 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 13U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 13U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH14 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH15 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F14F15_HANDLER)
#error "SPC5_EMIOS0_GFR_F14F15_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 14 and 15 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F14F15_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 14U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH14 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 14U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 14U);
#endif
#endif
  }
  if ((gfr & (1UL << 15U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH15 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 15U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD2, 15U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH16 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH17 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F16F17_HANDLER)
#error "SPC5_EMIOS0_GFR_F8F9_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 16 and 17 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F16F17_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 16U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH16 == TRUE)
    icu_lld_serve_interrupt(&ICUD10);
#elif (SPC5_PWM_USE_EMIOS0_CH16 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 16U);
#elif (SPC5_PWM_USE_EMIOS0_COUNT_BUS_D == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD3, 16U);
#endif
  }
  if ((gfr & (1UL << 17U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH17 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 17U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 17U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH18 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH19 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F18F19_HANDLER)
#error "SPC5_EMIOS0_GFR_F18F19_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 18 and 19 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F18F19_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 18U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH18 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 18U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 18U);
#endif
#endif
  }
  if ((gfr & (1UL << 19U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH19 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 19U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 19U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH20 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH21 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F20F21_HANDLER)
#error "SPC5_EMIOS0_GFR_F20F21_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 20 and 21 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F20F21_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 20U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH20 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 20U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 20U);
#endif
#endif
  }
  if ((gfr & (1UL << 21U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH21 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 21U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 21U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH22 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH23 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F22F23_HANDLER)
#error "SPC5_EMIOS0_GFR_F22F23_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 22 and 23 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F22F23_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 22U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH22 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 22U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD3, 22U);
#endif
#endif
  }
  if ((gfr & (1UL << 23U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD1, 23U);
#elif (SPC5_PWM_USE_EMIOS0_CH23 == TRUE)
	pwm_lld_serve_channel_interrupt(&PWMD3, 23U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_CH24 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH25 == TRUE) || \
    (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F24F25_HANDLER)
#error "SPC5_EMIOS0_GFR_F24F25_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 24 and 25 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F24F25_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 24U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS0_CH24 == TRUE)
    icu_lld_serve_interrupt(&ICUD11);
#elif (SPC5_PWM_USE_EMIOS0_CH24 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 24U);
#elif (SPC5_PWM_USE_EMIOS0_COUNT_BUS_E == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD4, 24U);
#endif
  }
  if ((gfr & (1UL << 25U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH25 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 25U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 25U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH26 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH27 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F26F27_HANDLER)
#error "SPC5_EMIOS0_GFR_F26F27_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 26 and 27 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F26F27_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 26U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH26 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 26U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 26U);
#endif
#endif
  }
  if ((gfr & (1UL << 27U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH27 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 27U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 27U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH28 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH29 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F28F29_HANDLER)
#error "SPC5_EMIOS0_GFR_F28F29_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 28 and 29 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F28F29_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 28U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH28 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 28U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 28U);
#endif
#endif
  }
  if ((gfr & (1UL << 29U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH29 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 29U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 29U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS0_CH30 == TRUE) || (SPC5_PWM_USE_EMIOS0_CH31 == TRUE)
#if !defined(SPC5_EMIOS0_GFR_F30F31_HANDLER)
#error "SPC5_EMIOS0_GFR_F30F31_HANDLER not defined"
#endif
/**
 * @brief   eMIOS0 Channels 30 and 31 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS0_GFR_F30F31_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios0_gfr();

  if ((gfr & (1UL << 30U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH30 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 30U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 30U);
#endif
#endif
  }
  if ((gfr & (1UL << 31U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS0_CH31 == TRUE)
#if (SPC5_PWM_USE_EMIOS0_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD1, 31U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD4, 31U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH0 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH1 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F0F1_HANDLER)
#error "SPC5_EMIOS1_GFR_F0F1_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 0 and 1 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F0F1_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 0U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS1_CH0 == TRUE)
    icu_lld_serve_interrupt(&ICUD12);
#elif (SPC5_PWM_USE_EMIOS1_CH0 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 0U);
#elif (SPC5_PWM_USE_EMIOS1_COUNT_BUS_B == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD5, 0U);
#endif
  }
  if ((gfr & (1UL << 1U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH1 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 1U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH2 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH3 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F2F3_HANDLER)
#error "SPC5_EMIOS1_GFR_F2F3_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 2 and 3 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F2F3_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 2U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH2 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 2U);
#endif
  }
  if ((gfr & (1UL << 3U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH3 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 3U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH4 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH5 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F4F5_HANDLER)
#error "SPC5_EMIOS1_GFR_F4F5_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 4 and 5 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F4F5_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 4U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH4 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 4U);
#endif
  }
  if ((gfr & (1UL << 5U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH5 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 5U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH6 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH7 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F6F7_HANDLER)
#error "SPC5_EMIOS1_GFR_F6F7_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 6 and 7 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F6F7_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 6U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH6 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 6U);
#endif
  }
  if ((gfr & (1UL << 7U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH7 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 7U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH8 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH9 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F8F9_HANDLER)
#error "SPC5_EMIOS1_GFR_F8F9_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 8 and 9 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F8F9_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 8U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS1_CH8 == TRUE)
    icu_lld_serve_interrupt(&ICUD13);
#elif (SPC5_PWM_USE_EMIOS1_CH8 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 8U);
#elif (SPC5_PWM_USE_EMIOS1_COUNT_BUS_C == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD6, 8U);
#endif
  }
  if ((gfr & (1UL << 9U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH9 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 9U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 9U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH10 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH11 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F10F11_HANDLER)
#error "SPC5_EMIOS1_GFR_F10F11_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 10 and 11 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F10F11_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 10U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH10 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 10U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 10U);
#endif
#endif
  }
  if ((gfr & (1UL << 11U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH11 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 11U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 11U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH12 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH13 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F12F13_HANDLER)
#error "SPC5_EMIOS1_GFR_F12F13_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 12 and 13 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F12F13_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 12U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH12 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 12U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 12U);
#endif
#endif
  }
  if ((gfr & (1UL << 13U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH13 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 13U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 13U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH14 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH15 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F14F15_HANDLER)
#error "SPC5_EMIOS1_GFR_F14F15_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 14 and 15 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F14F15_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 14U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH14 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 14U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 14U);
#endif
#endif
  }
  if ((gfr & (1UL << 15U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH15 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 15U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD6, 15U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH16 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH17 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F16F17_HANDLER)
#error "SPC5_EMIOS1_GFR_F8F9_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 16 and 17 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F16F17_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 16U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS1_CH16 == TRUE)
    icu_lld_serve_interrupt(&ICUD14);
#elif (SPC5_PWM_USE_EMIOS1_CH16 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 16U);
#elif (SPC5_PWM_USE_EMIOS1_COUNT_BUS_D == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD7, 16U);
#endif
  }
  if ((gfr & (1UL << 17U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH17 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 17U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 17U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH18 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH19 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F18F19_HANDLER)
#error "SPC5_EMIOS1_GFR_F18F19_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 18 and 19 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F18F19_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 18U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH18 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 18U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 18U);
#endif
#endif
  }
  if ((gfr & (1UL << 19U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH19 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 19U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 19U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH20 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH21 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F20F21_HANDLER)
#error "SPC5_EMIOS1_GFR_F20F21_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 20 and 21 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F20F21_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 20U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH20 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 20U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 20U);
#endif
#endif
  }
  if ((gfr & (1UL << 21U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH21 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 21U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 21U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH22 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH23 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F22F23_HANDLER)
#error "SPC5_EMIOS1_GFR_F22F23_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 22 and 23 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F22F23_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 22U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH22 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 22U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD7, 22U);
#endif
#endif
  }
  if ((gfr & (1UL << 23U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD5, 23U);
#elif (SPC5_PWM_USE_EMIOS1_CH23 == TRUE)
	pwm_lld_serve_channel_interrupt(&PWMD7, 23U);
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_CH24 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH25 == TRUE) || \
    (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F24F25_HANDLER)
#error "SPC5_EMIOS1_GFR_F24F25_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 24 and 25 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F24F25_HANDLER) {

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 24U)) != 0U) {
#if (SPC5_ICU_USE_EMIOS1_CH24 == TRUE)
    icu_lld_serve_interrupt(&ICUD15);
#elif (SPC5_PWM_USE_EMIOS1_CH24 == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 24U);
#elif (SPC5_PWM_USE_EMIOS1_COUNT_BUS_E == TRUE)
    pwm_lld_serve_period_interrupt(&PWMD8, 24U);
#endif
  }
  if ((gfr & (1UL << 25U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH25 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 25U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 25U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH26 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH27 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F26F27_HANDLER)
#error "SPC5_EMIOS1_GFR_F26F27_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 26 and 27 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F26F27_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 26U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH26 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 26U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 26U);
#endif
#endif
  }
  if ((gfr & (1UL << 27U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH27 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 27U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 27U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH28 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH29 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F28F29_HANDLER)
#error "SPC5_EMIOS1_GFR_F28F29_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 28 and 29 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F28F29_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 28U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH28 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 28U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 28U);
#endif
#endif
  }
  if ((gfr & (1UL << 29U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH29 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 29U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 29U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

#if (SPC5_PWM_USE_EMIOS1_CH30 == TRUE) || (SPC5_PWM_USE_EMIOS1_CH31 == TRUE)
#if !defined(SPC5_EMIOS1_GFR_F30F31_HANDLER)
#error "SPC5_EMIOS1_GFR_F30F31_HANDLER not defined"
#endif
/**
 * @brief   eMIOS1 Channels 30 and 31 interrupt handler.
 * @note    It is assumed that the various sources are only activated if the
 *          associated callback pointer is not equal to @p NULL in order to not
 *          perform an extra check in a potentially critical interrupt handler.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EMIOS1_GFR_F30F31_HANDLER) {

  IRQ_PROLOGUE();

  uint32_t gfr;

  IRQ_PROLOGUE();

  gfr = get_emios1_gfr();

  if ((gfr & (1UL << 30U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH30 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 30U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 30U);
#endif
#endif
  }
  if ((gfr & (1UL << 31U)) != 0U) {
#if (SPC5_PWM_USE_EMIOS1_CH31 == TRUE)
#if (SPC5_PWM_USE_EMIOS1_COUNT_BUS_A == TRUE)
    pwm_lld_serve_channel_interrupt(&PWMD5, 31U);
#else
	pwm_lld_serve_channel_interrupt(&PWMD8, 31U);
#endif
#endif
  }

  IRQ_EPILOGUE();
}
#endif

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/


#endif /* LLD_USE_ICU || LLD_USE_PWM */

/** @} */
