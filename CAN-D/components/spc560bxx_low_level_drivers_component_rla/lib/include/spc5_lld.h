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
 * @file    spc5_lld.h
 * @brief   SPC5xx subsystem low level driver header.
 *
 * @addtogroup SPC5_LLD
 * @{
 */

#ifndef _SPC5_LLD_H_
#define _SPC5_LLD_H_

#include "platform.h"
#include "board.h"
#include "clock.h"
#include "osal.h"
#include "lldconf.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* IRQ Handlers                                                              */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
  void spc5LLDInit(void);
#ifdef __cplusplus
}
#endif

#endif /* _SPC5_LLD_H_ */

/** @} */
