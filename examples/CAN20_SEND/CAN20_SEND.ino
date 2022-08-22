// example for send a can 2.0 frame
// SEND A CAN20 FRAME EXAMPLE OF SERIAL CAN MODULE
// void can_send(unsigned long id, unsigned char ext, unsigned char rtr, unsigned char fdf, unsigned char len, unsigned char *dta);
// SUPPORT: info@longan-labs.cc
#include "Serial_CAN_FD.h"
#include <SoftwareSerial.h>

#define can_tx  2           // tx of serial can module connect to D2
#define can_rx  3           // rx of serial can module connect to D3

SoftwareSerial can_serial(can_tx, can_rx);

#define uart_can    can_serial

void uart_init(unsigned long baudrate)
{
    uart_can.begin(baudrate);
}

void uart_write(unsigned char c)
{
    uart_can.write(c);
}

unsigned char uart_read()
{
    return uart_can.read();
}

int uart_available()
{
    return uart_can.available();
}

void setup()
{
    Serial.begin(115200);
    uart_init(9600);
    can_speed_20(5000000);          // set can bus baudrate to 500k
}

void loop()
{
    unsigned long __id = 0x01;      // can id
    unsigned char __ext = 0;        // extended frame or standard frame
    unsigned char __rtr = 0;        // remote frame or data frame
    unsigned char __fdf = 0;        // can fd or can 2.0
    unsigned char __len = 8;        // data length
    unsigned char __dta[8] = {1, 2, 3, 4, 5, 6, 7, 8};      // data
    
    can_send(__id, __ext, __rtr, __fdf, __len, __dta);
    delay(100);
}

// END FILE