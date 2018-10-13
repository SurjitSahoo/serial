#include "../include/serial.h"

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

static status_t sanity_check_config(const SerialPortConfig_t* config);
static status_t sanity_check_device(const SerialPort_t* device);

struct __serial_port_device
{
	EnSerialBaud_t		baud;
	EnSerialParity_t	parity;
	EnSerialStopBit_t	stopBit;
	uint8_t			 	id;
	void*				extra;
};

uint8_t id = 0;
SerialPort_t* mydevices[10];

static status_t sanity_check_config(const SerialPortConfig_t* config){
	if(config == 0){
		return CONFIG_NULL;
	}
    if(config->baud < enSerialBaud_9600 || config->baud > enSerialBaud_Max){
		return CONFIG_INVALID_BAUD;
    }
    if(config->parity < enSerialParity_ODD || config->parity > enSerialParity_Max){
		return CONFIG_INVALID_PARITY;
    }
    if(config->stopBit < enSerialStopBit_One || config->stopBit > enSerialStopBit_Max){
		return CONFIG_INVALID_STOP_BIT;
    }
	return enBoolean_True;
}

static status_t sanity_check_device(const SerialPort_t* device){
	if(device == 0){
		return DEVICE_NULL;
	}
	if(device->id >= MAX_PORT){
		return MAX_PORT_REACHED;
	}
	if(device != mydevices[device->id]){
		return INVALID_DEVICE;
	}
    if(device->baud < enSerialBaud_9600 || device->baud > enSerialBaud_Max){
		return DEVICE_INVALID_BAUD;
    }
    if(device->parity < enSerialParity_ODD || device->parity > enSerialParity_Max){
		return DEVICE_INVALID_PARITY;
    }
    if(device->stopBit < enSerialStopBit_One || device->stopBit > enSerialStopBit_Max){
		return DEVICE_INVALID_STOP_BIT;
    }
}

SerialPort_t* SerialPort_new(SerialPortConfig_t* config, status_t* result)
{
	if(result == 0){
		return SERIAL_RESULT_NULL;
	}
	
	if(id >= MAX_PORT){
		*result = MAX_PORT_REACHED;
		return 0;
	}

	//Sanity check
	*result = sanity_check_config(config);
	if(*result != enBoolean_True){
		return 0;
	}

	
	//malloc and create a serial_port_device
	SerialPort_t* dev = (SerialPort_t *)malloc(sizeof(struct __serial_port_device));

	uint32_t ubrr = 0;
	switch(config->baud) //Set UBBRL/H
	{
		case 0:
			ubrr = BAUD_SCALE(9600);
			_UBRRH(id) = (unsigned char)(ubrr >> 8);
			_UBRRL(id) = (unsigned char) ubrr;
			dev->baud = enSerialBaud_9600;
			break;
		case 1 :
			ubrr = BAUD_SCALE(19200);
			_UBRRH(id) = (unsigned char)(ubrr >> 8);
			_UBRRL(id) = (unsigned char) ubrr;
			dev->baud = enSerialBaud_19200;
			break;
		case 2 :
			ubrr = BAUD_SCALE(38400);
			_UBRRH(id) = (unsigned char)(ubrr >> 8);
			_UBRRL(id) = (unsigned char) ubrr;
			dev->baud = enSerialBaud_38400;
			break;
		case 3 :
			ubrr = BAUD_SCALE(57600);
			_UBRRH(id) = (unsigned char)(ubrr >> 8);
			_UBRRL(id) = (unsigned char) ubrr;
			dev->baud = enSerialBaud_57600;
			break;
		case 4 :
			ubrr = BAUD_SCALE(115200);
			_UBRRH(id) = (unsigned char)(ubrr >> 8);
			_UBRRL(id) = (unsigned char) ubrr;
			dev->baud = enSerialBaud_115200;
			break;
		default :
			free(dev);
			*result = DEVICE_INVALID_BAUD;

	}

	switch(APPLICATION_AVR){
		case 0:
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
					*result = DEVICE_INVALID_PARITY;
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
					*result = DEVICE_INVALID_STOP_BIT;
			}

			// Mode select
			CLR_BIT(UCSR0C, UMSEL00);
			CLR_BIT(UCSR0C, UMSEL01);

			//Frame size
			SET_BIT(UCSR0C, UCSZ00);
			SET_BIT(UCSR0C, UCSZ01);
			CLR_BIT(UCSR0B, UCSZ02);

			*result = enBoolean_True;
			id++;
		default :
			free(dev);
			*result = 0;
	}
	mydevices[id] = dev;
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
	if(status != enBoolean_True){
		return enBoolean_False;
	}
	switch(device->id) {
		case 0 :
			if(IS_BIT_SET(UCSR0B, TXEN0) == 0){
				SET_BIT(UCSR0B, TXEN0);
			}
			if(IS_BIT_SET(UCSR0B, RXEN0) == 0){
				SET_BIT(UCSR0B, RXEN0);
			}
			return enBoolean_True;
		case 1 :
			//code for case
		default :
			return enBoolean_False;
	}
}

status_t SerialPort_close(SerialPort_t* device)
{
	status_t status = sanity_check_device(device);
	if(status != enBoolean_True){
		return enBoolean_False;
	}
	switch(device->id){
		case 0:
			CLR_BIT(UCSR0B, TXEN0);
			CLR_BIT(UCSR0B, RXEN0);
			break;
		default:
			return enBoolean_False;
	}
	return enBoolean_True;
	
}

status_t SerialPort_writeByte(const SerialPort_t* device, unsigned char data){

  status_t status = sanity_check_device(device);
	if(status == 0){
		return enBoolean_False;
	}
	if(IS_BIT_SET(UCSR0B, TXEN0)){
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
	if(IS_BIT_SET(UCSR0B, RXEN0)){
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
