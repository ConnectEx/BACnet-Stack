/****************************************************************************************
*
*   Copyright (C) 2018 BACnet Interoperability Testing Services, Inc.
*
*       <info@bac-test.com>
*
*   This program is free software : you can redistribute it and/or modify
*   it under the terms of the GNU Lesser General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
*   GNU Lesser General Public License for more details.
*
*   You should have received a copy of the GNU Lesser General Public License
*   along with this program.If not, see <http://www.gnu.org/licenses/>.
*
*   As a special exception, if other files instantiate templates or
*   use macros or inline functions from this file, or you compile
*   this file and link it with other works to produce a work based
*   on this file, this file does not by itself cause the resulting
*   work to be covered by the GNU General Public License. However
*   the source code for this file must still be made available in
*   accordance with section (3) of the GNU General Public License.
*
*   For more information : info@bac-test.com
*
*   For access to source code :
*
*       info@bac-test.com
*           or
*       www.github.com/bacnettesting/bacnet-stack
*
****************************************************************************************/

#pragma once

#undef _MSC_VER

#include <stdio.h>

#include <pthread.h>

#define OS_LAYER_LINUX      

typedef unsigned uint;

typedef int bitsThreadVar;
void bitsCreateThread(void(*threadFunc)(void *arg), void *argListPtr);

#define bitsDetachThread(threadVar)
#define bitsThreadFunction(threadFuncName,argList)  void (threadFuncName) ( void *argList )

// Be aware: mutexs in windows have thread affinity (they can be locked recursively in same thread), linux mutexs do not
// I should have used CreateSemaphore() Stack Overflow: http://goo.gl/h96Wh9  to avoid this difference...
// MSDN: http://goo.gl/hSD2Yh


#define closesocket(a) close(a)

// vxWorks does not have recursive... we are going to deadlock?

#define bits_mutex_define(mutexName)        pthread_mutex_t mutexName = PTHREAD_MUTEX_INITIALIZER
#define bits_mutex_extern(mutexName)        extern pthread_mutex_t mutexName
#define bits_mutex_init(mutexName)
#define bits_mutex_lock(mutexName) 			pthread_mutex_lock( &mutexName )
#define bits_mutex_unlock(mutexName) 		pthread_mutex_unlock( &mutexName )

void *bitsCreateThread(
    bitsThreadVar threadId, 
    void *(*threadFunc)(void *arg),
	void *argListPtr);

bool read_config(char *filepath) ;
bool parse_cmd(int argc, char *argv[]) ;
int osGetch(void);
int osKBhit(void);