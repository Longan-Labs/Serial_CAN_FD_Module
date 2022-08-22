# Longan Labs CANBed Dual Arduino Library

[![Actions Status](https://github.com/arduino/arduino-cli-example/workflows/test/badge.svg)](https://github.com/arduino/arduino-cli-example/actions)
[![Spell Check](https://github.com/arduino/compile-sketches/workflows/Spell%20Check/badge.svg)](https://github.com/arduino/compile-sketches/actions?workflow=Spell+Check)
[![codecov](https://codecov.io/gh/arduino/compile-sketches/branch/main/graph/badge.svg?token=Uv6f1ebMZ4)](https://codecov.io/gh/arduino/compile-sketches)

Arduino library for Serial CAN-FD Module.

With this library, you can,

1. Send a CAN2.0 frame
2. Receive a CAN2.0 frame
3. Send a CAN FD frame
4. Receive a CAN FD frame

## Installation

1. [Download the library](https://github.com/Longan-Labs/Serial_CAN_FD_Module/archive/refs/heads/master.zip)
2. Extract the zip file
3. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Respository Contents

* [**/examples**](./examples) - Example sketches for the library (.ino). Run these from the Arduino IDE.
* [**/src**](./src) - Source files for the library (.cpp, .h).
* [**keywords.txt**](./keywords.txt) - Keywords from this library that will be highlighted in the Arduino IDE.
* [**library.properties**](./library.properties) - General library properties for the Arduino package manager.

## Functions

- can_speed_fd
- can_speed_20
- can_send
- read_can
- set_mask_filt
- set_baudrate

## Examples

here are many examples implemented in this library. One of the examples is below. You can find other examples [here](./examples)

```Cpp
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
```

## Get a Dev Board

If you need a Dev board, plese try,

- [Grove - CAN BUS Module based on GD32E103](https://www.seeedstudio.com/Grove-CAN-BUS-Module-based-on-GD32E103-p-5456.html)


## License

```
MIT License

Copyright (c) 2018 @ Longan Labs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Contact us

If you have any question, please feel free to contact [support@longan-labs.cc](support@longan-labs.cc)
