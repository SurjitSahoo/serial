#include "../include/serial.h"


#include <avr/io.h>
int myfunc(void)
{
	return 0;
}

#include<stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

static status_t sanity_check_config(const SerialPortConfig_t* config);
static status_t sanity_check_device(const SerialPort_t* device);

#define F_CPU 16000000L
#define SET_BIT(REG,BIT) REG |= (1 << BIT)
#define CLR_BIT(REG,BIT) REG &= (~(1 << BIT ))
#define IS_BIT_SET(REG, BIT) ((REG & (1 << BIT)) == 0 ? 0 : 1)
#define BAUD_SCALE(BAUD_RATE) ((( F_CPU / 16) + ( BAUD_RATE/ 2)) / ( BAUD_RATE) - 1)

struct __serial_port_device
{
	EnSerialBaud_t    baud;
	EnSerialParity_t  parity;
	EnSerialStopBit_t stopBit;
	uint8_t           is_open;
	uint8_t			  id;
};

#define MAX_PORTS  1
static status_t sanity_check_config(const SerialPortConfig_t* config){
	if(config == 0){
		return enBoolean_False;
	}
    if(config->baud < enSerialBaud_9600 || config->baud > enSerialBaud_Max){
		return enBoolean_False;
    }
    if(config->parity < enSerialParity_ODD || config->parity > enSerialParity_Max){
		return enBoolean_False;
    }
    if(config->stopBit < enSerialStopBit_One || config->stopBit > enSerialStopBit_Max){
		return enBoolean_False;
    }
}

static status_t sanity_check_device(const SerialPort_t* device){
	if(device == 0){
		return enBoolean_False;
	}
    if(device->baud < enSerialBaud_9600 || device->baud > enSerialBaud_Max){
		return enBoolean_False;
    }
    if(device->parity < enSerialParity_ODD || device->parity > enSerialParity_Max){
		return enBoolean_False;
    }
    if(device->stopBit < enSerialStopBit_One || device->stopBit > enSerialStopBit_Max){
		return enBoolean_False;
    }
}

SerialPort_t* SerialPort_new(SerialPortConfig_t* config, status_t* result)
{
	if(result == 0){
		return 0;
	}
	//Sanity check
	*result = sanity_check_config(config);
	if(*result == 0){
		return 0;
	}
	//malloc and create a serial_port_device
	SerialPort_t* dev = (SerialPort_t *)malloc(sizeof(struct __serial_port_device));

	uint32_t ubrr = 0;
	switch(config->baud) //Set UBBRL/H
	{
		case 0:
			ubrr = BAUD_SCALE(9600);
			UBRR0H = (unsigned char)(ubrr >> 8);
			UBRR0L = (unsigned char) ubrr;
			dev->baud = enSerialBaud_9600;
			break;
		case 1 :
			ubrr = BAUD_SCALE(19200);
			UBRR0H = (unsigned char)(ubrr >> 8);
			UBRR0L = (unsigned char) ubrr;
			dev->baud = enSerialBaud_19200;
			break;
		case 2 :
			ubrr = BAUD_SCALE(38400);
			UBRR0H = (unsigned char)(ubrr >> 8);
			UBRR0L = (unsigned char) ubrr;
			dev->baud = enSerialBaud_38400;
			break;
		case 3 :
			ubrr = BAUD_SCALE(57600);
			UBRR0H = (unsigned char)(ubrr >> 8);
			UBRR0L = (unsigned char) ubrr;
			dev->baud = enSerialBaud_57600;
			break;
		case 4 :
			ubrr = BAUD_SCALE(115200);
			UBRR0H = (unsigned char)(ubrr >> 8);
			UBRR0L = (unsigned char) ubrr;
			dev->baud = enSerialBaud_115200;
			break;
		default :
			free(dev);
			*result = enBoolean_False;

	}
	switch(config->parity)
	{
		case 0:
			SET_BIT(UCSR0C, UPM00);
			SET_BIT(UCSR0C, UPM01);
			dev->parity = enSerialParity_ODD;
			break;
		case 1 :
			CLR_BIT(UCSR0C, UPM00);
			SET_BIT(UCSR0C, UPM01);
			dev->parity = enSerialParity_Even;
			break;
		default :
			free(dev);
			*result = enBoolean_False;
	}
	
	switch(config->stopBit)
	{
		case 0 : 
			CLR_BIT(UCSR0C, USBS0);
			dev->stopBit = enSerialStopBit_One;
			break;
		case 1 :
			free(dev);
			*result = enBoolean_False;
			return enBoolean_False;
			break;
		case 2 :
			SET_BIT(UCSR0C, USBS0);
			dev->stopBit = enSerialStopBit_Two;
			break;
		default :
			free(dev);
			*result = enBoolean_False;

	}
    // Mode select
	CLR_BIT(UCSR0C, UMSEL00);
    CLR_BIT(UCSR0C, UMSEL01);

    //Frame size
	SET_BIT(UCSR0C, UCSZ00);
	SET_BIT(UCSR0C, UCSZ01);
	CLR_BIT(UCSR0B, UCSZ02);

	dev->is_open = enBoolean_False;
	*result = enBoolean_True;
	return dev;
}

status_t SerialPort_delete(SerialPort_t* device){
	if(device == 0){
		return enBoolean_False;
	}
	free(device);
	return enBoolean_True;
}

status_t SerialPort_open(SerialPort_t* device)
{
	//Sanity check
	status_t status = sanity_check_device(device);
	if(status == 0){
		return enBoolean_False;
	}
	switch(device->id) {
		case 0 :
			if(IS_BIT_SET(UCSR0B, TXEN0) == 0){
				SET_BIT(UCSR0B, TXEN0);
			}
			if(IS_BIT_SET(UCSR0B, RXEN0) == 0){
				SET_BIT(UCSR0B, TXEN0);
			}
			device->is_open = enBoolean_True;
			return enBoolean_True;
		default :
			return enBoolean_False;
	}
}

status_t SerialPort_close(SerialPort_t* device)
{
	status_t status = sanity_check_device(device);
	if(status == 0){
		return enBoolean_False;
	}
	device->is_open = enBoolean_False;

	return enBoolean_True;
	
}

status_t SerialPort_writeByte(const SerialPort_t* device, unsigned char data){

  status_t status = sanity_check_device(device);
	if(status == 0){
		return enBoolean_False;
	}
	if(device->is_open){
		sei();
		while(!IS_BIT_SET(UCSR0A, UDRE0));
		UDR0 = data;
		cli();
		return enBoolean_True;
	}
	else 
	{
		return enBoolean_False;
	}
}

status_t SerialPort_readByte(const SerialPort_t* device, unsigned char* data){
  status_t status = sanity_check_device(device);
	if(status == 0){
		return enBoolean_False;
	}
	if(device->is_open){
		sei();
		while(!IS_BIT_SET(UCSR0A, RXC0));
		*data = UDR0;
		cli();
		return enBoolean_True;
	}
	else{
		return enBoolean_False;
	}
}
