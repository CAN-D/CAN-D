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
 * @file    lldconf.h
 * @brief   LLD configuration header.
 * @details LLD configuration file, this file allows to enable or disable the
 *          various device drivers from your application. You may also use
 *          this file in order to override the device drivers default settings.
 *
 * @addtogroup LLD_CONF
 * @{
 */

#ifndef _LLDCONF_H_
#define _LLDCONF_H_

/**
 * @name    Drivers enable switches
 */
#define LLD_USE_DMA                 TRUE
#define LLD_USE_PAL                 TRUE
#define LLD_USE_PIT                 FALSE
#define LLD_USE_STM                 FALSE
#define LLD_USE_SERIAL              TRUE
#define LLD_USE_PWM                 TRUE
#define LLD_USE_ICU                 FALSE
#define LLD_USE_CAN                 TRUE
#define LLD_USE_SPI                 TRUE
#define LLD_USE_ADC                 FALSE
#define LLD_USE_CTU                 FALSE
#define LLD_USE_I2C                 FALSE
#define LLD_USE_RTC                 FALSE
#define LLD_USE_SWT                 FALSE
#define LLD_USE_SARADC              FALSE
#define LLD_USE_FCCU                FALSE
#define LLD_USE_CRC                 FALSE
#define LLD_USE_WKPU                FALSE
#define LLD_USE_LIN                 FALSE

/** @} */

/*===========================================================================*/
/**
 * @name SERIAL driver related setting
 * @{
 */
/*===========================================================================*/

/**
 * @name    SERIAL DMA modes
 * @{
 */
#define SPC5_SERIAL_DMA_OFF                 0
#define SPC5_SERIAL_DMA_ON                  1
/** @} */

/**
 * @name    LINFlex Mode Settings
 * @{
 */
#define SPC5_LINFLEX_MODE_NONE              0
#define SPC5_LINFLEX_MODE_SERIAL            1
#define SPC5_LINFLEX_MODE_LIN               2
/** @} */

/*===========================================================================*/
/**
 * @name SPI driver related setting
 * @{
 */
/*===========================================================================*/

/**
 * @brief   Enables synchronous APIs.
 * @note    Disabling this option saves both code and data space.
 */
#if !defined(SPI_USE_WAIT) || defined(__DOXYGEN__)
#define SPI_USE_WAIT                TRUE
#endif

/**
 * @brief   Enables the @p spiAcquireBus() and @p spiReleaseBus() APIs.
 * @note    Disabling this option saves both code and data space.
 */
#if !defined(SPI_USE_MUTUAL_EXCLUSION) || defined(__DOXYGEN__)
#define SPI_USE_MUTUAL_EXCLUSION    FALSE
#endif
/** @} */

/**
 * @name    SPI DMA modes
 * @{
 */
#define SPC5_SPI_DMA_NONE                   0
#define SPC5_SPI_DMA_RX_ONLY                1
#define SPC5_SPI_DMA_RX_AND_TX              2
/** @} */

/**
 * @name    ADC DMA modes
 * @{
 */
#define SPC5_ADC_DMA_OFF                    0
#define SPC5_ADC_DMA_ON                     1
/** @} */

/*
 * EDMA driver settings.
 */
#define SPC5_EDMA_CR_SETTING                (EDMA_CR_GRP1PRI(1) |           \
                                             EDMA_CR_GRP0PRI(0) |           \
                                             EDMA_CR_EMLM       |           \
                                             EDMA_CR_ERGA)
#define SPC5_EDMA_GROUP0_PRIORITIES         0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
#define SPC5_EDMA_ERROR_IRQ_PRIO            12
#define SPC5_EDMA_ERROR_HANDLER()           irqSysHalt()

/*
 * SERIAL driver system settings.
 */
