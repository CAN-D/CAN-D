/*
 SPC5 RLA - Copyright (C) 2018 STMicroelectronics

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
 * @file    lin_lld.c
 * @brief   SPC5xx LIN low level driver code.
 *
 * @addtogroup LIN
 * @{
 */

#include "lin_lld.h"

#if (LLD_USE_LIN == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/**
 * @brief   LIINFlex-0 lin driver identifier.
 */
#if (SPC5_LINFLEX0_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD1;
#endif

/**
 * @brief   LIINFlex-1 lin driver identifier.
 */
#if (SPC5_LINFLEX1_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD2;
#endif

/**
 * @brief   LIINFlex-2 lin driver identifier.
 */
#if (SPC5_LINFLEX2_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD3;
#endif

/**
 * @brief   LIINFlex-3 lin driver identifier.
 */
#if (SPC5_LINFLEX3_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD4;
#endif

/**
 * @brief   LIINFlex-4 lin driver identifier.
 */
#if (SPC5_LINFLEX4_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD5;
#endif

/**
 * @brief   LIINFlex-5 lin driver identifier.
 */
#if (SPC5_LINFLEX5_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD6;
#endif

/**
 * @brief   LIINFlex-6 lin driver identifier.
 */
#if (SPC5_LINFLEX6_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD7;
#endif

/**
 * @brief   LIINFlex-7 lin driver identifier.
 */
#if (SPC5_LINFLEX7_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD8;
#endif

/**
 * @brief   LIINFlex-8 lin driver identifier.
 */
#if (SPC5_LINFLEX8_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD9;
#endif

/**
 * @brief   LIINFlex-9 lin driver identifier.
 */
#if (SPC5_LINFLEX9_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD10;
#endif

/**
 * @brief   LIINFlex-10 lin driver identifier.
 */
#if (SPC5_LINFLEX10_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD11;
#endif

/**
 * @brief   LIINFlex-11 lin driver identifier.
 */
#if (SPC5_LINFLEX11_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD12;
#endif

/**
 * @brief   LIINFlex-12 lin driver identifier.
 */
#if (SPC5_LINFLEX12_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD13;
#endif

/**
 * @brief   LIINFlex-13 lin driver identifier.
 */
#if (SPC5_LINFLEX13_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD14;
#endif

/**
 * @brief   LIINFlex-14 lin driver identifier.
 */
#if (SPC5_LINFLEX14_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD15;
#endif

/**
 * @brief   LIINFlex-15 lin driver identifier.
 */
#if (SPC5_LINFLEX15_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD16;
#endif

/**
 * @brief   LIINFlex-16 lin driver identifier.
 */
#if (SPC5_LINFLEX16_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD17;
#endif

/**
 * @brief   LIINFlex-17 lin driver identifier.
 */
#if (SPC5_LINFLEX17_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD18;
#endif

/**
 * @brief   LIINFlex-18 lin driver identifier.
 */
#if (SPC5_LINFLEX18_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD19;
#endif

/**
 * @brief   LIINFlex-19 lin driver identifier.
 */
#if (SPC5_LINFLEX19_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD20;
#endif

/**
 * @brief   LIINFlex-20 lin driver identifier.
 */
#if (SPC5_LINFLEX20_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD21;
#endif

/**
 * @brief   LIINFlex-21 lin driver identifier.
 */
#if (SPC5_LINFLEX21_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD22;
#endif

/**
 * @brief   LIINFlex-22 lin driver identifier.
 */
#if (SPC5_LINFLEX22_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD23;
#endif

/**
 * @brief   LIINFlex-23 lin driver identifier.
 */
#if (SPC5_LINFLEX23_SETTING == SPC5_LINFLEX_MODE_LIN) || defined(__DOXYGEN__)
LinDriver LD24;
#endif

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver default configuration.
 */

