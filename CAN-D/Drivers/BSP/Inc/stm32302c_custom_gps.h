/**
  ******************************************************************************
  * @file    stm32302c_custom_gps.h
  * @author  Mark Griffith
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32303c_custom_gps.c driver.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32303C_CUSTOM_GPS_H
#define __STM32303C_CUSTOM_GPS_H

#ifdef __cplusplus
 extern "C" {
#endif


#include "stm32303c_custom.h"

/* Commands to set the update rate from once a second (1 Hz) to 10 times a second (10Hz) */
// Note that these only control the rate at which the position is echoed, to actually speed up the
// position fix you must also send one of the position fix rate commands below too.
#define PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ	"$PMTK220,10000*2F\r\n" /* Once every 10 seconds, 100 millihertz. */
#define PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ "$PMTK220,5000*1B\r\n"  /* Once every 5 seconds, 200 millihertz. */
#define PMTK_SET_NMEA_UPDATE_1HZ  	        "$PMTK220,1000*1F\r\n"	/* Once every 1 second, 1 Hz */
#define PMTK_SET_NMEA_UPDATE_5HZ            "$PMTK220,200*2C\r\n"   /* 5 Times every second, 5 Hz */
#define PMTK_SET_NMEA_UPDATE_10HZ           "$PMTK220,100*2F\r\n"	  /* 10 Times every second, 10 Hz */

/* Position fix update rate commands. */
#define PMTK_API_SET_FIX_CTL_100_MILLIHERTZ	"$PMTK300,10000,0,0,0,0*2C\r\n" // Once every 10 seconds, 100 millihertz.
#define PMTK_API_SET_FIX_CTL_200_MILLIHERTZ	"$PMTK300,5000,0,0,0,0*18\r\n"  // Once every 5 seconds, 200 millihertz.
#define PMTK_API_SET_FIX_CTL_1HZ            "$PMTK300,1000,0,0,0,0*1C\r\n"
#define PMTK_API_SET_FIX_CTL_5HZ            "$PMTK300,200,0,0,0,0*2F\r\n"
// Can't fix position faster than 5 times a second!

#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n" /* GPRMC data only */
#define PMTK_SET_NMEA_OUTPUT_RMCGGA	 "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n" /* GPRMC and GGA data */
#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n"
#define PMTK_SET_NMEA_OUTPUT_OFF     "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n"

void BSP_GPS_Init(void);

/* Link functions for GPS peripheral over UART */
void GPS_IO_Init(void);
void GPS_IO_WriteString(char Msg[]);


#ifdef __cplusplus
}
#endif

#endif /* __H */