/* 
 * File:   configDefine.h
 * Author: easydigital-001
 *
 * Created on 2012年11月23日, 下午4:21
 */

#ifndef CONFIGDEFINE_H
#define	CONFIGDEFINE_H

#include "usrConfigDefine.h"

#ifndef SERVER_IP
#define SERVER_IP "202.75.221.149"
#endif

#ifndef SERVER_PORT
#define SERVER_PORT (61111)
#endif

#ifndef RAKPEER_PORT
#define RAKPEER_PORT (0)
#endif

#ifndef MAX_CONNECT_COUNT
#define MAX_CONNECT_COUNT (100)
#endif

#ifndef MAX_INCOME_COUNT
#define MAX_INCOME_COUNT (MAX_CONNECT_COUNT - 1)
#endif

#ifdef __use_rakvoice__
        #ifndef SAMPLE_RATE 
        #define SAMPLE_RATE (8000)
        #endif

        #ifndef FRAMES_PER_BUFFER
        #define FRAMES_PER_BUFFER (2048 / (32000 / SAMPLE_RATE))
        #endif
#endif

typedef short SAMPLE;

#endif	/* CONFIGDEFINE_H */

