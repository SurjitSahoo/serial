#ifndef __EMB_SERIAL_H__
#define __EMB_SERIAL_H__
#include "types.h"

SerialPort_t*   SerialPort_new(SerialPortConfig_t* config, status_t* result);
status_t        SerialPort_delete(SerialPort_t* device);

status_t        SerialPort_open(SerialPort_t* device);
status_t	    SerialPort_close(SerialPort_t* device);

status_t	    SerialPort_writeByte(const SerialPort_t* device, unsigned char data);
status_t	    SerialPort_readByte(const SerialPort_t* device, unsigned char* data);

status_t set_serial_baud(SerialPort_t* device, EnSerialBaud_t baud);
status_t set_serial_parity(SerialPort_t* device, EnSerialParity_t parity);
status_t set_serial_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit);
status_t set_serial_mode(SerialPort_t* dev, EnSerialMode_t mode);
status_t set_serial_frame(SerialPort_t* device, EnSerialFrame_t frame);

#endif //__EMB_SERIAL_H__