#define SPC5_LINFLEX0_SETTING               SPC5_LINFLEX_MODE_SERIAL
#define SPC5_LINFLEX1_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX2_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX3_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX4_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX5_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX6_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX7_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX8_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX9_SETTING               SPC5_LINFLEX_MODE_NONE
#define SPC5_LINFLEX0_PRIORITY              8
#define SPC5_LINFLEX1_PRIORITY              8
#define SPC5_LINFLEX2_PRIORITY              8
#define SPC5_LINFLEX3_PRIORITY              8
#define SPC5_LINFLEX4_PRIORITY              8
#define SPC5_LINFLEX5_PRIORITY              8
#define SPC5_LINFLEX6_PRIORITY              8
#define SPC5_LINFLEX7_PRIORITY              8
#define SPC5_LINFLEX8_PRIORITY              8
#define SPC5_LINFLEX9_PRIORITY              8
#define SPC5_SERIAL_DMA_MODE                SPC5_SERIAL_DMA_OFF               

#define SPC5_SERIAL_LINFLEX0_TX_DMA_CH_ID   0
#define SPC5_SERIAL_LINFLEX0_RX_DMA_CH_ID   1
#define SPC5_SERIAL_LINFLEX1_TX_DMA_CH_ID   2
#define SPC5_SERIAL_LINFLEX1_RX_DMA_CH_ID   3
#define SPC5_SERIAL_LINFLEX0_DMA_IRQ_PRIO   8
#define SPC5_SERIAL_LINFLEX1_DMA_IRQ_PRIO   8

/*
 * SPI driver system settings.
 */
#define SPC5_SPI_USE_DSPI0                  TRUE
#define SPC5_SPI_USE_DSPI1                  FALSE
#define SPC5_SPI_USE_DSPI2                  FALSE
#define SPC5_SPI_USE_DSPI3                  FALSE
#define SPC5_SPI_USE_DSPI4                  FALSE
#define SPC5_SPI_USE_DSPI5                  FALSE
#define SPC5_SPI_DSPI0_SLAVE                FALSE
#define SPC5_SPI_DSPI1_SLAVE                FALSE
#define SPC5_SPI_DSPI2_SLAVE                FALSE
#define SPC5_SPI_DSPI3_SLAVE                FALSE
#define SPC5_SPI_DSPI4_SLAVE                FALSE
#define SPC5_SPI_DSPI5_SLAVE                FALSE
#define SPC5_SPI_DMA_MODE                   SPC5_SPI_DMA_RX_ONLY
#define SPC5_SPI_DSPI0_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1 | SPC5_MCR_PCSIS2 | SPC5_MCR_PCSIS3 | SPC5_MCR_PCSIS4 | SPC5_MCR_PCSIS5)
#define SPC5_SPI_DSPI1_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1 | SPC5_MCR_PCSIS2 | SPC5_MCR_PCSIS3 | SPC5_MCR_PCSIS4)
#define SPC5_SPI_DSPI2_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1 | SPC5_MCR_PCSIS2 | SPC5_MCR_PCSIS3)
#define SPC5_SPI_DSPI3_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1)
#define SPC5_SPI_DSPI4_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1)
#define SPC5_SPI_DSPI5_MCR                  (0U | SPC5_MCR_PCSIS0 | SPC5_MCR_PCSIS1)
#define SPC5_SPI_DSPI0_TX1_DMA_CH_ID        4
#define SPC5_SPI_DSPI0_TX2_DMA_CH_ID        5
#define SPC5_SPI_DSPI0_RX_DMA_CH_ID         6
#define SPC5_SPI_DSPI1_TX1_DMA_CH_ID        7
#define SPC5_SPI_DSPI1_TX2_DMA_CH_ID        8
#define SPC5_SPI_DSPI1_RX_DMA_CH_ID         9
#define SPC5_SPI_DSPI2_TX1_DMA_CH_ID        10
#define SPC5_SPI_DSPI2_TX2_DMA_CH_ID        11
#define SPC5_SPI_DSPI2_RX_DMA_CH_ID         12
#define SPC5_SPI_DSPI3_TX1_DMA_CH_ID        13
#define SPC5_SPI_DSPI3_TX2_DMA_CH_ID        14
#define SPC5_SPI_DSPI3_RX_DMA_CH_ID         15
#define SPC5_SPI_DSPI4_TX1_DMA_CH_ID        1
#define SPC5_SPI_DSPI4_TX2_DMA_CH_ID        2
#define SPC5_SPI_DSPI4_RX_DMA_CH_ID         3
#define SPC5_SPI_DSPI5_TX1_DMA_CH_ID        4
#define SPC5_SPI_DSPI5_TX2_DMA_CH_ID        5
#define SPC5_SPI_DSPI5_RX_DMA_CH_ID         6
#define SPC5_SPI_DSPI0_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI1_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI2_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI3_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI4_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI5_DMA_IRQ_PRIO         10
#define SPC5_SPI_DSPI0_IRQ_PRIO             10
#define SPC5_SPI_DSPI1_IRQ_PRIO             10
#define SPC5_SPI_DSPI2_IRQ_PRIO             10
#define SPC5_SPI_DSPI3_IRQ_PRIO             10
#define SPC5_SPI_DSPI4_IRQ_PRIO             10
#define SPC5_SPI_DSPI5_IRQ_PRIO             10
#define SPC5_SPI_DMA_ERROR_HOOK(spip)       irqSysHalt()