static const LinConfig default_config = {
		LIN_DEFAULT_BAUDRATE,
        LIN_MODE_MASTER,
		SPC5_LIN_API_MODE_SYNCHRONOUS,
		NULL,
		NULL,
		NULL,
		0
};

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static void spc5_linflex_set_filter(LinDriver *ldp, uint32_t filter, LinFilter *filter_cfg)
{
	uint32_t ifcrx_off;
	uint16_t ifer;
	uint32_t *pFilter;
	uint32_t p;

	ifcrx_off = (((filter * 4U) + SPC5_LINFLEX_IFCR0_OFFSET) / 4U);
	p = (uint32_t) (ldp->linflexlp);

	p += ifcrx_off * sizeof (uint32_t);
	pFilter = (uint32_t *)p;

	ifer = (uint16_t)(ldp->linflexlp->IFER.R & 0xFFFFU);
	ldp->linflexlp->IFER.R = (uint16_t) (ifer | (((uint32_t)1U << filter)));	/* Enable #Filter */
	ldp->linflexlp->IFMR.R = (uint16_t)filter_cfg->mode;			/* All filters are in identifier list mode */

	*pFilter = ((((uint32_t)filter_cfg->datasize - 1U) & SPC5_BIDR_DFL_MASK) << 10U) |
			   ((uint32_t)filter_cfg->direction << 9U) |
			   ((uint32_t)filter_cfg->ccs << 8U) |
			   ((uint32_t)filter_cfg->value & SPC5_BIDR_ID_MASK);
}

/**
 * @brief   LINFlex initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 */
static void spc5_linflex_start(LinDriver *ldp) {
  uint32_t i;
  uint32_t div;

  volatile struct spc5_linflexl *linflexlp = ldp->linflexlp;

  linflexlp->LINCR1.B.SLEEP = 0;                /* exit sleep mode */
  /* Enters the configuration mode.*/
  linflexlp->LINCR1.B.INIT = 1;                      /* Enter in Initialization Mode       */

  while (0x1000U != (linflexlp->LINSR.R & 0xF000U)) {}

  linflexlp->LINCR1.B.MME = (uint8_t)ldp->config->mode;  /* Select Master/Slave mode */

  linflexlp->LINCR1.B.MBL = 3U;		            /* 13-bit break */
  linflexlp->LINCR1.B.LASE = 0;                 /* Auto synchronization disabled */
  linflexlp->LINCR2.B.IOBE = 0;                 /* Bit Error does not reset LIN state machine */

  linflexlp->LINTCSR.B.MODE = 0; /* LIN timeout mode for 8-bit counter */
  linflexlp->LINTCSR.B.IOT  = 0; /* LIN state machine does not reset to Idle on timeout */
  linflexlp->LINTCSR.B.TOCE = 0; /* Time-out counter enable - OCF flag is set if an output compare event occurs */

  linflexlp->LINSR.R = 0xFFFF;        /* Clearing LINSR register. */
  linflexlp->LINIER.R = 0;            /* LIN Interrupts disabled.     */

  /* Set the LIN baud Rate */
  div = ldp->clock / (ldp->config->speed);
  linflexlp->LINFBRR.R = (uint16_t)(div & 15U); /* Fractional divider.      */
  linflexlp->LINIBRR.R = (uint16_t)(div >> 4);  /* Integer divider.         */

  if ((ldp->config->mode == LIN_MODE_SLAVE) && (ldp->config->filters != NULL)) {
    for (i = 0; i < LIN_NUM_FILTERS; i++) {
      LinFilter *p = ldp->config->filters[i];
      if (p != NULL) {
        spc5_linflex_set_filter(ldp, i, p);
	  }
    }
  }

#if 0
  if (ldp->config->loopBack)
	  /* Loop Back mode. 0 - Disabled, 1 - Enabled. */
	  linflexlp->LINCR1.B.LBKM = 1;
#endif

  if (ldp->config->tx_end_cb != NULL) {
    /* Enable Header transmit interrupt */
    ldp->linflexlp->LINIER.B.HRIE = 1;
  }

  if (ldp->config->rx_end_cb != NULL) {
    /* Enable receive interrupt */
    ldp->linflexlp->LINIER.B.DRIE = 1;
  }

  /* Leaves the configuration mode.*/
  linflexlp->LINCR1.B.INIT = 0;  /* Enter in normal mode */
}

/**
 * @brief   LINFlex de-initialization.
 * @details This function must be invoked with interrupts disabled.
 *
 * @param[in] linflexlp  pointer to a LINFlex I/O block
 */
