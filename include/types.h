#ifndef __EMB_SERIAL_TYPES_H__
#define __EMB_SERIAL_TYPES_H__
#include "defs.h"

typedef enum
{
	enSerialBaud_9600,
	enSerialBaud_19200,
	enSerialBaud_38400,
	enSerialBaud_57600,
	enSerialBaud_115200,
	enSerialBaud_Max
}EnSerialBaud_t;


typedef enum
{
	enSerialParity_ODD,
	enSerialParity_Even,
	enSerialParity_Max
}EnSerialParity_t;

typedef enum
{
	enSerialStopBit_One,
	enSerialStopBit_OneAndHalf,
	enSerialStopBit_Two,
	enSerialStopBit_Max
}EnSerialStopBit_t;



typedef struct
{
	EnSerialBaud_t    baud;
	EnSerialParity_t  parity;
	EnSerialStopBit_t stopBit;
	uint8_t			  id;
}SerialPortConfig_t;

typedef enum
{
	enBoolean_False,
	enBoolean_True,
	enBoolean_Max
}EnBoolean_t;



typedef struct __serial_port_device SerialPort_t;
typedef int status_t;

SerialPort_t* SerialPort_new(SerialPortConfig_t* config, status_t* result);
status_t	SerialPort_delete(SerialPort_t* device);

status_t	SerialPort_open(SerialPort_t* device);
status_t	SerialPort_close(SerialPort_t* device);

status_t	SerialPort_writeByte(const SerialPort_t* device, unsigned char data);
status_t	SerialPort_readByte(const SerialPort_t* device, unsigned char* data);

status_t	_sanity_check_config(const SerialPortConfig_t* config);
status_t _sanity_check_device(const SerialPort_t* device);




#endif //__EMB_SERIAL_TYPES_H__