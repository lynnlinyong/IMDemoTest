/* 
 * File:   UPacketProcessor.cpp
 * Author: easydigital-001
 * 
 * Created on 2012年11月28日, 下午5:07
 */

#include <RakNetTypes.h>
#include <RakPeerInterface.h>
#include <PacketLogger.h>
#include <string>
#include <RakSleep.h>
#include "UPacketProcessor.h"
#include "UMainControler.h"

UPacketProcessor UPacketProcessor::instance;

UPacketProcessor *UPacketProcessor::getInstance() {
    return &instance;
}

UPacketProcessor::UPacketProcessor(): updateVoice(false){
    debug_(DEBUG_INFO, "UPacketProcessor start\n");
    
    callbackContainer.clear();
    pthread_mutex_init(&mutex, NULL);

    debug_(DEBUG_INFO, "UPacketProcessor finish\n");
}

UPacketProcessor::~UPacketProcessor() {
    debug_(DEBUG_INFO, "~UPacketProcessor start\n");

    pthread_mutex_destroy(&mutex);

    debug_(DEBUG_INFO, "~UPacketProcessor finish\n");
}

REG_CALLBACK_RESULT UPacketProcessor::registCallback(unsigned int paraMsgIdentify,
        func_pointer actionFunction) {
    if (actionFunction == NULL) {
        return ERROR_CALLBACK_POINTER;
    }

    std::map<int, func_pointer>::iterator tmp_iter = callbackContainer.find(paraMsgIdentify);
    if (tmp_iter != callbackContainer.end()) {
        return REG_CALLBACK_ALREADY;
    }

    debug_(DEBUG_INFO, "registCallback to map start\n");
    pthread_mutex_lock(&mutex);
    callbackContainer[paraMsgIdentify] = actionFunction;
    pthread_mutex_unlock(&mutex);
    debug_(DEBUG_INFO, "registCallback to map finish\n");

    return REG_CALLBACK_SUCC;
}

FREE_REG_RESULT UPacketProcessor::freeCallback(unsigned int paraMsgIdentify) {
    std::map<int, func_pointer>::iterator tmp_iter = callbackContainer.find(paraMsgIdentify);
    if (tmp_iter == callbackContainer.end()){
        return FREE_NOT_REG;
    }
    debug_(DEBUG_INFO, "freeCallback from map start\n");
    callbackContainer.erase(tmp_iter);
    debug_(DEBUG_INFO, "freeCallback from map finish\n");
    return FREE_REG_SUCC;
}

void UPacketProcessor::setUpdateVoice(bool update) {
    updateVoice = update;
}

void UPacketProcessor::processPacketLoop() {
    RakNet::Packet *packet = NULL;
    extern RakNet::RakPeerInterface *g_rakPeer;
    if (g_rakPeer == NULL){
        uprintf("network engine not init\n");
        return;
    }
    
    while (1) {
        for (packet = g_rakPeer->Receive(); packet;
                g_rakPeer->DeallocatePacket(packet), packet = g_rakPeer->Receive()) {
            packet->systemAddress.ToString(true);
            debug_(DEBUG_INFO, "recv packet identify is %d %s\ncome from %s\n", 
                    packet->data[0], RakNet::PacketLogger::BaseIDTOString(packet->data[0]), packet->systemAddress.ToString(true));
            unsigned int paraMsgIdentify = packet->data[0];
            if (callbackContainer.find(paraMsgIdentify) != callbackContainer.end()) {
                debug_(DEBUG_INFO, "find callback function, callback\n");
                std::string tmp_string((char *) (packet->data));
                callbackContainer[paraMsgIdentify](const_cast<char *> (tmp_string.c_str()));
            }
        }
        
        if (updateVoice) {
            UMainControler::getInstance()->updateVoice();
        }
        RakSleep(3);
    }
}