#ifndef __EMB_SERIAL_CONFIG_H__
#define __EMB_SERIAL_CONFIG_H__
#include "../user_config.h"

#ifndef MYAVR
#error "Define the macro MYAVR as 0 (ATmega328|P) or 1 (ATmega8) in user_config.h"
#endif

#if (MYAVR == 0)
#define APPLICATION_AVR 0
#elif (MYAVR == 1)
#define APPLICATION_AVR 1
#else
#error "MYAVR is defined but the value isn't 0 0r 1."
#endif

#endif //__EMB_SERIAL_CONFIG_H__