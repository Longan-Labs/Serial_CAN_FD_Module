
#include <stdio.h>
#include "Serial_CAN_FD.h"

extern void uart_init(unsigned long baudrate);
extern void uart_write(unsigned char c);
extern unsigned char uart_read();
extern int uart_available();

int dtaLen = 0;
unsigned char dtaCan[100];


unsigned long char2long(unsigned char *str)
{
    unsigned long num = 0;
    memcpy((unsigned char *)(&num), str, 4);
    return num;
}

void long2char(unsigned long num, unsigned char *str)
{
    memcpy(str, (unsigned char*)(&num), 4);
}

unsigned int CrcCalculate(unsigned char Byte, unsigned int _CRC)
{
    unsigned char Carry;
    int Bit_Index;
    _CRC = _CRC ^ (Byte & 0xFF);
    for (Bit_Index = 0; Bit_Index < 8; Bit_Index++)
    {
        Carry = _CRC & 0x0001;
        _CRC = _CRC >> 1;
        if (Carry)
        _CRC = _CRC ^ 0xA001;
    }
    return _CRC;
}

unsigned int calCRC(unsigned char *str)
{
    unsigned int __crc = 0xffff;
    int i=0;

    for(i=0; i < str[1]; i++)
    {
        __crc = CrcCalculate(str[i+2], __crc);
    }
    return __crc;
}

unsigned char checkCRC(unsigned char *str)
{
    unsigned int __crc = calCRC(str);
    unsigned int __crc0 = str[3+str[1]];

    __crc0 <<= 8;
    __crc0 |= str[2+str[1]];

    return (__crc == __crc0);
    return 0;
}


void can_send(unsigned long id, unsigned char ext, unsigned char rtr, unsigned char fdf, unsigned char len, unsigned char *dta)
{
    unsigned char str[80];
    str[0] = 0xAA;
    str[1] = len+9;
    str[2] = 0x01;
    long2char(id, &str[3]);
    str[7] = ext;
    str[8] = rtr;
    str[9] = fdf;
    str[10] = len;
    for(int i=0; i<len; i++)
    {
        str[11+i] = dta[i];
    }

    unsigned int crc = calCRC(str);
    str[11+len] = crc & 0xff;
    str[12+len] = (crc>>8) & 0xff;

    for(int i=0; i<(13+len); i++)
    {
        uart_write(str[i]);
    }
}

void can_speed_fd(unsigned long speed_20, unsigned long speed_fd)
{
    unsigned char str[80];
    str[0] = 0xAA;
    str[1] = 0x09;
    str[2] = 0x02;
    long2char(speed_20, &str[3]);
    long2char(speed_fd, &str[7]);


    unsigned int crc = calCRC(str);
    str[str[1]+2] = crc & 0xff;
    str[str[1]+3] = (crc>>8) & 0xff;

    for(int i=0; i<(4+str[1]); i++)
    {
        uart_write(str[i]);
    }
}

void can_speed_20(unsigned long speed_20)
{
    can_speed_fd(speed_20, 4000000);
}

void strProcess(int num)
{
    if(dtaLen >= num)
    {
        unsigned char __str[500];
        memcpy(__str, dtaCan, dtaLen);
        memcpy(dtaCan, &__str[num], dtaLen-num);
        dtaLen = dtaLen-num;
    }
}


void checkData()
{
    int __len = 0;
    unsigned char __dta[100];
    int i=0;

    for(i=0; i<dtaLen; i++)
    {
        if(dtaCan[0] != 0xAA)
        {
            strProcess(1);
        }
        else break;
    }

    if(dtaLen>2)
    {
        if(dtaLen >= (dtaCan[1]+4))
        {
            __len = dtaLen;
            memcpy(__dta, dtaCan, __len);
            strProcess(__len);
            dtaProcess(__len, __dta);
        }
    }
}

void serialProcess()
{
    while(uart_available())
    {
        dtaCan[dtaLen++] = uart_read();
        //Serial.write(dtaCan[dtaLen-1]);
    }
}

void dtaProcess(int len, unsigned char *dta)
{
    int i=0;
    unsigned long tmp = 0;
    int __crc = checkCRC(dta);

    if(__crc)
    {
        Serial.println("get dta crc ok");
    }
}


int read_can(unsigned long *id, unsigned char *ext, unsigned char *rtr, unsigned char *fdf, unsigned char *len, unsigned char *dta)
{
    serialProcess();
    
    if(dtaLen == 0)return 0;
    int __len = 0;
    unsigned char __dta[100];
    int i=0;

    for(i=0; i<dtaLen; i++)
    {
        if(dtaCan[0] != 0xAA)
        {
            strProcess(1);
        }
        else break;
    }

    if(dtaLen>2)
    {
        if(dtaLen >= (dtaCan[1]+4))
        {
  
            __len = dtaLen;
            memcpy(__dta, dtaCan, __len);

            strProcess(__len);
  
            int __crc = checkCRC(__dta);
            if(__crc)
            {
                *id = char2long(&__dta[3]);
                *ext = __dta[7];
                *rtr = __dta[8];
                *fdf = __dta[9];
                *len = __dta[10];
                
                for(int i=0; i<*len; i++)
                {
                    dta[i] = __dta[11+i];
                }
                return 1;
            }
            else return 0;
        }
    }
    
    return 0;
}

void set_mask_filt(unsigned char num, unsigned char ext, unsigned long mask, unsigned long filt)
{
    if(num > 3)return;
    
    unsigned char str[15];
    str[0] = 0xAA;
    str[1] = 11;
    str[2] = 0x03+num;
    str[3] = 1;
    str[4] = ext;
   
    long2char(mask, &str[5]);
    long2char(filt, &str[9]);
    
    unsigned int crc = calCRC(str);
    str[13] = crc & 0xff;
    str[14] = (crc>>8) & 0xff;

    for(int i=0; i<15; i++)
    {
        uart_write(str[i]);
    }
}

void set_baudrate(unsigned long __baud)
{

    unsigned char str[15];
    str[0] = 0xAA;
    str[1] = 5;
    str[2] = 7;
   
    long2char(__baud, &str[3]);
    
    unsigned int crc = calCRC(str);
    str[7] = crc & 0xff;
    str[8] = (crc>>8) & 0xff;

    for(int i=0; i<9; i++)
    {
        uart_write(str[i]);
    }
    
    delay(10);
    uart_init(__baud);
}

// END FILE