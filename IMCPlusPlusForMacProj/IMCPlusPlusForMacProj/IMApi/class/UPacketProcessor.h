/* 
 * File:   UPacketProcessor.h
 * Author: easydigital-001
 *
 * Created on 2012年11月28日, 下午5:07
 */

#ifndef UPACKETPROCESSOR_H
#define	UPACKETPROCESSOR_H
#include <map>
#include <pthread.h>
#include "debug.h"
#include "errorNumber.h"

class UPacketProcessor {
    
public:
    virtual ~UPacketProcessor();
    
public:
    interface__ static UPacketProcessor *getInstance();
    interface__ REG_CALLBACK_RESULT registCallback(unsigned int, func_pointer);
    interface__ FREE_REG_RESULT freeCallback(unsigned int);
    interface__ void processPacketLoop();
    interface__ void setUpdateVoice(bool);
    
private:
    forbid__ UPacketProcessor();
    forbid__ UPacketProcessor(const UPacketProcessor& orig);
    
private:
    static UPacketProcessor instance;
    std::map <int, func_pointer> callbackContainer;
    pthread_mutex_t mutex;
    bool updateVoice;
};

#endif	/* UPACKETPROCESSOR_H */

