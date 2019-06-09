/**************************************************************************
*
* Copyright (C) 2006 Steve Karg <skarg@users.sourceforge.net>
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

#ifndef CLIENT_H
#define CLIENT_H

#include <stdint.h>
#include "event.h"
//#include "ptransfer.h"
//
//
///* unconfirmed requests */

void Send_I_Am(
    uint8_t * buffer);

//    void Send_I_Am_To_Network(
//        BACNET_ADDRESS * target_address,
//        uint32_t device_id,
//        unsigned int max_apdu,
//        int segmentation,
//        uint16_t vendor_id);
//    int iam_encode_pdu(
//        uint8_t * buffer,
//        BACNET_ADDRESS * dest,
//        BACNET_NPCI_DATA * npci_data);

void Send_I_Am_Unicast(
    uint8_t * buffer,
    BACNET_ADDRESS * src);

//    int iam_unicast_encode_pdu(
//        uint8_t * buffer,
//        BACNET_ADDRESS * src,
//        BACNET_ADDRESS * dest,
//        BACNET_NPCI_DATA * npci_data);

void Send_WhoIs(
    int32_t low_limit,
    int32_t high_limit);

//    void Send_WhoIs_Global(
//        int32_t low_limit,
//        int32_t high_limit);
//
//    void Send_WhoIs_Local(
//        int32_t low_limit,
//        int32_t high_limit);
//
//    void Send_WhoIs_Remote(
//        BACNET_ADDRESS * target_address,
//        int32_t low_limit,
//        int32_t high_limit);
//
//    void Send_WhoIs_To_Network(
//        BACNET_ADDRESS * target_address,
//        int32_t low_limit,
//        int32_t high_limit);
//
//    void Send_WhoHas_Object(
//        int32_t low_limit,
//        int32_t high_limit,
//        BACNET_OBJECT_TYPE object_type,
//        uint32_t object_instance);

void Send_WhoHas_Name(
    int32_t low_limit,
    int32_t high_limit,
    const char *object_name);

void Send_I_Have(
    uint32_t device_id,
    BACNET_OBJECT_TYPE object_type,
    uint32_t object_instance,
    BACNET_CHARACTER_STRING * object_name);

//    int Send_UCOV_Notify(
//        uint8_t * buffer,
//        unsigned buffer_len,
//        BACNET_COV_DATA * cov_data);
//    int ucov_notify_encode_pdu(
//        uint8_t * buffer,
//        unsigned buffer_len,
//        BACNET_ADDRESS * dest,
//        BACNET_NPCI_DATA * npci_data,
//        BACNET_COV_DATA * cov_data);
//    uint8_t Send_COV_Subscribe(
//        uint32_t device_id,
//        BACNET_SUBSCRIBE_COV_DATA * cov_data);
//
///* returns the invoke ID for confirmed request, or 0 if failed */
//    uint8_t Send_GetEvent(
//        BACNET_ADDRESS * target_address,
//        BACNET_OBJECT_ID *lastReceivedObjectIdentifier);
//    uint8_t Send_GetEvent_Global(void);
//
///* returns the invoke ID for confirmed request, or 0 if failed */
//    uint8_t Send_Read_Property_Request_Address(
//        BACNET_ADDRESS * dest,
//        uint16_t max_apdu,
//        BACNET_OBJECT_TYPE object_type,
//        uint32_t object_instance,
//        BACNET_PROPERTY_ID object_property,
//        uint32_t array_index);
//    uint8_t Send_Read_Property_Request(
//        uint32_t device_id,     /* destination device */
//        BACNET_OBJECT_TYPE object_type,
//        uint32_t object_instance,
//        BACNET_PROPERTY_ID object_property,
//        uint32_t array_index);
//    uint8_t Send_Read_Property_Multiple_Request(
//        uint8_t * pdu,
//        size_t max_pdu,
//        uint32_t device_id,     /* destination device */
//        BACNET_READ_ACCESS_DATA * read_access_data);
//
///* returns the invoke ID for confirmed request, or 0 if failed */
//    uint8_t Send_Write_Property_Request(
//        uint32_t device_id,     /* destination device */
//        BACNET_OBJECT_TYPE object_type,
//        uint32_t object_instance,
//        BACNET_PROPERTY_ID object_property,
//        BACNET_APPLICATION_DATA_VALUE * object_value,
//        uint8_t priority,
//        uint32_t array_index);
//    uint8_t Send_Write_Property_Request_Data(
//        uint32_t device_id,
//        BACNET_OBJECT_TYPE object_type,
//        uint32_t object_instance,
//        BACNET_PROPERTY_ID object_property,
//        uint8_t * application_data,
//        int application_data_len,
//        uint8_t priority,
//        uint32_t array_index);
//    uint8_t Send_Write_Property_Multiple_Request_Data(
//        uint8_t * pdu,
//        size_t max_pdu,
//        uint32_t device_id,
//        BACNET_WRITE_ACCESS_DATA * write_access_data);
//
///* returns the invoke ID for confirmed request, or 0 if failed */
//    uint8_t Send_Reinitialize_Device_Request(
//        uint32_t device_id,
//        BACNET_REINITIALIZED_STATE state,
//        char *password);
//
///* returns the invoke ID for confirmed request, or 0 if failed */
//    uint8_t Send_Device_Communication_Control_Request(
//        uint32_t device_id,
//        uint16_t timeDuration,  /* 0=optional */
//        BACNET_COMMUNICATION_ENABLE_DISABLE state,
//        char *password);        /* NULL=optional */
//
//    void Send_TimeSync(
//        BACNET_DATE * bdate,
//        BACNET_TIME * btime);
//
//    void Send_TimeSync_Remote(
//        BACNET_ADDRESS * dest,
//        BACNET_DATE * bdate,
//        BACNET_TIME * btime);
//
//    void Send_TimeSyncUTC(
//        BACNET_DATE * bdate,
//        BACNET_TIME * btime);
//    void Send_TimeSyncUTC_Remote(
//        BACNET_ADDRESS * dest,
//        BACNET_DATE * bdate,
//        BACNET_TIME * btime);
//    void Send_TimeSyncUTC_Device(void);
//    void Send_TimeSync_Device(void);
//
//    uint8_t Send_Atomic_Read_File_Stream(
//        uint32_t device_id,
//        uint32_t file_instance,
//        int fileStartPosition,
//        unsigned requestedOctetCount);
//    uint8_t Send_Atomic_Write_File_Stream(
//        uint32_t device_id,
//        uint32_t file_instance,
//        int fileStartPosition,
//        BACNET_OCTET_STRING * fileData);