static void spc5_linflex_stop(volatile struct spc5_linflexl *linflexlp) {

  /* Enters the configuration mode.*/
  linflexlp->LINCR1.R = 1;                      /* INIT bit.                */

  while (0x1000U != (linflexlp->LINSR.R & 0xF000U)) {}
	
  /* Resets the LINFlex registers.*/
  linflexlp->LINIBRR.R = 0;       /* LIN Integer Baud Rate register         */
  linflexlp->LINFBRR.R = 0;       /* LIN Fractional Baud Rate register      */
  linflexlp->LINSR.R   = 0xFFFF;  /* Clearing LINSR register.               */
  linflexlp->LINCR2.R  = 0;       /* Clear LIN control register 2.          */

  linflexlp->LINIER.R = 0;        /* Disable LIN Interrupts                 */
  
  /* Leaves the configuration mode.*/
  linflexlp->LINCR1.B.INIT = 0;   /* Enter in normal mode                   */
}

/**
 * @brief   Common TXI IRQ handler.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 */
static void spc5xx_lin_txi_interrupt(uint32_t ildp) {
  uint32_t status;
  LinDriver *ldp = (LinDriver *) ildp;
  volatile struct spc5_linflexl *linflexlp = ldp->linflexlp;

  status = linflexlp->LINSR.R;

  if ((status & SPC5_LINSR_HRF) != 0U) {

    /* Slave transmit mode */

    if (ldp->config->tx_end_cb != NULL) {

      uint16_t len;
      uint8_t tx_buf[LIN_DATA_LEN];

      /* Call the related callback.
       * tx_buf will be filled by this callback
       */
      len = (uint16_t)ldp->config->tx_end_cb(ldp,
    		  linflexlp->BIDR.B.ID,
			  tx_buf,
			  (uint16_t)linflexlp->BIDR.B.DFL + 1U);

      if (len != 0U) {
        /* Set TX Buffer */
        uint8_t *pbuf = &tx_buf[--len];

        switch (len) {
        case 7:
          linflexlp->BDRM.B.DATA7 = *pbuf--;
          /* no break */
        case 6:
          linflexlp->BDRM.B.DATA6 = *pbuf--;
          /* no break */
        case 5:
          linflexlp->BDRM.B.DATA5 = *pbuf--;
          /* no break */
        case 4:
          linflexlp->BDRM.B.DATA4 = *pbuf--;
          /* no break */
        case 3:
          linflexlp->BDRL.B.DATA3 = *pbuf--;
          /* no break */
        case 2:
          linflexlp->BDRL.B.DATA2 = *pbuf--;
          /* no break */
        case 1:
          linflexlp->BDRL.B.DATA1 = *pbuf--;
          /* no break */
        case 0:
          linflexlp->BDRL.B.DATA0 = *pbuf;
          /* no break */
        default:
          /* nothing to do */
          break;
        }

        /* Trigger Data transmission*/
        linflexlp->LINCR2.B.DTRQ = 1;
      }
    }

    /* Acknowledge header received interrupt */
    linflexlp->LINSR.B.HRF = 1;

  } else {

    /* Master transmit mode */

    /* Acknowledge transmit interrupt */
    linflexlp->LINSR.B.DTF = 1;

    /* Disable transmit interrupt */
    linflexlp->LINIER.B.DTIE = 0;

    /* Call the related callback.*/
    if (ldp->config->tx_end_cb != NULL) {
      /* Ignoring return value */
      (void)ldp->config->tx_end_cb(ldp, ldp->tx_id_msg, ldp->tx_buf, ldp->tx_len);
    }

    SPC5_LIN_TX_DONE(ldp);
  }
}

/**
 * @brief   Common RXI IRQ handler.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 */
