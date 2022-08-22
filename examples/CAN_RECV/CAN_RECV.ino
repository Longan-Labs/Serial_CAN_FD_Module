// RECV EXAMPLE OF SERIAL CAN MODULE
// unsigned int read_can(unsigned long *id, unsigned char *ext, unsigned char *rtr, unsigned char *fdf, unsigned char *len, unsigned char *dta);
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
    can_speed_20(5000000);                   // set can bus baudrate to 500k
}

unsigned long __id = 0;
unsigned char __ext = 0;
unsigned char __rtr = 0;
unsigned char __fdf = 0;
unsigned char __len = 0;
unsigned char __dta[8];


void loop()
{

    if(read_can(&__id, &__ext, &__rtr, &__fdf, &__len, __dta))
    {
        Serial.print("GET DATA FROM: 0x");
        Serial.println(__id, HEX);
        Serial.print("EXT = ");
        Serial.println(__ext);
        Serial.print("RTR = ");
        Serial.println(__rtr);
        Serial.print("FDF = ");
        Serial.println(__fdf);
        Serial.print("LEN = ");
        Serial.println(__len);
        
        for(int i=0; i<__len; i++)
        {
            Serial.print(__dta[i]);
            Serial.print(' ');
        }
        Serial.println("");
        
    }

}

// END FILE