/**************************************************************************
*
* Copyright (C) 2007 Steve Karg <skarg@users.sourceforge.net>
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
*********************************************************************/

#ifndef RS485_H
#define RS485_H

#include <stdint.h>

#define MX_RS485_PORTS    3

typedef struct {
  uint8_t   hwPortId;
} RS485_PORT_INFO ;


void RS485_Initialize(
                     volatile RS485_PORT_INFO  *portInfo,
                     uint32_t baud);

void RS485_Send_Frame(
                      volatile RS485_PORT_INFO *portInfo,
                      uint8_t * buffer,       /* data to send */
                      uint16_t nbytes);       /* number of bytes of data */

bool RS485_ReceiveError(
                        volatile RS485_PORT_INFO  *portInfo);

bool RS485_StillTransmitting(
                        volatile RS485_PORT_INFO  *portInfo);

// optimizing as much as possible, these functions are VERY busy
unsigned int RS485_isDataAvailable(
                         volatile RS485_PORT_INFO  *portInfo);

bool RS485_getDataAvailable(
                         volatile RS485_PORT_INFO  *portInfo,
                         volatile uint8_t * data);

#if 0
void RS485_Turnaround_Delay(
                            volatile RS485_PORT_INFO  *portInfo);
#endif

uint32_t RS485_Get_Baud_Rate(
                             volatile RS485_PORT_INFO  *portInfo);

bool RS485_Set_Baud_Rate(
                         volatile RS485_PORT_INFO  *portInfo,
                         uint32_t baud);

#endif