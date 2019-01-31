/*
    SPC5 RLA - Copyright (C) 2016 STMicroelectronics

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

/* Inclusion of the main header files of all the imported components in the
   order specified in the application wizard. The file is generated
   automatically.*/
#include "components.h"

#include "FreeRTOS.h"
#include "task.h"

uint8_t message_task1[]= "Task1...\r\n";
uint8_t message_task2[]= "Task2...\r\n";

/* Demo tasks */
portTASK_FUNCTION( vTaskOne, pvParameters )
{
  ( void ) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for ( ;; ) {
    vTaskSuspendAll();
    sd_lld_write(&SD1,message_task1,(uint16_t)(sizeof(message_task1)/sizeof(message_task1[0])));
    xTaskResumeAll();
    pal_lld_togglepad(PORT_C, PC_LED7);
    vTaskDelayUntil( &xLastWakeTime, 200 );
  }
}

/* Demo tasks */
portTASK_FUNCTION( vTaskTwo, pvParameters )
{
  ( void ) pvParameters;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  for ( ;; ) {
    vTaskSuspendAll();
    sd_lld_write(&SD1,message_task2,(uint16_t)(sizeof(message_task2)/sizeof(message_task2[0])));
    xTaskResumeAll();
    vTaskDelayUntil( &xLastWakeTime, 200 );
    pal_lld_togglepad(PORT_C, PC_LED8);
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Enable Interrupts */
  irqIsrEnable();

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sd_lld_start(&SD1, NULL);

  /* Creating first task to blink LED0 */
  xTaskCreate( vTaskOne,
               (const char * const)"task #1",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               NULL );

  /* Creating second task to blink LED1 */
  xTaskCreate( vTaskTwo,
               (const char * const)"task #2",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               NULL );

  /* Start the FreeRTOS scheduler */
  vTaskStartScheduler();

  return 0;

}