static void spc5xx_lin_rxi_interrupt(uint32_t ildp) {
  LinDriver *ldp = (LinDriver *) ildp;
  volatile struct spc5_linflexl *linflexlp = ldp->linflexlp;
  uint8_t *pbuf;
  uint16_t len;
  uint8_t id_msg;
  uint8_t rx_buf[LIN_DATA_LEN];

  /* Acknowledge receive interrupt */
  linflexlp->LINSR.B.DRF = 1;

  /* Retrieve message id */
  id_msg = linflexlp->BIDR.B.ID;

  /* Retrieve message data length */
  len = (uint16_t)linflexlp->BIDR.B.DFL + 1U;

  if (ldp->config->mode == LIN_MODE_MASTER) {

	 /* Master receive */

    /* Disable receive interrupt */
    linflexlp->LINIER.B.DRIE = 0;

    /* Check the size of the data buffer */
    if (ldp->rx_len < len) {
	    len = ldp->rx_len;
    }

    /* Set returned data length */
    ldp->rx_len = len;

    /* Set RX Buffer */
    pbuf = &ldp->rx_buf[--len];

  } else {

    /* Slave receive */

    /* Set RX Buffer */
    pbuf = &rx_buf[--len];
  }

  /* Read the data */
  switch (len) {
  case 7:
    *pbuf-- = (uint8_t)linflexlp->BDRM.B.DATA7;
    /* no break */
  case 6:
    *pbuf-- = (uint8_t)linflexlp->BDRM.B.DATA6;
    /* no break */
  case 5:
    *pbuf-- = (uint8_t)linflexlp->BDRM.B.DATA5;
    /* no break */
  case 4:
    *pbuf-- = (uint8_t)linflexlp->BDRM.B.DATA4;
    /* no break */
  case 3:
    *pbuf-- = (uint8_t)linflexlp->BDRL.B.DATA3;
    /* no break */
  case 2:
    *pbuf-- = (uint8_t)linflexlp->BDRL.B.DATA2;
    /* no break */
  case 1:
    *pbuf-- = (uint8_t)linflexlp->BDRL.B.DATA1;
    /* no break */
  case 0:
    *pbuf = (uint8_t)linflexlp->BDRL.B.DATA0;
    /* no break */
  default:
    /* Nothing to do */
    break;
  }

  /* Call the related callback.*/
  if (ldp->config->rx_end_cb != NULL) {
    /* Ignoring return value */
    (void)ldp->config->rx_end_cb(ldp, id_msg, pbuf, len + 1U);
  }

  SPC5_LIN_RX_DONE(ldp);
}

/**
 * @brief   Common ERR IRQ handler.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 */
static void spc5xx_lin_err_interrupt(uint32_t ildp) {
  LinDriver *ldp = (LinDriver *) ildp;

  (void)ldp;

}

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level lin driver initialization.
 *
 * @init
 */
