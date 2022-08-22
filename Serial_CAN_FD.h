#ifndef __SERIAL_CAN_FD_H__
#define __SERIAL_CAN_FD_H__

#include <Arduino.h>

unsigned long char2long(unsigned char *str);
void long2char(unsigned long num, unsigned char *str);
unsigned int CrcCalculate(unsigned char Byte, unsigned int _CRC);
unsigned int calCRC(unsigned char *str);
unsigned char checkCRC(unsigned char *str);

void can_send(unsigned long id, unsigned char ext, unsigned char rtr, unsigned char fdf, unsigned char len, unsigned char *dta);
void strProcess(int num);
void checkData();
void serialProcess();
void dtaProcess(int len, unsigned char *dta);

void can_speed_fd(unsigned long speed_20, unsigned long speed_fd);
void can_speed_20(unsigned long speed_20);
void can_send(unsigned long id, unsigned char ext, unsigned char rtr, unsigned char fdf, unsigned char len, unsigned char *dta);
int read_can(unsigned long *id, unsigned char *ext, unsigned char *rtr, unsigned char *fdf, unsigned char *len, unsigned char *dta);
void set_mask_filt(unsigned char num, unsigned char ext, unsigned long mask, unsigned long filt);
void set_baudrate(unsigned long __baud);

#endif