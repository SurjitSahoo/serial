#ifndef __PRIVATE_AVR_SERIAL_H__
#define __PRIVATE_AVR_SERIAL_H__

#include "../../include/serial.h"

#ifndef MYAVR
#error "This source file is only meant for avr family of processors."
#endif

#if (MYAVR == 0)
#define APPLICATION_AVR 0
#define F_CPU           16000000L
    //This device supports only one UART port
    #if(defined(PORTS) && PORTS == 1)
    #define MAX_PORT    1
    #else
    #define MAX_PORT    0
    #endif

#elif (MYAVR == 1)
#define APPLICATION_AVR 1
//#define F_CPU
//#define MAX_PORT  
#else
#error "MYAVR is defined but the value isn't 0 0r 1."
#endif

#define SET_BIT(REG, BIT)        (REG |= (1 << BIT))
#define CLR_BIT(REG, BIT)        (REG &= (~(1 << BIT)))
#define IS_BIT_SET(REG, BIT)    ((REG & (1 << BIT)) == 0 ? 0 : 1)
#define BAUD_SCALE(BAUD_RATE)   ((( F_CPU / 16) + ( BAUD_RATE/ 2)) / ( BAUD_RATE) - 1)



#endif //__PRIVATE_AVR_SERIAL_H__