void lin_lld_init(void) {

#if (SPC5_LINFLEX0_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD1.linflexlp = &SPC5_LINFLEX0L;
  LD1.linflexhp = &SPC5_LINFLEX0H;
  LD1.clock = SPC5_LINFLEX0_CLK;
  LinflexD1.device = (uint32_t)&LD1;
  LinflexD1.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD1.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD1.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX0_SETTING */

#if (SPC5_LINFLEX1_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD2.linflexlp = &SPC5_LINFLEX1L;
  LD2.linflexhp = &SPC5_LINFLEX1H;
  LD2.clock = SPC5_LINFLEX1_CLK;
  LinflexD2.device = (uint32_t)&LD2;
  LinflexD2.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD2.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD2.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX1_SETTING */

#if (SPC5_LINFLEX2_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD3.linflexlp = &SPC5_LINFLEX2L;
  LD3.linflexhp = &SPC5_LINFLEX2H;
  LD3.clock = SPC5_LINFLEX2_CLK;
  LinflexD3.device = (uint32_t)&LD3;
  LinflexD3.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD3.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD3.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX2_SETTING */

#if (SPC5_LINFLEX3_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD4.linflexlp = &SPC5_LINFLEX3L;
  LD4.linflexhp = &SPC5_LINFLEX3H;
  LD4.clock = SPC5_LINFLEX3_CLK;
  LinflexD4.device = (uint32_t)&LD4;
  LinflexD4.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD4.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD4.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX3_SETTING */

#if (SPC5_LINFLEX4_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD5.linflexlp = &SPC5_LINFLEX4L;
  LD5.linflexhp = &SPC5_LINFLEX4H;
  LD5.clock = SPC5_LINFLEX4_CLK;
  LinflexD5.device = (uint32_t)&LD5;
  LinflexD5.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD5.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD5.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX4_SETTING */

#if (SPC5_LINFLEX5_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD6.linflexlp = &SPC5_LINFLEX5L;
  LD6.linflexhp = &SPC5_LINFLEX5H;
  LD6.clock = SPC5_LINFLEX5_CLK;
  LinflexD6.device = (uint32_t)&LD6;
  LinflexD6.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD6.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD6.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX5_SETTING */

#if (SPC5_LINFLEX6_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD7.linflexlp = &SPC5_LINFLEX6L;
  LD7.linflexhp = &SPC5_LINFLEX6H;
  LD7.clock = SPC5_LINFLEX6_CLK;
  LinflexD7.device = (uint32_t)&LD7;
  LinflexD7.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD7.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD7.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX6_SETTING */

#if (SPC5_LINFLEX7_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD8.linflexlp = &SPC5_LINFLEX7L;
  LD8.linflexhp = &SPC5_LINFLEX7H;
  LD8.clock = SPC5_LINFLEX7_CLK;
  LinflexD8.device = (uint32_t)&LD8;
  LinflexD8.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD8.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD8.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX7_SETTING */

#if (SPC5_LINFLEX8_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD9.linflexlp = &SPC5_LINFLEX8L;
  LD9.linflexhp = &SPC5_LINFLEX8H;
  LD9.clock = SPC5_LINFLEX8_CLK;
  LinflexD9.device = (uint32_t)&LD9;
  LinflexD9.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD9.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD9.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX8_SETTING */

#if (SPC5_LINFLEX9_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD10.linflexlp = &SPC5_LINFLEX9L;
  LD10.linflexhp = &SPC5_LINFLEX9H;
  LD10.clock = SPC5_LINFLEX9_CLK;
  LinflexD10.device = (uint32_t)&LD10;
  LinflexD10.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD10.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD10.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX9_SETTING */

#if (SPC5_LINFLEX10_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD11.linflexlp = &SPC5_LINFLEX10L;
  LD11.linflexhp = &SPC5_LINFLEX10H;
  LD11.clock = SPC5_LINFLEX10_CLK;
  LinflexD11.device = (uint32_t)&LD11;
  LinflexD11.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD11.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD11.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX10_SETTING */

#if (SPC5_LINFLEX11_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD12.linflexlp = &SPC5_LINFLEX11L;
  LD12.linflexhp = &SPC5_LINFLEX11H;
  LD12.clock = SPC5_LINFLEX11_CLK;
  LinflexD12.device = (uint32_t)&LD12;
  LinflexD12.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD12.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD12.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX11_SETTING */

#if (SPC5_LINFLEX12_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD13.linflexlp = &SPC5_LINFLEX12L;
  LD13.linflexhp = &SPC5_LINFLEX12H;
  LD13.clock = SPC5_LINFLEX12_CLK;
  LinflexD13.device = (uint32_t)&LD13;
  LinflexD13.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD13.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD13.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX12_SETTING */

#if (SPC5_LINFLEX13_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD14.linflexlp = &SPC5_LINFLEX13L;
  LD14.linflexhp = &SPC5_LINFLEX13H;
  LD14.clock = SPC5_LINFLEX13_CLK;
  LinflexD14.device = (uint32_t)&LD14;
  LinflexD14.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD14.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD14.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX13_SETTING */

#if (SPC5_LINFLEX14_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD15.linflexlp = &SPC5_LINFLEX14L;
  LD15.linflexhp = &SPC5_LINFLEX14H;
  LD15.clock = SPC5_LINFLEX14_CLK;
  LinflexD15.device = (uint32_t)&LD15;
  LinflexD15.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD15.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD15.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX14_SETTING */

#if (SPC5_LINFLEX15_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD16.linflexlp = &SPC5_LINFLEX15L;
  LD16.linflexhp = &SPC5_LINFLEX15H;
  LD16.clock = SPC5_LINFLEX15_CLK;
  LinflexD16.device = (uint32_t)&LD16;
  LinflexD16.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD16.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD16.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX15_SETTING */

#if (SPC5_LINFLEX16_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD17.linflexlp = &SPC5_LINFLEX16L;
  LD17.linflexhp = &SPC5_LINFLEX16H;
  LD17.clock = SPC5_LINFLEX16_CLK;
  LinflexD17.device = (uint32_t)&LD17;
  LinflexD17.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD17.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD17.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX16_SETTING */

#if (SPC5_LINFLEX17_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD18.linflexlp = &SPC5_LINFLEX17L;
  LD18.linflexhp = &SPC5_LINFLEX17H;
  LD18.clock = SPC5_LINFLEX17_CLK;
  LinflexD18.device = (uint32_t)&LD18;
  LinflexD18.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD18.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD18.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX17_SETTING */

#if (SPC5_LINFLEX18_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD19.linflexlp = &SPC5_LINFLEX18L;
  LD19.linflexhp = &SPC5_LINFLEX18H;
  LD19.clock = SPC5_LINFLEX18_CLK;
  LinflexD19.device = (uint32_t)&LD19;
  LinflexD19.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD19.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD19.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX18_SETTING */

#if (SPC5_LINFLEX19_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD20.linflexlp = &SPC5_LINFLEX19L;
  LD20.linflexhp = &SPC5_LINFLEX19H;
  LD20.clock = SPC5_LINFLEX19_CLK;
  LinflexD20.device = (uint32_t)&LD20;
  LinflexD20.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD20.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD20.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX19_SETTING */

#if (SPC5_LINFLEX20_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD21.linflexlp = &SPC5_LINFLEX20L;
  LD21.linflexhp = &SPC5_LINFLEX20H;
  LD21.clock = SPC5_LINFLEX20_CLK;
  LinflexD21.device = (uint32_t)&LD21;
  LinflexD21.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD21.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD21.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX20_SETTING */

#if (SPC5_LINFLEX21_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD22.linflexlp = &SPC5_LINFLEX21L;
  LD22.linflexhp = &SPC5_LINFLEX21H;
  LD22.clock = SPC5_LINFLEX21_CLK;
  LinflexD22.device = (uint32_t)&LD22;
  LinflexD22.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD22.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD22.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX21_SETTING */

#if (SPC5_LINFLEX22_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD23.linflexlp = &SPC5_LINFLEX22L;
  LD23.linflexhp = &SPC5_LINFLEX22H;
  LD23.clock = SPC5_LINFLEX22_CLK;
  LinflexD23.device = (uint32_t)&LD23;
  LinflexD23.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD23.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD23.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX22_SETTING */

#if (SPC5_LINFLEX23_SETTING == SPC5_LINFLEX_MODE_LIN)
  LD24.linflexlp = &SPC5_LINFLEX23L;
  LD24.linflexhp = &SPC5_LINFLEX23H;
  LD24.clock = SPC5_LINFLEX23_CLK;
  LinflexD24.device = (uint32_t)&LD24;
  LinflexD24.rxi_lincallback = spc5xx_lin_rxi_interrupt;
  LinflexD24.txi_lincallback = spc5xx_lin_txi_interrupt;
  LinflexD24.err_lincallback = spc5xx_lin_err_interrupt;
#endif /* SPC5_LINFLEX23_SETTING */

  linflex_lld_init();
}

