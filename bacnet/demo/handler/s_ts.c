/**************************************************************************
*
* Copyright (C) 2005 Steve Karg <skarg@users.sourceforge.net>
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
*****************************************************************************************
*
*   Modifications Copyright (C) 2017 BACnet Interoperability Testing Services, Inc.
*
*   July 1, 2017    BITS    Modifications to this file have been made in compliance
*                           with original licensing.
*
*   This file contains changes made by BACnet Interoperability Testing
*   Services, Inc. These changes are subject to the permissions,
*   warranty terms and limitations above.
*   For more information: info@bac-test.com
*   For access to source code:  info@bac-test.com
*          or      www.github.com/bacnettesting/bacnet-stack
*
****************************************************************************************/

#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "configProj.h"
#include "txbuf.h"
#include "bacdef.h"
#include "bacdcode.h"
#include "address.h"
#include "tsm.h"
#include "npdu.h"
#include "apdu.h"
#include "device.h"
#include "datalink.h"
#include "dcc.h"
#include "timesync.h"
/* some demo stuff needed */
#include "handlers.h"
#include "txbuf.h"
#include "client.h"

/** @file s_ts.c  Send TimeSync requests. */

#if BACNET_SVC_TS_A
/**
 * Sends a TimeSync message to a specific destination
 *
 * @param dest - #BACNET_ADDRESS - the specific destination
 * @param bdate - #BACNET_DATE
 * @param btime - #BACNET_TIME
 */

void Send_TimeSync_Remote(
    BACNET_ADDRESS * dest,
    BACNET_DATE * bdate,
    BACNET_TIME * btime)
{
    int len = 0;
    int pdu_len = 0;
    int bytes_sent = 0;
    BACNET_NPCI_DATA npci_data;
    BACNET_ADDRESS my_address;

    if (!dcc_communication_enabled())
        return;

    datalink_get_my_address(&my_address);
    /* encode the NPDU portion of the packet */
    npdu_setup_npci_data(&npci_data, false, MESSAGE_PRIORITY_NORMAL);
    pdu_len =
        npdu_encode_pdu(&Handler_Transmit_Buffer[0], dest, &my_address,
        &npci_data);
    /* encode the APDU portion of the packet */
    len =
        timesync_encode_apdu(&Handler_Transmit_Buffer[pdu_len], bdate, btime);
    pdu_len += len;
    /* send it out the datalink */
    bytes_sent =
        datalink_send_pdu(dest, &npci_data, &Handler_Transmit_Buffer[0],
        pdu_len);
#if PRINT_ENABLED
    if (bytes_sent <= 0)
        fprintf(stderr, "Failed to Send Time-Synchronization Request (%s)!\n",
            strerror(errno));
#endif
}

/**
 * Sends a TimeSync message as a broadcast
 *
 * @param bdate - #BACNET_DATE
 * @param btime - #BACNET_TIME
 */
void Send_TimeSync(
    BACNET_DATE * bdate,
    BACNET_TIME * btime)
{
    BACNET_ADDRESS dest;

    datalink_get_broadcast_address(&dest);
    Send_TimeSync_Remote(&dest, bdate, btime);
}

/**
 * Sends a UTC TimeSync message to a specific destination
 *
 * @param dest - #BACNET_ADDRESS - the specific destination
 * @param bdate - #BACNET_DATE
 * @param btime - #BACNET_TIME
 */
void Send_TimeSyncUTC_Remote(
    BACNET_ADDRESS * dest,
    BACNET_DATE * bdate,
    BACNET_TIME * btime)
{
    int len ;
    int pdu_len ;
    int bytes_sent = 0;
    BACNET_NPCI_DATA npci_data;
    BACNET_ADDRESS my_address;

    if (!dcc_communication_enabled())
        return;

    datalink_get_my_address(&my_address);
    /* encode the NPDU portion of the packet */
    npdu_setup_npci_data(&npci_data, false, MESSAGE_PRIORITY_NORMAL);
    pdu_len =
        npdu_encode_pdu(&Handler_Transmit_Buffer[0], dest, &my_address,
        &npci_data);
    /* encode the APDU portion of the packet */
    len =
        timesync_utc_encode_apdu(&Handler_Transmit_Buffer[pdu_len],
        bdate, btime);
    pdu_len += len;
    bytes_sent =
        datalink_send_pdu(dest, &npci_data, &Handler_Transmit_Buffer[0],
        pdu_len);

}

/**
 * Sends a UTC TimeSync message as a broadcast
 *
 * @param bdate - #BACNET_DATE
 * @param btime - #BACNET_TIME
 */
void Send_TimeSyncUTC(
    BACNET_DATE * bdate,
    BACNET_TIME * btime)
{
    BACNET_ADDRESS dest;

    datalink_get_broadcast_address(&dest);
    Send_TimeSyncUTC_Remote(&dest, bdate, btime);
}

/**
 * Sends a UTC TimeSync message using the local time from the device.
 */
void Send_TimeSyncUTC_Device(void)
{
    int32_t utc_offset_minutes = 0;
    bool dst = false;
    BACNET_DATE_TIME local_time;
    BACNET_DATE_TIME utc_time;

    Device_getCurrentDateTime(&local_time);
    dst = Device_Daylight_Savings_Status();
    utc_offset_minutes = Device_UTC_Offset();
    datetime_copy(&utc_time, &local_time);
    datetime_add_minutes(&utc_time, utc_offset_minutes);
    if (dst) {
        datetime_add_minutes(&utc_time, -60);
    }
    Send_TimeSyncUTC(&utc_time.date, &utc_time.time);
}

/**
 * Sends a TimeSync message using the local time from the device.
 */
void Send_TimeSync_Device(void)
{
    BACNET_DATE_TIME local_time;

    Device_getCurrentDateTime(&local_time);
    Send_TimeSync(&local_time.date, &local_time.time);
}

#endif //#if BACNET_SVC_TS_A