/*
 * ICU-PWM driver system settings.
 */
#define SPC5_PWM_USE_EMIOS0_COUNT_BUS       EMIOS_PWM_COUNTER_BUS_A

#define SPC5_ICU_USE_EMIOS0_CH0             FALSE
#define SPC5_ICU_USE_EMIOS0_CH1             FALSE
#define SPC5_ICU_USE_EMIOS0_CH2             FALSE
#define SPC5_ICU_USE_EMIOS0_CH3             FALSE
#define SPC5_ICU_USE_EMIOS0_CH4             FALSE
#define SPC5_ICU_USE_EMIOS0_CH5             FALSE
#define SPC5_ICU_USE_EMIOS0_CH6             FALSE
#define SPC5_ICU_USE_EMIOS0_CH7             FALSE
#define SPC5_ICU_USE_EMIOS0_CH8             FALSE
#define SPC5_ICU_USE_EMIOS0_CH16            FALSE
#define SPC5_ICU_USE_EMIOS0_CH24            FALSE

#define SPC5_PWM_USE_EMIOS0_CH0             FALSE
#define SPC5_PWM_USE_EMIOS0_CH1             FALSE
#define SPC5_PWM_USE_EMIOS0_CH2             FALSE
#define SPC5_PWM_USE_EMIOS0_CH3             FALSE
#define SPC5_PWM_USE_EMIOS0_CH4             FALSE
#define SPC5_PWM_USE_EMIOS0_CH5             FALSE
#define SPC5_PWM_USE_EMIOS0_CH6             FALSE
#define SPC5_PWM_USE_EMIOS0_CH7             FALSE
#define SPC5_PWM_USE_EMIOS0_CH8             FALSE
#define SPC5_PWM_USE_EMIOS0_CH9             FALSE
#define SPC5_PWM_USE_EMIOS0_CH10            FALSE
#define SPC5_PWM_USE_EMIOS0_CH11            FALSE
#define SPC5_PWM_USE_EMIOS0_CH12            FALSE
#define SPC5_PWM_USE_EMIOS0_CH13            FALSE
#define SPC5_PWM_USE_EMIOS0_CH14            FALSE
#define SPC5_PWM_USE_EMIOS0_CH15            FALSE
#define SPC5_PWM_USE_EMIOS0_CH16            FALSE
#define SPC5_PWM_USE_EMIOS0_CH17            FALSE
#define SPC5_PWM_USE_EMIOS0_CH18            FALSE
#define SPC5_PWM_USE_EMIOS0_CH19            FALSE
#define SPC5_PWM_USE_EMIOS0_CH20            FALSE
#define SPC5_PWM_USE_EMIOS0_CH21            FALSE
#define SPC5_PWM_USE_EMIOS0_CH22            FALSE
#define SPC5_PWM_USE_EMIOS0_CH23            FALSE
#define SPC5_PWM_USE_EMIOS0_CH24            FALSE
#define SPC5_PWM_USE_EMIOS0_CH25            FALSE
#define SPC5_PWM_USE_EMIOS0_CH26            FALSE
#define SPC5_PWM_USE_EMIOS0_CH27            FALSE
#define SPC5_PWM_USE_EMIOS0_CH28            FALSE
#define SPC5_PWM_USE_EMIOS0_CH29            FALSE
#define SPC5_PWM_USE_EMIOS0_CH30            FALSE
#define SPC5_PWM_USE_EMIOS0_CH31            FALSE