/**
 * @brief   Low level lin driver configuration and start.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 * @param[in] config    the architecture-dependent lin driver configuration.
 *                      If this parameter is set to @p NULL then a default
 *                      configuration is used.
 *
 * @api
 */
void lin_lld_start(LinDriver *ldp, const LinConfig *config) {

  if (config == NULL) {
    ldp->config = &default_config;
  } else {
    ldp->config = config;
  }
#if (SPC5_LINFLEX0_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD1 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX0_PCTL,
    SPC5_LINFLEX0_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX1_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD2 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX1_PCTL,
    SPC5_LINFLEX1_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX2_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD3 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX2_PCTL,
    SPC5_LINFLEX2_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX3_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD4 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX3_PCTL,
    SPC5_LINFLEX3_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX4_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD5 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX4_PCTL,
    SPC5_LINFLEX4_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX5_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD6 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX5_PCTL,
    SPC5_LINFLEX5_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX6_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD7 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX6_PCTL,
    SPC5_LINFLEX6_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX7_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD8 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX7_PCTL,
    SPC5_LINFLEX7_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX8_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD9 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX8_PCTL,
    SPC5_LINFLEX8_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX9_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD10 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX9_PCTL,
    SPC5_LINFLEX9_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX10_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD11 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX10_PCTL,
    SPC5_LINFLEX10_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX11_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD12 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX11_PCTL,
    SPC5_LINFLEX11_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX12_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD13 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX12_PCTL,
    SPC5_LINFLEX12_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX13_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD14 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX13_PCTL,
    SPC5_LINFLEX13_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX14_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD15 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX14_PCTL,
    SPC5_LINFLEX14_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX15_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD16 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX15_PCTL,
    SPC5_LINFLEX15_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX16_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD17 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX16_PCTL,
    SPC5_LINFLEX16_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX17_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD18 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX17_PCTL,
    SPC5_LINFLEX17_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX18_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD19 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX18_PCTL,
    SPC5_LINFLEX18_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX19_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD20 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX19_PCTL,
    SPC5_LINFLEX19_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX20_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD21 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX20_PCTL,
    SPC5_LINFLEX20_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX21_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD22 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX21_PCTL,
    SPC5_LINFLEX21_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX22_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD23 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX22_PCTL,
    SPC5_LINFLEX22_START_PCTL);
  }