#if 0
int Send_UEvent_Notify(
    uint8_t *buffer,
    BACNET_EVENT_NOTIFICATION_DATA *data,
    BACNET_ADDRESS * dest);

uint8_t Send_CEvent_Notify(
    uint32_t device_id,
    BACNET_EVENT_NOTIFICATION_DATA *data);
#endif

//    int Send_Network_Layer_Message(
//        BACNET_NETWORK_MESSAGE_TYPE network_message_type,
//        BACNET_ADDRESS * dst,
//        int *iArgs);
//    void Send_Who_Is_Router_To_Network(
//        BACNET_ADDRESS * dst,
//        int dnet);
//    void Send_I_Am_Router_To_Network(
//        const int DNET_list[]);
//    void Send_Reject_Message_To_Network(
//        BACNET_ADDRESS * dst,
//        uint8_t reject_reason,
//        int dnet);
//    void Send_Initialize_Routing_Table(
//        BACNET_ADDRESS * dst,
//        const int DNET_list[]);
//    void Send_Initialize_Routing_Table_Ack(
//        BACNET_ADDRESS * dst,
//        const int DNET_list[]);
//
//    uint8_t Send_Life_Safety_Operation_Data(
//        uint32_t device_id,
//        BACNET_LSO_DATA * data);
//    uint8_t Send_Alarm_Acknowledgement(
//        uint32_t device_id,
//        BACNET_ALARM_ACK_DATA * data);
//
//    int Send_UnconfirmedPrivateTransfer(
//        BACNET_ADDRESS * dest,
//        BACNET_PRIVATE_TRANSFER_DATA * private_data);
//
//    uint8_t Send_Get_Alarm_Summary_Address(
//        BACNET_ADDRESS *dest,
//        uint16_t max_apdu);
//
//    uint8_t Send_Get_Alarm_Summary(
//        uint32_t device_id);
//
//    uint8_t Send_Get_Event_Information_Address(
//        BACNET_ADDRESS *dest,
//        uint16_t max_apdu,
//        BACNET_OBJECT_ID * lastReceivedObjectIdentifier);
//
//    uint8_t Send_Get_Event_Information(
//        uint32_t device_id,
//        BACNET_OBJECT_ID * lastReceivedObjectIdentifier);
//
//    int Send_Abort_To_Network(
//        uint8_t * buffer,
//        BACNET_ADDRESS *dest,
//        uint8_t invoke_id,
//        BACNET_ABORT_REASON reason,
//        bool server);
//
//    int abort_encode_pdu(
//        uint8_t * buffer,
//        BACNET_ADDRESS * dest,
//        BACNET_ADDRESS * src,
//        BACNET_NPCI_DATA * npci_data,
//        uint8_t invoke_id,
//        BACNET_ABORT_REASON reason,
//        bool server);
//
//    int Send_Error_To_Network(
//        uint8_t * buffer,
//        BACNET_ADDRESS *dest,
//        uint8_t invoke_id,
//        BACNET_CONFIRMED_SERVICE service,
//        BACNET_ERROR_CLASS error_class,
//        BACNET_ERROR_CODE error_code);
//
//    int error_encode_pdu(
//        uint8_t * buffer,
//        BACNET_ADDRESS * dest,
//        BACNET_ADDRESS * src,
//        BACNET_NPCI_DATA * npci_data,
//        uint8_t invoke_id,
//        BACNET_CONFIRMED_SERVICE service,
//        BACNET_ERROR_CLASS error_class,
//        BACNET_ERROR_CODE error_code);

#endif