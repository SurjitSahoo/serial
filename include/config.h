#ifndef __EMB_SERIAL_CONFIG_H__
#define __EMB_SERIAL_CONFIG_H__
#include "../user_config.h"

#ifndef DEVICE
#error  "Define the device you want to program for in "
    #ifndef MYAVR
    #error "Define the macro MYAVR as 0 (ATmega328|P) or 1 (ATmega8) in user_config.h"
    #endif


#endif //__EMB_SERIAL_CONFIG_H__