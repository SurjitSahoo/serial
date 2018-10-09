#ifndef __EMB_SERIAL_DEFS_H__
#define __EMB_SERIAL_DEFS_H__
#include "config.h"
  
#define SET_BIT(REG,BIT) REG |= (1 << BIT)
#define CLR_BIT(REG,BIT) REG &= (~(1 << BIT ))
#define IS_BIT_SET(REG, BIT) ((REG & (1 << BIT)) == 0 ? 0 : 1)
#define BAUD_SCALE(BAUD_RATE) ((( F_CPU / 16) + ( BAUD_RATE/ 2)) / ( BAUD_RATE) - 1)

//Error Codes
#define SERIAL_RESULT_NULL       0
#define MAX_PORT_REACHED        -1
#define CONFIG_NULL             -2
#define CONFIG_INVALID_BAUD     -3
#define CONFIG_INVALID_PARITY   -4
#define CONFIG_INVALID_STOP_BIT -5
#define DEVICE_NULL             -6
#define DEVICE_INVALID_BAUD     -7
#define DEVICE_INVALID_PARITY   -8
#define DEVICE_INVALID_STOP_BIT -9


#endif //__EMB_SERIAL_DEFS_H__