#define SPC5_EMIOS0_GFR_F0F1_PRIORITY       8
#define SPC5_EMIOS0_GFR_F2F3_PRIORITY       8
#define SPC5_EMIOS0_GFR_F4F5_PRIORITY       8
#define SPC5_EMIOS0_GFR_F6F7_PRIORITY       8
#define SPC5_EMIOS0_GFR_F8F9_PRIORITY       8
#define SPC5_EMIOS0_GFR_F10F11_PRIORITY     8
#define SPC5_EMIOS0_GFR_F12F13_PRIORITY     8
#define SPC5_EMIOS0_GFR_F14F15_PRIORITY     8
#define SPC5_EMIOS0_GFR_F16F17_PRIORITY     8
#define SPC5_EMIOS0_GFR_F18F19_PRIORITY     8
#define SPC5_EMIOS0_GFR_F20F21_PRIORITY     8
#define SPC5_EMIOS0_GFR_F22F23_PRIORITY     8
#define SPC5_EMIOS0_GFR_F24F25_PRIORITY     8
#define SPC5_EMIOS0_GFR_F26F27_PRIORITY     8
#define SPC5_EMIOS0_GFR_F28F29_PRIORITY     8
#define SPC5_EMIOS0_GFR_F30F31_PRIORITY     8

#define SPC5_EMIOS0_START_PCTL              (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_EMIOS0_STOP_PCTL               (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_EMIOS0_GPRE_VALUE              20UL

#define SPC5_PWM_USE_EMIOS1_COUNT_BUS       EMIOS_PWM_DISABLED

#define SPC5_ICU_USE_EMIOS1_CH0             FALSE
#define SPC5_ICU_USE_EMIOS1_CH8             FALSE
#define SPC5_ICU_USE_EMIOS1_CH16            FALSE
#define SPC5_ICU_USE_EMIOS1_CH24            FALSE

#define SPC5_PWM_USE_EMIOS1_CH0             FALSE
#define SPC5_PWM_USE_EMIOS1_CH1             FALSE
#define SPC5_PWM_USE_EMIOS1_CH2             FALSE
#define SPC5_PWM_USE_EMIOS1_CH3             FALSE
#define SPC5_PWM_USE_EMIOS1_CH4             FALSE
#define SPC5_PWM_USE_EMIOS1_CH5             FALSE
#define SPC5_PWM_USE_EMIOS1_CH6             FALSE
#define SPC5_PWM_USE_EMIOS1_CH7             FALSE
#define SPC5_PWM_USE_EMIOS1_CH8             FALSE
#define SPC5_PWM_USE_EMIOS1_CH9             FALSE
#define SPC5_PWM_USE_EMIOS1_CH10            FALSE
#define SPC5_PWM_USE_EMIOS1_CH11            FALSE
#define SPC5_PWM_USE_EMIOS1_CH12            FALSE
#define SPC5_PWM_USE_EMIOS1_CH13            FALSE
#define SPC5_PWM_USE_EMIOS1_CH14            FALSE
#define SPC5_PWM_USE_EMIOS1_CH15            FALSE
#define SPC5_PWM_USE_EMIOS1_CH16            FALSE
#define SPC5_PWM_USE_EMIOS1_CH17            FALSE
#define SPC5_PWM_USE_EMIOS1_CH18            FALSE
#define SPC5_PWM_USE_EMIOS1_CH19            FALSE
#define SPC5_PWM_USE_EMIOS1_CH20            FALSE
#define SPC5_PWM_USE_EMIOS1_CH21            FALSE
#define SPC5_PWM_USE_EMIOS1_CH22            FALSE
#define SPC5_PWM_USE_EMIOS1_CH23            FALSE
#define SPC5_PWM_USE_EMIOS1_CH24            FALSE
#define SPC5_PWM_USE_EMIOS1_CH25            FALSE
#define SPC5_PWM_USE_EMIOS1_CH26            FALSE
#define SPC5_PWM_USE_EMIOS1_CH27            FALSE
#define SPC5_PWM_USE_EMIOS1_CH28            FALSE
#define SPC5_PWM_USE_EMIOS1_CH29            FALSE
#define SPC5_PWM_USE_EMIOS1_CH30            FALSE
#define SPC5_PWM_USE_EMIOS1_CH31            FALSE