#endif

#if (SPC5_LINFLEX23_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD24 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX23_PCTL,
    SPC5_LINFLEX23_START_PCTL);
  }
#endif

  spc5_linflex_start(ldp);
}

/**
 * @brief   Low level lin driver stop.
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 *
 * @api
 */
void lin_lld_stop(LinDriver *ldp) {

  spc5_linflex_stop(ldp->linflexlp);

#if (SPC5_LINFLEX0_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD1 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX0_PCTL,
    SPC5_LINFLEX0_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX1_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD2 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX1_PCTL,
    SPC5_LINFLEX1_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX2_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD3 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX2_PCTL,
    SPC5_LINFLEX2_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX3_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD4 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX3_PCTL,
    SPC5_LINFLEX3_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX4_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD5 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX4_PCTL,
    SPC5_LINFLEX4_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX5_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD6 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX5_PCTL,
    SPC5_LINFLEX5_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX6_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD7 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX6_PCTL,
    SPC5_LINFLEX6_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX7_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD8 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX7_PCTL,
    SPC5_LINFLEX7_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX8_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD9 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX8_PCTL,
    SPC5_LINFLEX8_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX9_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD10 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX9_PCTL,
    SPC5_LINFLEX9_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX10_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD11 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX10_PCTL,
    SPC5_LINFLEX10_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX11_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD12 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX11_PCTL,
    SPC5_LINFLEX11_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX12_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD13 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX12_PCTL,
    SPC5_LINFLEX12_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX13_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD14 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX13_PCTL,
    SPC5_LINFLEX13_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX14_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD15 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX14_PCTL,
    SPC5_LINFLEX14_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX15_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD16 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX15_PCTL,
    SPC5_LINFLEX15_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX16_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD17 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX16_PCTL,
    SPC5_LINFLEX16_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX17_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD18 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX17_PCTL,
    SPC5_LINFLEX17_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX18_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD19 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX18_PCTL,
    SPC5_LINFLEX18_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX19_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD20 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX19_PCTL,
    SPC5_LINFLEX19_STOP_PCTL);
    return;
  }
#endif

#if (SPC5_LINFLEX20_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD21 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX20_PCTL,
    SPC5_LINFLEX20_STOP_PCTL);
    return;
  }

#endif

#if (SPC5_LINFLEX21_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD22 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX21_PCTL,
    SPC5_LINFLEX21_STOP_PCTL);
    return;
  }

#endif

#if (SPC5_LINFLEX22_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD23 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX22_PCTL,
    SPC5_LINFLEX22_STOP_PCTL);
    return;
  }

#endif

#if (SPC5_LINFLEX23_SETTING == SPC5_LINFLEX_MODE_LIN)
  if (&LD24 == ldp) {
    SPCSetPeripheralClockMode(SPC5_LINFLEX23_PCTL,
    SPC5_LINFLEX23_STOP_PCTL);
    return;
  }

#endif

}

