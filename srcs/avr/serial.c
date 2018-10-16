#include "../include/serial.h"
#include "private_avr_serial.h"

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

static status_t __sanity_check_config(const SerialPortConfig_t* config);
static status_t __sanity_check_device(const SerialPort_t* device);

struct __serial_port_device
{
	uint8_t			 	id;
	void*				extra;
};

uint8_t id = 0;
SerialPort_t* mydevices[MAX_PORT];

status_t set_serial_baud(SerialPort_t* device, EnSerialBaud_t baud){
	status_t result = sanity_check_device(device);
	if(result != SERIAL_STATUS_OK){
		return SERIAL_STATUS_ERROR;
	}
	uint32_t ubrr = 0;
	if(APPLICATION_AVR == 0){
		// when we add support for other avr which supports multiple uart ports
		// we'll add the condition for other avr in above if statement
		//e.g if(APPLICATION_AVR == 0 || APPLICATION_AVR == 3)
		switch(device->id){status_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)
		case 0: //For device id 0status_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)
			switch(baud){status_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)
				case 0:status_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)
					ubrr = BAUD_SCAstatus_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)LE(9600);
					UBRR0H = (unsigstatus_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)ned char)(ubrr >> 8);
					UBRR0L = (unsigstatus_t __update_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit)ned char)ubrr;
					break;
				case 1:
					ubrr = BAUD_SCALE(19200);
					UBRR0H = (unsigned char)(ubrr >> 8);
					UBRR0L = (unsigned char) ubrr;
					break;
				case 2:
					ubrr = BAUD_SCALE(38400);
					UBRR0H = (unsigned char)(ubrr >> 8);
					UBRR0L = (unsigned char) ubrr;
					break;
				case 3:
					ubrr = BAUD_SCALE(57600);
					UBRR0H = (unsigned char)(ubrr >> 8);
					UBRR0L = (unsigned char) ubrr;
					break;
				case 4:
					ubrr = BAUD_SCALE(115200);
					UBRR0H = (unsigned char)(ubrr >> 8);
					UBRR0L = (unsigned char) ubrr;
					break;
				default:
					return SERIAL_STATUS_ERROR;
			}
			break; //End of device id 0

		case 1: //For device id 1
			switch(baud){
				case 0:
					ubrr = BAUD_SCALE(9600);
					UBRR1H = (unsigned char)(ubrr >> 8);
					UBRR1L = (unsigned char)ubrr;
					break;
				case 1:
					ubrr = BAUD_SCALE(19200);
					UBRR1H = (unsigned char)(ubrr >> 8);
					UBRR1L = (unsigned char) ubrr;
					break;
				case 2:
					ubrr = BAUD_SCALE(38400);
					UBRR1H = (unsigned char)(ubrr >> 8);
					UBRR1L = (unsigned char) ubrr;
					break;
				case 3:
					ubrr = BAUD_SCALE(57600);
					UBRR1H = (unsigned char)(ubrr >> 8);
					UBRR1L = (unsigned char) ubrr;
					break;
				case 4:
					ubrr = BAUD_SCALE(115200);
					UBRR1H = (unsigned char)(ubrr >> 8);
					UBRR1L = (unsigned char) ubrr;
					break;
				default:
					return SERIAL_STATUS_ERROR;
			}
			break; //End of device id 1

		default:
			return SERIAL_STATUS_ERROR;

		} //End of switch defice->id
	
	return SERIAL_STATUS_OK;
	}//End of If

	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		switch(baud){
			case 0:
				ubrr = BAUD_SCALE(9600);
				UBRRH = (unsigned char)(ubrr >> 8);
				UBRRL = (unsigned char)ubrr;
				break;
			case 1:
				ubrr = BAUD_SCALE(19200);
				UBRRH = (unsigned char)(ubrr >> 8);
				UBRRL = (unsigned char) ubrr;
				break;
			case 2:
				ubrr = BAUD_SCALE(38400);
				UBRRH = (unsigned char)(ubrr >> 8);
				UBRRL = (unsigned char) ubrr;
				break;
			case 3:
				ubrr = BAUD_SCALE(57600);
				UBRRH = (unsigned char)(ubrr >> 8);
				UBRRL = (unsigned char) ubrr;
				break;
			case 4:
				ubrr = BAUD_SCALE(115200);
				UBRRH = (unsigned char)(ubrr >> 8);
				UBRRL = (unsigned char) ubrr;
				break;
			default:
				return SERIAL_STATUS_ERROR;
		}
	
	return SERIAL_STATUS_OK;
	}
	
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t set_serial_parity(SerialPort_t* device, EnSerialParity_t parity){
	status_t result = sanity_check_device(device);
	if(result != SERIAL_STATUS_OK){
		return SERIAL_STATUS_ERROR;
	}

	if(APPLICATION_AVR == 0){ 
		// when we add support for other avr which supports multiple uart ports
		// we'll add the condition for other avr in above if statement
		//e.g if(APPLICATION_AVR == 0 || APPLICATION_AVR == 3)
		switch(devie->id){
			case 0:
				switch(parity){
					case 0:
						SET_BIT(UCSR0C, UPM00);
						SET_BIT(UCSR0C, UPM01);
						break;
					case 1 :
						CLR_BIT(UCSR0C, UPM00);
						SET_BIT(UCSR0C, UPM01);
						break;
					default :
						return SERIAL_STATUS_ARG_IS_INVALID;
				}
				break;
			case 1:
				switch(parity){
					case 0:
						SET_BIT(UCSR1C, UPM10);
						SET_BIT(UCSR1C, UPM11);
						break;
					case 1 :
						CLR_BIT(UCSR1C, UPM10);
						SET_BIT(UCSR1C, UPM11);
						break;
					default :
						return SERIAL_STATUS_ARG_IS_INVALID;
				}
				break;
			default :
				return SERIAL_STATUS_NOT_SUPPORTED;
		}// End of switch(device->id)
		return SERIAL_STATUS_OK;
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		switch(parity){
			case 0:
				SET_BIT(UCSRC, UPM10);
				SET_BIT(UCSRC, UPM11);
				break;
			case 1 :
				CLR_BIT(UCSRC, UPM10);
				SET_BIT(UCSRC, UPM11);
				break;
			default :
				return SERIAL_STATUS_ERROR;
		}
		return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t set_serial_stopbit(SerialPort_t* device, EnSerialStopBit_t stopBit){
	status_t result = sanity_check_device(device);
	if(result != SERIAL_STATUS_OK){
		return SERIAL_STATUS_ERROR;
	}

	if(APPLICATION_AVR == 0){
		switch(device->id){
			case 0:
				switch(stopBit){
					case 0 : 
						CLR_BIT(UCSR0C, USBS0);
						break;
					case 1 :
						return SERIAL_STATUS_NOT_SUPPORTED;
						break;
					case 2 :
						SET_BIT(UCSR0C, USBS0);
						break;
					default :
						return SERIAL_STATUS_ARG_IS_INVALID;
				}
				case 1:
					switch(stopBit){
						case 0 : 
							CLR_BIT(UCSR1C, USBS1);
							break;
						case 1 :
							return SERIAL_STATUS_NOT_SUPPORTED;
							break;
						case 2 :
							SET_BIT(UCSR1C, USBS1);
							break;
						default :
							return SERIAL_STATUS_ARG_IS_INVALID;
					}
				default:
					return SERIAL_STATUS_NOT_SUPPORTED;

		}
		return SERIAL_STATUS_OK;
	}//End of if statement
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		switch(stopBit){
			case 0 : 
				CLR_BIT(UCSRC, USBS);
				break;
			case 1 :
				return SERIAL_STATUS_NOT_SUPPORTED;
				break;
			case 2 :
				SET_BIT(UCSRC, USBS);
				break;
			default :
				return SERIAL_STATUS_ARG_IS_INVALID;
		}
		return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t set_serial_mode(SerialPort_t* device, EnSerialMode_t mode){
	status_t result = sanity_check_device(device);
	if(result != SERIAL_STATUS_OK){
		return SERIAL_STATUS_ERROR;
	}

	if(APPLICATION_AVR == 0){
		switch(mode){
			case 0: // for UART
				switch(device->id){
					case 0:
						CLR_BIT(UCSR0C, UMSEL00);
						CLR_BIT(UCSR0C, UMSEL01);
						break;
					case 1:
						CLR_BIT(UCSR1C, UMSEL10);
						CLR_BIT(UCSR1C, UMSEL11);
						break;
					default:
						return SERIAL_STATUS_NOT_SUPPORTED;
				}
			case 1: //for USART
				switch(device->id){
					case 0:
						SET_BIT(UCSR0C, UMSEL00);
						CLR_BIT(UCSR0C, UMSEL01);
						break;
					case 1:
						SET_BIT(UCSR1C, UMSEL10);
						CLR_BIT(UCSR1C, UMSEL11);
						break;
					default:
						return SERIAL_STATUS_NOT_SUPPORTED;
				}
			default:
				return SERIAL_STATUS_ARG_IS_INVALID;
		}
		return SERIAL_STATUS_OK;
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		switch(mode){
			case 0:
				CLR_BIT(UCSRC, UMSEL0);
				CLR_BIT(UCSRC, UMSEL1);
				break;
			case 1:
				SET_BIT(UCSRC, UMSEL0);
				CLR_BIT(UCSRC, UMSEL1);
				break;
			default:
				return SERIAL_STATUS_ARG_IS_INVALID;
		}
		return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_ERROR;
}
status_t set_serial_frame(SerialPort_t* device, EnSerialFrame_t frame){
	status_t result = sanity_check_device(device);
	if(result != SERIAL_STATUS_OK){
		return SERIAL_STATUS_ERROR;
	}
	if(APPLICATION_AVR == 0){
		switch(device->id){
			case 0:
				switch(frame){
					case 0: //5 bit
						CLR_BIT(UCSR0C, UCSZ00);
						CLR_BIT(UCSR0C, UCSZ01);
						CLR_BIT(, UCSZ0);
						break;					cse 1: //6 bit
						SET_BIT(UCSR0C, UCSZ00;
						CLR_BIT(UCSR0C, UCSZ01);
						CLR_BIT(UCSR0B, UCSZ02);
						break;
					case 2: //7 bit
						CLR_BIT(UCSR0C, UCSZ00);
						SET_BIT(UCSR0C, UCSZ01);
						CLR_BIT(UCSR0B, UCSZ02);
						break;
					case 3: //8 bit
						SET_BIT(UCSR0C, UCSZ00);
						SET_BIT(UCSR0C, UCSZ01);
						CLR_BIT(UCSR0B, UCSZ02);
						break;
					default:
						return SERIAL_STATUS_NOT_SUPPORTED;
				}
				break;
			case 1:
				switch(frame){
					case 0: //5 bit
						CLR_BIT(UCSR1C, UCSZ10);
						CLR_BIT(UCSR1C, UCSZ11);
						CLR_BIT(UCSR1B, UCSZ12);
						break;
					case 1: //6 bit
						SET_BIT(UCSR1C, UCSZ10);
						CLR_BIT(UCSR1C, UCSZ11);
						CLR_BIT(UCSR1B, UCSZ12);
						break;
					case 2: //7 bit
						CLR_BIT(UCSR1C, UCSZ10);
						SET_BIT(UCSR1C, UCSZ11);
						CLR_BIT(UCSR1B, UCSZ12);
						break;
					case 3: //8 bit
						SET_BIT(UCSR1C, UCSZ10);
						SET_BIT(UCSR1C, UCSZ11);
						CLR_BIT(UCSR1B, UCSZ12);
						break;
					default:
						return SERIAL_STATUS_NOT_SUPPORTED;
				}
				break;
			default:
				return SERIAL_STATUS_NOT_SUPPORTED;
		}
		return SERIAL_STATUS_OK;
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		switch(frame){
			case 0: //5 bit
				CLR_BIT(UCSRC, UCSZ0);
				CLR_BIT(UCSRC, UCSZ1);
				CLR_BIT(UCSRB, UCSZ2);
				break;
			case 1: //6 bit
				SET_BIT(UCSRC, UCSZ0);
				CLR_BIT(UCSRC, UCSZ1);
				CLR_BIT(UCSRB, UCSZ2);
				break;
			case 2: //7 bit
				CLR_BIT(UCSRC, UCSZ0);
				SET_BIT(UCSRC, UCSZ1);
				CLR_BIT(UCSRB, UCSZ2);
				break;
			case 3: //8 bit
				SET_BIT(UCSRC, UCSZ0);
				SET_BIT(UCSRC, UCSZ1);
				CLR_BIT(UCSRB, UCSZ2);
				break;
			default:
				return SERIAL_STATUS_NOT_SUPPORTED;
	}
	return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;	
}

//__update_stopbit SerialPort_setStopBit  MODULENAME_verbNameAttribute
//$Package$_$ModuleName_$Verb
//$Package$_$ModuleName_set$Attribute
//$Package$_$ModuleName_get$Attribute
//Package = EmbeddedSystem
//ModuleName = SerialPort
/*
namespace package
{
	class ModuleName
	{
		public:
		//ctor
		ModuleName();		
		//dtor
		~ModuleName();
		public:
		status_t verb1(args);
		status_t verb2(args);
		status_t verb3(args);

		public:
		status_t setAttributeA(const atype& value);
		status_t getAttributeA(atype& value);

	}
}
*/


static status_t sanity_check_config(const SerialPortConfig_t* config){
	if(config == 0){
		return SERIAL_CONFIG_ARG_IS_NULL;
	}
    if(config->baud < enSerialBaud_9600 || config->baud > enSerialBaud_Max){
		return SERIAL_CONFIG_ARG_INVALID;
    }
    if(config->parity < enSerialParity_ODD || config->parity > enSerialParity_Max){
		return SERIAL_CONFIG_ARG_INVALID;
    }
    if(config->stopBit < enSerialStopBit_One || config->stopBit > enSerialStopBit_Max){
		return SERIAL_CONFIG_ARG_INVALID;
    }
	if(config->mode != enSerialMode_uart || config->mode != enSerialMode_usart){
		return SERIAL_CONFIG_ARG_INVALID
	}
	return SERIAL_STATUS_OK;
}

static status_t sanity_check_device(const SerialPort_t* device){
	if(device == MYNULL){
		return SERIAL_DEVICE_ARG_IS_NULL;
	}
	if(device == mydevices[device->id]){
		return SERIAL_STATUS_OK;
	}
	else {
		return SERIAL_STATUS_ERROR;
	}
}

SerialPort_t* SerialPort_new(SerialPortConfig_t* config, status_t* result)
{
	if(result == MYNULL){
		return SERIAL_STATUS_ARG_IS_NULL;
	}
	
	if(id >= MAX_PORT){
		*result = SERIAL_MAX_PORT_REACHED;
		return MYNULL;
	}

	//Sanity check
	*result = sanity_check_config(config);
	if(*result != SERIAL_STATUS_OK){
		return MYNULL;
	}

	//malloc and create a serial_port_device
	SerialPort_t* dev = (SerialPort_t *)malloc(sizeof(struct __serial_port_device));
	dev->id = id;

	*result = set_serial_baud(dev, config->baud);
	if(*result != SERIAL_STATUS_OK){
		free(dev);
		return MYNULL;
	}
	*result = set_serial_parity(dev, config->parity);
	if(*result != SERIAL_STATUS_OK){
		free(dev);
		return MYNULL;
	}
	*result = set_serial_stopbit(dev, config->stopBit);
	if(*result != SERIAL_STATUS_OK){
		free(dev);
		return MYNULL;
	}

	*result = set_serial_mode(dev, config->mode);
	if(*result != SERIAL_STATUS_OK){
		free(dev);
		return MYNULL;
	}

	*result = set_serial_frame(dev, config->frame);
	if(*result != SERIAL_STATUS_OK){
		free(dev);
		return MYNULL;
	}
	// // Mode select
	// CLR_BIT(UCSR0C, UMSEL00);
	// CLR_BIT(UCSR0C, UMSEL01);

	// //Frame size
	// SET_BIT(UCSR0C, UCSZ00);
	// SET_BIT(UCSR0C, UCSZ01);
	// CLR_BIT(UCSR0B, UCSZ02);

	//*result = SERIAL_STATUS_OK; 
	id++;
	mydevices[id] = dev;
	return dev;
}

status_t SerialPort_delete(SerialPort_t* device){
	if(device == 0){
		return SERIAL_STATUS_ERROR;
	}
	free(device);
	return SERIAL_STATUS_OK;
}

status_t SerialPort_open(SerialPort_t* device)
{
	//Sanity check
	status_t status = sanity_check_device(device);
	if(status != SERIAL_STATUS_OK){
		return status;
	}
	if(APPLICATION_AVR == 0){
		switch(device->id) {
			case 0 :
				if(IS_BIT_SET(UCSR0B, TXEN0) == 0){
					SET_BIT(UCSR0B, TXEN0);
				}
				if(IS_BIT_SET(UCSR0B, RXEN0) == 0){
					SET_BIT(UCSR0B, RXEN0);
				}
				break;
			case 1 :
				if(IS_BIT_SET(UCSR1B, TXEN1) == 0){
					SET_BIT(UCSR1B, TXEN1);
				}
				if(IS_BIT_SET(UCSR1B, RXEN1) == 0){
					SET_BIT(UCSR1B, RXEN1);
				}
			default :
				return SERIAL_STATUS_NOT_SUPPORTED;
		}
		return SERIAL_STATUS_OK;
	}

	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		if(IS_BIT_SET(UCSRB, TXEN) == 0){
			SET_BIT(UCSRB, TXEN);
		}
		if(IS_BIT_SET(UCSRB, RXEN) == 0){
			SET_BIT(UCSRB, RXEN);
		}
		return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t SerialPort_close(SerialPort_t* device)
{
	status_t status = sanity_check_device(device);
	if(status != SERIAL_STATUS_OK){
		return status;
	}
	if(APPLICATION_AVR == 0){
		switch(device->id){
			case 0:
				CLR_BIT(UCSR0B, TXEN0);
				CLR_BIT(UCSR0B, RXEN0);
				break;
			case 1:
				CLR_BIT(UCSR1B, TXEN1);
				CLR_BIT(UCSR1B, RXEN1);
				break;
			default:
				return SERIAL_STATUS_NOT_SUPPORTED;
		}
		return SERIAL_STATUS_OK;
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		CLR_BIT(UCSRB, TXEN);
		CLR_BIT(UCSRB, RXEN);
		return SERIAL_STATUS_OK;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t SerialPort_writeByte(const SerialPort_t* device, unsigned char data){

  status_t status = sanity_check_device(device);
	if(status != SERIAL_STATUS_OK){
		return status;
	}

	if(APPLICATION_AVR == 0){
		switch(device->id){
			case 0:
				if(IS_BIT_SET(UCSR0B, TXEN0)){
					while(IS_BIT_SET(UCSR0A, UDRE0)){};
					UDR0 = data;
					return SERIAL_STATUS_OK;
				}
				else{
					return SERIAL_STATUS_ERROR;
				}
				break;
			case 1:
				if(IS_BIT_SET(UCSR1B, TXEN1)){
					while(IS_BIT_SET(UCSR1A, UDRE1)){};
					UDR1 = data;
					return SERIAL_STATUS_OK;
				}
				else{
					return SERIAL_STATUS_ERROR;
				}
				break;
			default:
				return SERIAL_STATUS_NOT_SUPPORTED;
		}
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		if(IS_BIT_SET(UCSRB, TXEN)){
			while(IS_BIT_SET(UCSRA, UDRE)){};
			UDR = data;
			return SERIAL_STATUS_OK;
		}
		return SERIAL_STATUS_ERROR;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}

status_t SerialPort_readByte(const SerialPort_t* device, unsigned char* data){
  status_t status = sanity_check_device(device);
	if(status != SERIAL_STATUS_OK){
		return status;
	}
	if(APPLICATION_AVR == 0){
		switch(device->id){
			case 0:
				if(IS_BIT_SET(UCSR0B, RXEN0)){
					while(IS_BIT_SET(UCSR0A, RXC0)){};
					*data = UDR0;
					return SERIAL_STATUS_OK;
				}
				else{
					return SERIAL_STATUS_ERROR;
				}
				break;
			case 1:
				if(IS_BIT_SET(UCSR1B, RXEN1)){
					while(IS_BIT_SET(UCSR1A, RXC1)){};
					*data = UDR1;
					return SERIAL_STATUS_OK;
				}
				else{
					return SERIAL_STATUS_ERROR;
				}
			default:
				return SERIAL_STATUS_NOT_SUPPORTED;
		}
	}
	if(APPLICATION_AVR == 1 || APPLICATION_AVR == 2){
		if(IS_BIT_SET(UCSRB, RXEN)){
			while(IS_BIT_SET(UCSRA, RXC)){};
			*data = UDR;
			return SERIAL_STATUS_OK;
		}
		return SERIAL_STATUS_ERROR;
	}
	return SERIAL_STATUS_NOT_SUPPORTED;
}
