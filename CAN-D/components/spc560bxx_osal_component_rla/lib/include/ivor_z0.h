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
 * @file    ivor_z0.h
 * @brief   Interrupt Handler Macros.
 *
 * @addtogroup PPC_CORE
 * @{
 */

#define _FROM_ASM_

#if !defined(__DOXYGEN__)

#define LOAD_IVOR1_EXC_REG LOAD_CSSR0_CSSR1
#define RET_IVOR1 se_rfci
#if defined (_SPC570Sxx_)
#define LOAD_IVOR9_EXC_REG LOAD_DSSR0_DSSR1
#define RET_IVOR9 se_rfdi
#else
#define LOAD_IVOR9_EXC_REG LOAD_SSR0_SSR1_PLUS
#define RET_IVOR9 se_rfi
#endif


#endif /* !defined(__DOXYGEN__) */


  /** @} */
