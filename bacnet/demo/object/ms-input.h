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
*  2018.07.04 EKH Diffed in hints from Binary Value for future reference
*
****************************************************************************************/

#ifndef MS_INPUT_H
#define MS_INPUT_H
#include "configProj.h"

#if (BACNET_USE_OBJECT_MULTISTATE_INPUT == 1 )
#include <stdbool.h>
#include <stdint.h>
#include "bacdef.h"
#include "rp.h"
#include "wp.h"
#include "BACnetObject.h"

#if (INTRINSIC_REPORTING_B == 1)
#include "nc.h"
#include "getevent.h"
#include "alarm_ack.h"
// Deprecated since Rev 13    #include "get_alarm_sum.h"
#endif

/* how many states? 1 to 254 states - 0 is not allowed. */
#ifndef MULTISTATE_NUMBER_OF_STATES
#define MULTISTATE_NUMBER_OF_STATES (5)
#endif


typedef struct {

    BACNET_OBJECT   common;         // must be first field in structure due to llist

    BACNET_EVENT_STATE Event_State;                 // Event_State is a required property
    uint16_t Present_Value;
    uint16_t shadow_Present_Value;

    // todo 2-use malloc, linked lists, etc.
    char State_Text[MULTISTATE_NUMBER_OF_STATES][64];

    bool Out_Of_Service;
    BACNET_RELIABILITY Reliability;
    BACNET_RELIABILITY shadowReliability;

#if (BACNET_SVC_COV_B == 1)
    uint16_t Prior_Value;
    bool Changed;
    bool prior_OOS;
#endif

#if (INTRINSIC_REPORTING_B == 1)
    uint32_t Time_Delay;
    uint32_t Notification_Class;
    int High_Limit;
    int Low_Limit;
    unsigned Deadband;
    unsigned Limit_Enable : 2;
    unsigned Event_Enable : 3;
    BACNET_NOTIFY_TYPE Notify_Type;
    ACKED_INFO Acked_Transitions[MAX_BACNET_EVENT_TRANSITION];
    BACNET_DATE_TIME Event_Time_Stamps[MAX_BACNET_EVENT_TRANSITION];
    /* time to generate event notification */
    uint32_t Remaining_Time_Delay;
    /* AckNotification informations */
    ACK_NOTIFICATION Ack_notify_data;
#endif

} MULTISTATE_INPUT_DESCR;


void Multistate_Input_Property_Lists(
    const BACNET_PROPERTY_ID **pRequired,
    const BACNET_PROPERTY_ID **pOptional,
    const BACNET_PROPERTY_ID **pProprietary);

bool Multistate_Input_Valid_Instance(
    uint32_t object_instance);

unsigned Multistate_Input_Count(
    void);

uint32_t Multistate_Input_Index_To_Instance(
    unsigned index);
// making static
//unsigned Multistate_Input_Instance_To_Index(
//    const uint32_t object_instance);

int Multistate_Input_Read_Property(
    BACNET_READ_PROPERTY_DATA * rpdata);

bool Multistate_Input_Write_Property(
    BACNET_WRITE_PROPERTY_DATA * wp_data);

/* optional API */
bool Multistate_Input_Object_Instance_Add(
    uint32_t instance);

bool Multistate_Input_Object_Name(
    uint32_t object_instance,
    BACNET_CHARACTER_STRING * object_name);

bool Multistate_Input_Name_Set(
    uint32_t object_instance,
    char *new_name);

uint32_t Multistate_Input_Present_Value(
    uint32_t object_instance);

//bool Multistate_Input_Present_Value_Set(
//    uint32_t object_instance,
//    uint32_t value);

bool Multistate_Input_Change_Of_Value(
    uint32_t instance);
void Multistate_Input_Change_Of_Value_Clear(
    uint32_t instance);
bool Multistate_Input_Encode_Value_List(
    uint32_t object_instance,
    BACNET_PROPERTY_VALUE * value_list);

bool Multistate_Input_Out_Of_Service(
    uint32_t object_instance);

//void Multistate_Input_Out_Of_Service_Set(
//    uint32_t object_instance,
//    bool value);

char *Multistate_Input_Description(
    uint32_t instance);

bool Multistate_Input_Description_Set(
    uint32_t object_instance,
    char *text_string);

BACNET_RELIABILITY Multistate_Input_Reliability(
    uint32_t object_instance);


//bool Multistate_Input_Reliability_Set(
//    uint32_t object_instance,
//    BACNET_RELIABILITY value);

bool Multistate_Input_State_Text_Set(
    uint32_t object_instance,
    uint32_t state_index,
    char *new_name);

bool Multistate_Input_Max_States_Set(
    uint32_t instance,
    uint32_t max_states_requested);

//char *Multistate_Input_State_Text(
//    uint32_t object_instance,
//    uint32_t state_index);

bool Multistate_Input_Create(
    const uint32_t object_instance,
    const char *name);

bool Multistate_Input_Delete(
    uint32_t object_instance);

void Multistate_Input_Cleanup(
    void);

void Multistate_Input_Init(
    void);


#ifdef TEST
#include "ctest.h"
void testMultistateInput(
    Test * pTest);
#endif

#endif
#endif  // XXX_H include guard