#define SPC5_EMIOS1_GFR_F0F1_PRIORITY       8
#define SPC5_EMIOS1_GFR_F2F3_PRIORITY       8
#define SPC5_EMIOS1_GFR_F4F5_PRIORITY       8
#define SPC5_EMIOS1_GFR_F6F7_PRIORITY       8
#define SPC5_EMIOS1_GFR_F8F9_PRIORITY       8
#define SPC5_EMIOS1_GFR_F10F11_PRIORITY     8
#define SPC5_EMIOS1_GFR_F12F13_PRIORITY     8
#define SPC5_EMIOS1_GFR_F14F15_PRIORITY     8
#define SPC5_EMIOS1_GFR_F16F17_PRIORITY     8
#define SPC5_EMIOS1_GFR_F18F19_PRIORITY     8
#define SPC5_EMIOS1_GFR_F20F21_PRIORITY     8
#define SPC5_EMIOS1_GFR_F22F23_PRIORITY     8
#define SPC5_EMIOS1_GFR_F24F25_PRIORITY     8
#define SPC5_EMIOS1_GFR_F26F27_PRIORITY     8
#define SPC5_EMIOS1_GFR_F28F29_PRIORITY     8
#define SPC5_EMIOS1_GFR_F30F31_PRIORITY     8

#define SPC5_EMIOS1_START_PCTL              (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_EMIOS1_STOP_PCTL               (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_EMIOS1_GPRE_VALUE              20UL

/*
 * CAN driver system settings.
 */
#define SPC5_CAN_USE_FILTERS                FALSE

#define SPC5_CAN_USE_FLEXCAN0               TRUE
#define SPC5_CAN_FLEXCAN0_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN0_IRQ_PRIORITY      11
#define SPC5_CAN_NUM_RX_MAILBOXES           8U
#define SPC5_CAN_NUM_TX_MAILBOXES           24U
#define SPC5_CAN_FLEXCAN0_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN0_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_CAN_USE_FLEXCAN1               FALSE
#define SPC5_CAN_FLEXCAN1_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN1_IRQ_PRIORITY      11
#define SPC5_CAN_FLEXCAN1_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN1_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_CAN_USE_FLEXCAN2               FALSE
#define SPC5_CAN_FLEXCAN2_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN2_IRQ_PRIORITY      11
#define SPC5_CAN_FLEXCAN2_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN2_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_CAN_USE_FLEXCAN3               FALSE
#define SPC5_CAN_FLEXCAN3_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN3_IRQ_PRIORITY      11
#define SPC5_CAN_FLEXCAN3_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN3_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_CAN_USE_FLEXCAN4               FALSE
#define SPC5_CAN_FLEXCAN4_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN4_IRQ_PRIORITY      11
#define SPC5_CAN_FLEXCAN4_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN4_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

#define SPC5_CAN_USE_FLEXCAN5               FALSE
#define SPC5_CAN_FLEXCAN5_USE_EXT_CLK       FALSE
#define SPC5_CAN_FLEXCAN5_IRQ_PRIORITY      11
#define SPC5_CAN_FLEXCAN5_START_PCTL        (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_CAN_FLEXCAN5_STOP_PCTL         (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

/*
* ADC driver system settings.
*/


#define SPC5_ADC_DMA_MODE                   SPC5_ADC_DMA_ON

#define SPC5_ADC_USE_ADC0                   FALSE
#define SPC5_ADC_ADC0_CLK_FREQUENCY         HALF_PERIPHERAL_SET_CLOCK_FREQUENCY
#define SPC5_ADC_ADC0_AUTO_CLOCK_OFF        FALSE
#define SPC5_ADC_ADC0_WD_PRIORITY           12
#define SPC5_ADC_ADC0_EOC_PRIORITY          SPC5_ADC_ADC0_WD_PRIORITY
#define SPC5_ADC_ADC0_DMA_CH_ID             1
#define SPC5_ADC_ADC0_DMA_IRQ_PRIO          12
#define SPC5_ADC_ADC0_START_PCTL            (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_ADC_ADC0_STOP_PCTL             (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))



