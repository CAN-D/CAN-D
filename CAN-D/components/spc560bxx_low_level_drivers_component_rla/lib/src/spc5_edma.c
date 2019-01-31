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
 * @file    spc5_edma.c
 * @brief   EDMA helper driver code for RLA components.
 *
 * @addtogroup SPC5xx_EDMA
 * @{
 */

#include "spc5_edma.h"

#if (SPC5_HAS_EDMA == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver local definitions.                                                 */
/*===========================================================================*/

static const uint8_t g0[16] = {SPC5_EDMA_GROUP0_PRIORITIES};
#if (SPC5_EDMA_NCHANNELS > 16U) || defined(__DOXYGEN__)
static const uint8_t g1[16] = {SPC5_EDMA_GROUP1_PRIORITIES};
#endif
#if (SPC5_EDMA_NCHANNELS > 32U) || defined(__DOXYGEN__)
static const uint8_t g2[16] = {SPC5_EDMA_GROUP2_PRIORITIES};
static const uint8_t g3[16] = {SPC5_EDMA_GROUP3_PRIORITIES};
#endif

#if (SPC5_EDMA_HAS_MUX == TRUE)
#if (SPC5_EDMA_NUM_OF_MUX > 1U)
static const uint8_t mux_ch_num[SPC5_EDMA_NUM_OF_MUX] = {SPC5_EDMA_MUX_CH_NUM};
#endif /* (SPC5_EDMA_NUM_OF_MUX > 1U) */
#endif /* SPC5_EDMA_HAS_MUX */

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Configurations for the various EDMA channels.
 */
static const edma_channel_config_t *channels[SPC5_EDMA_NCHANNELS];

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/**
 * @brief   EDMA (channels 0..31) error interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_ERR_FLAG_31_0_HANDLER) {
  edma_channel_t channel;
  uint32_t erl, esr = SPC5_EDMA.ESR.R;

  IRQ_PROLOGUE();

  /* Scanning for errors.*/
  channel = 0;
#if (SPC5_EDMA_NCHANNELS > 32U)
  while (((erl = SPC5_EDMA.ERL.R) != 0U) && (channel < 32U)) {
#else
  while (((erl = SPC5_EDMA.ERL.R) != 0U) && (channel < SPC5_EDMA_NCHANNELS)) {
#endif
    if ((erl & (1UL << (uint32_t)channel)) != 0U) {
      /* Error flag cleared.*/
      SPC5_EDMA.CER.R = (uint8_t)channel;

      /* If the channel is not associated then the error is simply discarded
         else the error callback is invoked.*/
      if ((channels[channel] != NULL) &&
          (channels[channel]->dma_error_func != NULL)) {
        channels[channel]->dma_error_func(channel,
                                          channels[channel]->dma_param,
                                          esr);
      }
    }
    channel++;
  }

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 0 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH0_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[0] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 0;
  channels[0]->dma_func(0, channels[0]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 1 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH1_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[1] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 1;
  channels[1]->dma_func(1, channels[1]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 2 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH2_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[2] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 2;
  channels[2]->dma_func(2, channels[2]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 3 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH3_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[3] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 3;
  channels[3]->dma_func(3, channels[3]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 4 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH4_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[4] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 4;
  channels[4]->dma_func(4, channels[4]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 5 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH5_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[5] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 5;
  channels[5]->dma_func(5, channels[5]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 6 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH6_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[6] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 6;
  channels[6]->dma_func(6, channels[6]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 7 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH7_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[7] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 7;
  channels[7]->dma_func(7, channels[7]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 8 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH8_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[8] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 8;
  channels[8]->dma_func(8, channels[8]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 9 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH9_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[9] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 9;
  channels[9]->dma_func(9, channels[9]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 10 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH10_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[10] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 10;
  channels[10]->dma_func(10, channels[10]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 11 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH11_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[11] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 11;
  channels[11]->dma_func(11, channels[11]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 12 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH12_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[12] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 12;
  channels[12]->dma_func(12, channels[12]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 13 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH13_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[13] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 13;
  channels[13]->dma_func(13, channels[13]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 14 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH14_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[14] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 14;
  channels[14]->dma_func(14, channels[14]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 15 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH15_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[15] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 15;
  channels[15]->dma_func(15, channels[15]->dma_param);

  IRQ_EPILOGUE();
}

#if (SPC5_EDMA_NCHANNELS > 16U) || defined(__DOXYGEN__)
/**
 * @brief   EDMA channel 16 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH16_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[16] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 16;
  channels[16]->dma_func(16, channels[16]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 17 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH17_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[17] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 17;
  channels[17]->dma_func(17, channels[17]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 18 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH18_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[18] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 18;
  channels[18]->dma_func(18, channels[18]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 19 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH19_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[19] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 19;
  channels[19]->dma_func(19, channels[19]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 20 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH20_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[20] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 20;
  channels[20]->dma_func(20, channels[20]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 21 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH21_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[21] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 21;
  channels[21]->dma_func(21, channels[21]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 22 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH22_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[22] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 22;
  channels[22]->dma_func(22, channels[22]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 23 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH23_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[23] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 23;
  channels[23]->dma_func(23, channels[23]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 24 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH24_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[24] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 24;
  channels[24]->dma_func(24, channels[24]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 25 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH25_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[25] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 25;
  channels[25]->dma_func(25, channels[25]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 26 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH26_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[26] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 26;
  channels[26]->dma_func(26, channels[26]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 27 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH27_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[27] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 27;
  channels[27]->dma_func(27, channels[27]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 28 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH28_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[28] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 28;
  channels[28]->dma_func(28, channels[28]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 29 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH29_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[29] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 29;
  channels[29]->dma_func(29, channels[29]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 30 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH30_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[30] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 30;
  channels[30]->dma_func(30, channels[30]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 31 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH31_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[31] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 31;
  channels[31]->dma_func(31, channels[31]->dma_param);

  IRQ_EPILOGUE();
}
#if (SPC5_EDMA_NCHANNELS > 32U) || defined(__DOXYGEN__)
/**
 * @brief   EDMA (channels 32..64) error interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_ERR_FLAG_63_32_HANDLER) {
  edma_channel_t channel;
  uint32_t erh, esr = SPC5_EDMA.ESR.R;

  IRQ_PROLOGUE();

  /* Scanning for errors.*/
  channel = 32;
  while (((erh = SPC5_EDMA.ERH.R) != 0U) && (channel < SPC5_EDMA_NCHANNELS)) {

    if ((erh & (1UL << (channel - 32U))) != 0UL) {
      /* Error flag cleared.*/
      SPC5_EDMA.CER.R = (uint8_t)channel;

      /* If the channel is not associated then the error is simply discarded
         else the error callback is invoked.*/
      if ((channels[channel] != NULL) &&
          (channels[channel]->dma_error_func != NULL)) {
        channels[channel]->dma_error_func(channel,
                                          channels[channel]->dma_param,
                                          esr);
      }
      channel++;
    }
  }

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 32 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH32_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[32] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 32;
  channels[32]->dma_func(32, channels[32]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 33 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH33_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[33] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 33;
  channels[33]->dma_func(33, channels[33]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 34 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH34_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[34] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 34;
  channels[34]->dma_func(34, channels[34]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 35 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH35_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[35] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 35;
  channels[35]->dma_func(35, channels[35]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 36 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH36_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[36] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 36;
  channels[36]->dma_func(36, channels[36]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 37 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH37_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[37] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 37;
  channels[37]->dma_func(37, channels[37]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 38 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH38_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[38] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 38;
  channels[38]->dma_func(38, channels[38]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 39 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH39_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[39] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 39;
  channels[39]->dma_func(39, channels[39]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 40 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH40_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[40] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 40;
  channels[40]->dma_func(40, channels[40]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 41 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH41_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[41] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 41;
  channels[41]->dma_func(41, channels[41]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 42 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH42_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[42] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 42;
  channels[42]->dma_func(42, channels[42]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 43 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH43_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[43] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 43;
  channels[43]->dma_func(43, channels[43]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 44 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH44_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[44] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 44;
  channels[44]->dma_func(44, channels[44]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 45 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH45_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[45] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 45;
  channels[45]->dma_func(45, channels[45]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 46 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH46_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[46] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 46;
  channels[46]->dma_func(46, channels[46]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 47 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH47_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[47] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 47;
  channels[47]->dma_func(47, channels[47]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 48 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH48_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[48] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 48;
  channels[48]->dma_func(48, channels[48]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 49 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH49_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[49] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 49;
  channels[49]->dma_func(49, channels[49]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 50 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH50_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[50] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 50;
  channels[50]->dma_func(50, channels[50]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 51 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH51_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[51] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 51;
  channels[51]->dma_func(51, channels[51]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 52 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH52_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[52] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 52;
  channels[52]->dma_func(52, channels[52]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 53 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH53_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[53] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 53;
  channels[53]->dma_func(53, channels[53]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 54 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH54_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[54] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 54;
  channels[54]->dma_func(54, channels[54]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 55 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH55_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[55] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 55;
  channels[55]->dma_func(55, channels[55]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 56 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH56_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[56] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 56;
  channels[56]->dma_func(56, channels[56]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 57 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH57_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[57] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 57;
  channels[57]->dma_func(57, channels[57]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 58 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH58_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[58] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 58;
  channels[58]->dma_func(58, channels[58]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 59 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH59_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[59] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 59;
  channels[59]->dma_func(59, channels[59]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 60 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH60_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[60] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 60;
  channels[60]->dma_func(60, channels[60]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 61 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH61_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[61] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 61;
  channels[61]->dma_func(61, channels[61]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 62 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH62_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[62] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 62;
  channels[62]->dma_func(62, channels[62]->dma_param);

  IRQ_EPILOGUE();
}

/**
 * @brief   EDMA channel 63 interrupt.
 *
 * @isr
 */
IRQ_HANDLER(SPC5_EDMA_CH63_HANDLER) {

  IRQ_PROLOGUE();

  if (channels[63] == NULL) {
    SPC5_EDMA_ERROR_HANDLER();
  }
  SPC5_EDMA.CIRQR.R = 63;
  channels[63]->dma_func(63, channels[63]->dma_param);

  IRQ_EPILOGUE();
}
#endif /* SPC5_EDMA_NCHANNELS > 32 */
#endif /* SPC5_EDMA_NCHANNELS > 16 */

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   EDMA driver initialization.
 *
 * @special
 */
void edmaInit(void) {
  uint8_t i;

  SPC5_EDMA.CR.R    = SPC5_EDMA_CR_SETTING;
  SPC5_EDMA.ERQRL.R = 0x00000000UL;
  SPC5_EDMA.EEIRL.R = 0x00000000UL;
  SPC5_EDMA.IRQRL.R = 0xFFFFFFFFUL;
  SPC5_EDMA.ERL.R =   0xFFFFFFFFUL;
#if (SPC5_EDMA_NCHANNELS > 32U)
  SPC5_EDMA.ERQRH.R = 0x00000000UL;
  SPC5_EDMA.EEIRH.R = 0x00000000UL;
  SPC5_EDMA.IRQRH.R = 0xFFFFFFFFUL;
  SPC5_EDMA.ERH.R =   0xFFFFFFFFUL;
#endif
  /* Initializing all the channels with a different priority withing the
     channels group.*/
  for (i = 0; i < 16U; i++) {
    SPC5_EDMA.CPR[i].R = g0[i];
#if (SPC5_EDMA_NCHANNELS > 16U)
    SPC5_EDMA.CPR[i + 16U].R = g1[i];
#endif
#if (SPC5_EDMA_NCHANNELS > 32U)
    SPC5_EDMA.CPR[i + 32U].R = g2[i];
    SPC5_EDMA.CPR[i + 48U].R = g3[i];
#endif
  }

  /* Error interrupt source.*/
  INTC_PSR(SPC5_EDMA_ERR_FLAG_31_0_NUMBER) = SPC5_EDMA_ERROR_IRQ_PRIO;
#if (SPC5_EDMA_NCHANNELS > 32U)
  INTC_PSR(SPC5_EDMA_ERR_FLAG_63_32_NUMBER) = SPC5_EDMA_ERROR_IRQ_PRIO;
#endif

#if defined(SPC5_EDMA_MUX_PCTL)
  /* DMA MUX PCTL setup, only if required.*/
  SPCSetPeripheralClockMode(SPC5_EDMA_MUX_PCTL, SPC5_EDMA_MUX_START_PCTL);
#endif
}

#if (SPC5_EDMA_HAS_MUX == TRUE)
/**
 * @brief   EDMA mux slot set.
 *
 * @param[in] ccfg      channel configuration
 *
 * @notapi
 */
static void edmaSetMuxSlot(const edma_channel_config_t *ccfg) {
#if (SPC5_EDMA_NUM_OF_MUX > 1U)
  uint8_t i, chcfg = (uint8_t)ccfg->dma_channel;
  for(i = 0; i < ccfg->dma_mux; i++) {
    chcfg = chcfg - mux_ch_num[i];
  }
  /* Programming the MUX.*/
  /*lint -e9033*/
  SPC5_DMAMUX(ccfg->dma_mux).CHCONFIG[chcfg].R = (uint8_t)(0x80U |
                                                           ccfg->dma_periph);
  /*lint +e9033*/
#else
  /* Programming the MUX.*/
  SPC5_DMAMUX.CHCONFIG[ccfg->dma_channel].R = (uint8_t)(0x80U |
                                                        ccfg->dma_periph);
#endif /* (SPC5_EDMA_NUM_OF_MUX > 1U) */
}
#endif /* SPC5_EDMA_HAS_MUX */

/**
 * @brief   EDMA channel allocation.
 *
 * @param[in] ccfg      channel configuration
 * @return              The channel number.
 * @retval EDMA_ERROR   if the channel cannot be allocated.
 *
 * @special
 */
edma_channel_t edmaChannelAllocate(const edma_channel_config_t *ccfg) {

  /* If the channel is already taken then an error is returned.*/
  if (channels[ccfg->dma_channel] != NULL) {
    return EDMA_ERROR;                          /* Already taken.           */
  }

#if (SPC5_EDMA_HAS_MUX == TRUE)
  edmaSetMuxSlot(ccfg);
#endif /* SPC5_EDMA_HAS_MUX */

  /* Associating the configuration to the channel.*/
  channels[ccfg->dma_channel] = ccfg;

  /* If an error callback is defined then the error interrupt source is
     enabled for the channel.*/
  if (ccfg->dma_error_func != NULL) {
    SPC5_EDMA.SEEIR.R = (uint8_t)ccfg->dma_channel;
  }

  /* Setting up IRQ priority for the selected channel.*/
  if (ccfg->dma_channel < 16U){
  /* Method of accessing PSR DMA channels by incrementing channel index in the INTC_PSR
     macro not comply with MISRA C because it involves a cast on a composite expression.*/
    /*lint -e9032 -e9033*/
    INTC_PSR(SPC5_EDMA_CH0_NUMBER + ccfg->dma_channel) = ccfg->dma_irq_prio;
  }
#if (SPC5_EDMA_NCHANNELS > 16U)
  else if ((ccfg->dma_channel > 15U) && (ccfg->dma_channel < 32U)){
    INTC_PSR(SPC5_EDMA_CH16_NUMBER + ccfg->dma_channel - 16U) = ccfg->dma_irq_prio;
  }
#endif
#if (SPC5_EDMA_NCHANNELS > 32U)
  else if (ccfg->dma_channel > 31U){
	INTC_PSR(SPC5_EDMA_CH32_NUMBER + ccfg->dma_channel - 32U) = ccfg->dma_irq_prio;
    /*lint +e9032 +e9033*/
  }
#endif
  else{
	/*required by MISRA*/
  }
  return ccfg->dma_channel;
}

#if (SPC5_EDMA_HAS_MUX == TRUE)
/**
 * @brief   EDMA mux slot reset.
 *
 * @param[in] ccfg      channel configuration
 *
 * @notapi
 */
static void edmaResetMuxSlot(const edma_channel_config_t *ccfg) {
#if (SPC5_EDMA_NUM_OF_MUX > 1U)
  uint8_t i, chcfg = (uint8_t)ccfg->dma_channel;
  for(i = 0; i < ccfg->dma_mux; i++) {
    chcfg =  chcfg - mux_ch_num[i];
  }
  /* Disabling the MUX slot.*/
  /*lint -e9033*/
  SPC5_DMAMUX(ccfg->dma_mux).CHCONFIG[chcfg].R = 0;
  /*lint +e9033*/
#else
  /* Disabling the MUX slot.*/
  SPC5_DMAMUX.CHCONFIG[ccfg->dma_channel].R = 0;
#endif /* (SPC5_EDMA_NUM_OF_MUX > 1U) */
}
#endif /* SPC5_EDMA_HAS_MUX */

/**
 * @brief   EDMA channel release.
 *
 * @param[in] ccfg      channel configuration
 *
 * @special
 */
void edmaChannelRelease(const edma_channel_config_t *ccfg) {

  /* Enforcing a stop.*/
  edmaChannelStop(ccfg->dma_channel);

#if (SPC5_EDMA_HAS_MUX == TRUE)
  edmaResetMuxSlot(ccfg);
#endif /* SPC5_EDMA_HAS_MUX */

  /* Clearing ISR sources for the channel.*/
  SPC5_EDMA.CIRQR.R = (uint8_t)(ccfg->dma_channel);
  SPC5_EDMA.CEEIR.R = (uint8_t)(ccfg->dma_channel);
  SPC5_EDMA.CER.R   = (uint8_t)(ccfg->dma_channel);

  /* The channels is flagged as available.*/
  channels[ccfg->dma_channel] = NULL;
}

#endif /* SPC5_HAS_EDMA */

/** @} */
