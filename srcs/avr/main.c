#include <avr/io.h>
#include "private_avr_serial.h"

 int main(){
     SerialPortConfig_t config;
     status_t result = SERIAL_STATUS_ERROR;
     config.baud = enSerialBaud_9600;
     config.parity = enSerialParity_Even;
     config.stopBit = enSerialStopBit_One;
     config.mode = enSerialMode_uart;
     config.frame = enSerialFrame_8bit;

     SerialPort_t * dev = SerialPort_new(&config, &result);
     if(result != SERIAL_STATUS_OK){
         return -1;
     }
    result = SerialPort_open(dev);
    if(result != SERIAL_STATUS_OK){
        return -1;
    }
    result = SerialPort_writeByte(dev, '1');
 }