#define SPC5_ADC_USE_ADC1                   FALSE
#define SPC5_ADC_ADC1_CLK_FREQUENCY         HALF_PERIPHERAL_SET_CLOCK_FREQUENCY
#define SPC5_ADC_ADC1_AUTO_CLOCK_OFF        FALSE
#define SPC5_ADC_ADC1_WD_PRIORITY           12
#define SPC5_ADC_ADC1_EOC_PRIORITY          SPC5_ADC_ADC1_WD_PRIORITY
#define SPC5_ADC_ADC1_DMA_CH_ID             2
#define SPC5_ADC_ADC1_DMA_IRQ_PRIO          12
#define SPC5_ADC_ADC1_START_PCTL            (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_ADC_ADC1_STOP_PCTL             (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))

/*
* PIT driver system settings.
*/
#define PIT_CHANNEL_CH0_ENABLED             FALSE
#define PIT_CHANNEL_CH1_ENABLED             FALSE
#define PIT_CHANNEL_CH2_ENABLED             FALSE
#define PIT_CHANNEL_CH3_ENABLED             FALSE
#define PIT_CHANNEL_CH4_ENABLED             FALSE
#define PIT_CHANNEL_CH5_ENABLED             FALSE
#define PIT_CHANNEL_CH6_ENABLED             FALSE
#define PIT_CHANNEL_CH7_ENABLED             FALSE
#define SPC5_PIT_START_PCTL                 (SPC5_ME_PCTL_RUN(1) |          \
                                             SPC5_ME_PCTL_LP(2))
#define SPC5_PIT_STOP_PCTL                  (SPC5_ME_PCTL_RUN(0) |          \
                                             SPC5_ME_PCTL_LP(0))
#define SPC5_PIT_CH0_IRQ_PRIO               4
#define SPC5_PIT_CH1_IRQ_PRIO               12
#define SPC5_PIT_CH2_IRQ_PRIO               12
#define SPC5_PIT_CH3_IRQ_PRIO               12

/*
* STM driver system settings.
*/
#define SPC5_STM_USE_STM0                   FALSE
#define SPC5_STM0_CH0_ENABLED               FALSE
#define SPC5_STM0_CH1_ENABLED               FALSE
#define SPC5_STM0_CH2_ENABLED               FALSE
#define SPC5_STM0_CH3_ENABLED               FALSE
#define SPC5_STM0_SYSCLOCK_PRE              1
#define SPC5_STM0_CH0_IRQ_PRIORITY          INTC_PSR_ENABLE(INTC_PSR_MAINCORE,11)
#define SPC5_STM0_CH1_IRQ_PRIORITY          INTC_PSR_ENABLE(INTC_PSR_MAINCORE,11)
#define SPC5_STM0_CH2_IRQ_PRIORITY          INTC_PSR_ENABLE(INTC_PSR_MAINCORE,11)
#define SPC5_STM0_CH3_IRQ_PRIORITY          INTC_PSR_ENABLE(INTC_PSR_MAINCORE,12)


/*
 * SWT driver system settings.
 */
#define SPC5_SWT_USE_SWT0                   FALSE
#define SPC5_SWT0_IRQ_PRIORITY              INTC_PSR_ENABLE(INTC_PSR_MAINCORE, 1)

#define SPC5_SWT0_CLOCK_SOURCE_OSC          TRUE
#define SPC5_SWT0_FREQUENCY                 128000U
#define SPC5_SWT0_TIMEOUT_PERIOD            0
#define SPC5_SWT0_INTERRUPT_MODE            TRUE
#define SPC5_SWT0_PSEUDO_RANDOM_KEY         FALSE
#define SPC5_SWT0_WINDOW_MODE               FALSE
#define SPC5_SWT0_WINDOW_PERIOD             0
#define SPC5_SWT0_STOP_IN_STOP_MODE         FALSE
#define SPC5_SWT0_FREEZE_IN_DEBUG_MODE      TRUE
#define SPC5_SWT0_SYSTEM_RESET              FALSE

#endif /* _LLDCONF_H_ */

/** @} */
