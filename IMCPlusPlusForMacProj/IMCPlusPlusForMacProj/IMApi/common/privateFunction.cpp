#include <RakPeerInterface.h>
#include <stdio.h>
#include <stdlib.h>
#include <MessageIdentifiers.h>
#include <NatPunchthroughClient.h>
#include <PacketLogger.h>
#include "debug.h"
#include "privateDefine.h"
#include "errorNumber.h"

extern RakNet::RakPeerInterface *g_rakPeer;

private_method__ bool connect_server() {
    debug_(DEBUG_INFO, "connect_server %s:%d start\n", SERVER_IP, SERVER_PORT);

    if ((g_rakPeer->Connect(SERVER_IP, SERVER_PORT, 0, 0)) != (RakNet::CONNECTION_ATTEMPT_STARTED)) {
        uprintf("connect interal error\n");
        return false;
    }   

    RakNet::Packet *packet;
    RakNet::SystemAddress systemAddress;
    bool isRunning = true;
    while (isRunning) {
        for (packet = g_rakPeer->Receive(); packet; g_rakPeer->DeallocatePacket(packet), packet = g_rakPeer->Receive()) {
            debug_(DEBUG_INFO, "%d\n", packet->data[0]);
            debug_(DEBUG_INFO, "%s\n", RakNet::PacketLogger::BaseIDTOString(packet->data[0]));
            if (packet->data[0] == ID_CONNECTION_REQUEST_ACCEPTED) {
                uprintf("connect server succeed\n");
                isRunning = false;
                break;
            } else {
                uprintf("Server reply error identify\n");
                return false;
            }
        }
    }

    debug_(DEBUG_INFO, "connect_server finish\n");
    return true;
}

private_method__ CHECK_CONFIG_RESULT check_config() {
    debug_(DEBUG_INFO, "check_config start\n");

    bool isRightIP(const char *);
    if (!isRightIP(SERVER_IP)) {
        debug_(DEBUG_CONFIG, "error server ip config\n");
        return ERROR_IP;
    }
    debug_(DEBUG_CONFIG, "right server ip config\n");

    if (SERVER_PORT >= 65535 || SERVER_PORT <= 0) {
        debug_(DEBUG_CONFIG, "error server port config\n");
        return ERROR_PORT;
    }
    debug_(DEBUG_CONFIG, "right server port config\n");

    if (RAKPEER_PORT >= 65535 || RAKPEER_PORT < 0) {
        debug_(DEBUG_CONFIG, "error rakPeer port config\n");
        return ERROR_RAKPEER_PORT;
    }
    debug_(DEBUG_CONFIG, "right rakPeer port config\n");

    if (MAX_CONNECT_COUNT > 65535 || MAX_CONNECT_COUNT <= 0) {
        debug_(DEBUG_CONFIG, "error max connect count config\n");
        return ERROR_MAX_CONNECT_COUNT;
    }
    debug_(DEBUG_CONFIG, "right max connect count config\n");

    if (MAX_INCOME_COUNT > MAX_CONNECT_COUNT || MAX_INCOME_COUNT < 0) {
        debug_(DEBUG_CONFIG, "error max income count config\n");
        return ERROR_MAX_INCOME_COUNT;
    }
    debug_(DEBUG_CONFIG, "right max income count config\n");

#ifdef __use_rakvoice__
    if ( (SAMPLE_RATE != 8000) && (SAMPLE_RATE != 16000) && (SAMPLE_RATE != 32000)) {
        debug_(DEBUG_CONFIG, "error sample rate config\n");
        return ERROR_SAMPLE_RATE;
    }
    debug_(DEBUG_CONFIG, "right sample rate config\n");
    
#endif
    
    debug_(DEBUG_INFO, "check_config finish\n");
    return CONFIG_SUCC;
}

private_method__ bool isRightIP(const char *p_para) {
    if (!p_para) {
        return false;
    }

    //获取字符串长度，
    int stringSize = strlen(p_para);
    //最短IP字符串"0.0.0.0"长度为7
    //最长IP字符串"255.255.255.255"长度位15
    if (stringSize < 7 || stringSize > 15){
        return false;
    }

    int dotCount = 0;
    const char *tmp_p = p_para;
    char tmp_array[4] = {""};
    for (int i = 0; i < stringSize; i++,p_para++) {
        if ( (*(p_para) == '.') || (stringSize == i + 1)) {
            dotCount++;            
            if ((p_para - tmp_p) > 3){
                
                return false;
            }
            for(int j = 0;tmp_p <= p_para; tmp_p++, j++){
                tmp_array[j] = *tmp_p;
            }
            int tmp = atoi(tmp_array);
            
            if (tmp > 255 || tmp < 0){
                return false;
            }
        }
        memset(tmp_array, '\0', sizeof(tmp_array));
    }
    if (dotCount != 4){
        return false;
    }
    
    return true;
}
