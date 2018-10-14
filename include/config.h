#ifndef __EMB_SERIAL_CONFIG_H__
#define __EMB_SERIAL_CONFIG_H__
#include "../user_config.h"

#ifndef DEVICE
#error  "Define the macro DEVICE as AVR, WIN32 or LINUX in user_config.h"
#elif(defined(DEVICE) && DEVICE == avr)
    #ifndef MYAVR
    #error "Define the macro MYAVR as 0 (ATmega328|P) or 1 (ATmega8) in user_config.h"
    #endif

#else
#error "DEVICE is defined but it's value is not 'avr', 'win32' or 'linux'

#endif //__EMB_SERIAL_CONFIG_H__