static void lin_master_transmit(LinDriver *ldp, uint8_t idMessage, uint8_t *buffer, uint16_t msg_len) {
  volatile struct spc5_linflexl *linflexlp = ldp->linflexlp;
  uint8_t *pbuf;

  if ((msg_len == 0U) || (msg_len > 8U)) {
	  return;
  }

  SPC5_LIN_TX_IN_PROGRESS(ldp);

  /* Save message parameters */
  ldp->tx_id_msg = idMessage;
  ldp->tx_buf = buffer;
  ldp->tx_len = msg_len;

  /* Decrement length */
  msg_len--;

  /* Set Header */
  linflexlp->BIDR.R = 0;
  linflexlp->BIDR.B.ID = idMessage & SPC5_BIDR_ID_MASK;
  linflexlp->BIDR.B.DFL = (uint8_t)(((uint32_t)msg_len) & SPC5_BIDR_DFL_MASK); /* Configure DFL in BIDR */
  linflexlp->BIDR.B.CCS = 0;
  linflexlp->BIDR.B.DIR = (uint8_t)LIN_DIRECTION_TRANSMIT;

  /* Fill TX Buffer */
  pbuf = &buffer[msg_len];

  switch (msg_len) {
  case 7:
    linflexlp->BDRM.B.DATA7 = *pbuf--;
    /* no break */
  case 6:
    linflexlp->BDRM.B.DATA6 = *pbuf--;
    /* no break */
  case 5:
    linflexlp->BDRM.B.DATA5 = *pbuf--;
    /* no break */
  case 4:
    linflexlp->BDRM.B.DATA4 = *pbuf--;
    /* no break */
  case 3:
    linflexlp->BDRL.B.DATA3 = *pbuf--;
    /* no break */
  case 2:
    linflexlp->BDRL.B.DATA2 = *pbuf--;
    /* no break */
  case 1:
    linflexlp->BDRL.B.DATA1 = *pbuf--;
    /* no break */
  case 0:
    linflexlp->BDRL.B.DATA0 = *pbuf--;
    /* no break */
  default:
	/* Nothing to do */
    break;
  }

  /* Enable transmit interrupt */
  linflexlp->LINIER.B.DTIE = 1;

  /* Trigger Header transmission*/
  linflexlp->LINCR2.B.HTRQ = 1;

  SPC5_LIN_WAIT_FOR_TX_COMPLETION(ldp);
}

static uint16_t lin_master_receive(LinDriver *ldp, uint8_t idMessage, uint8_t *buffer, uint16_t msg_len) {
  volatile struct spc5_linflexl *linflexlp = ldp->linflexlp;

  if ((msg_len == 0U) || (msg_len > 8U)) {
	  return 0;
  }

  SPC5_LIN_RX_IN_PROGRESS(ldp);

  /* Prepare buffer for receiving data */
  ldp->rx_buf = buffer;
  ldp->rx_len = msg_len;

  /* Prepare message header */
  linflexlp->BIDR.R = 0;
  linflexlp->BIDR.B.ID  = idMessage & SPC5_BIDR_ID_MASK;
  linflexlp->BIDR.B.DFL = (uint8_t)(((uint32_t)msg_len - 1U) & SPC5_BIDR_DFL_MASK); /* Configure DFL in BIDR */
  linflexlp->BIDR.B.CCS = 0;
  linflexlp->BIDR.B.DIR = (uint8_t)LIN_DIRECTION_RECEIVE;

  /* Enable Data Receive interrupt */
  linflexlp->LINIER.B.DRIE = 1;

  /* Trigger Header transmission*/
  linflexlp->LINCR2.B.HTRQ = 1;

  SPC5_LIN_WAIT_FOR_RX_COMPLETION(ldp);

  /* rx_len could have been changed at interrupt time */
  return ldp->rx_len;
}


/**
 * @brief   Low level lin driver transmit for LIN device configured as Master
 *
 * @param[in] ldp       pointer to a @p LinDriver object
 * @param[in] idMessage Id Message for the buffer to transmit.
 * @param[in] buffer    data buffer to transmit
 * @param[in] msg_len   number of bytes to transmit
 *
 * @api
 */
void lin_lld_transmit(LinDriver *ldp, uint8_t idMessage, uint8_t *buffer, uint16_t msg_len) {
  if (ldp->config->mode == LIN_MODE_MASTER) {
    lin_master_transmit(ldp, idMessage, buffer, msg_len);
  }
}


/**
 * @brief   Low level lin driver receive for LIN device configured as Master
 *
 * @param[in]  ldp       pointer to a @p LinDriver object
 * @param[in]  idMessage Id Message for the buffer to receive.
 * @param[out] buffer    pointer to data buffer to receive
 * @param[in]  buf_len   size of input data buffer
 *
 * @return               number of received bytes
 *
 * @api
 */
uint16_t lin_lld_receive(LinDriver *ldp, uint8_t idMessage, uint8_t *buffer, uint16_t buf_len) {
  uint16_t msg_len;

  if (ldp->config->mode == LIN_MODE_MASTER) {
    msg_len = lin_master_receive(ldp, idMessage, buffer, buf_len);
  } else {
    msg_len = 0;
  }

  return msg_len;
}

#endif /* LLD_USE_LIN */

/** @} */
