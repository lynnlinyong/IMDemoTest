#include <RakPeerInterface.h>
#include <SocketLayer.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include "debug.h"
#include "globalAPI.h"
#include "privateDefine.h"
#include "UMainControler.h"
#include "UPacketProcessor.h"

RakNet::RakPeerInterface *g_rakPeer = NULL;
UMainControler *g_mainControler = NULL;

INIT_ENGINE_RESULT init_network_engine() {
    debug_(DEBUG_INFO, "init_network_engine start\n");

    if (g_rakPeer) {
        return INIT_AREADY;
    }
    g_rakPeer = RakNet::RakPeerInterface::GetInstance();

    CHECK_CONFIG_RESULT check_config();
    CHECK_CONFIG_RESULT check_rst = check_config();
    if (check_rst != CONFIG_SUCC) {
        uprintf("error config exsits,error no is %d\n", check_rst);
        return ERROR_CONFIG;
    }

    RakNet::SocketDescriptor sd(RAKPEER_PORT, 0);
    if (g_rakPeer->Startup(MAX_CONNECT_COUNT, &sd, 1) != RakNet::RAKNET_STARTED) {
        uprintf("Failed to start rakPeer! Quitting\n");
        RakNet::RakPeerInterface::DestroyInstance(g_rakPeer);
        return START_UP_FAIL;
    }

    g_rakPeer->SetMaximumIncomingConnections(MAX_INCOME_COUNT);

    if (g_mainControler) {
        return ERROR_INIT_CONTROLER;
    }
    g_mainControler = UMainControler::getInstance();

    if (g_mainControler->initNatPunchthrough() != INIT_NAT_SUCC) {
        return INIT_NAT_ERROR;
    }
    
#ifdef __use_rakvoice__
    if (!g_mainControler->initFmod()) {
        return INIT_FMOD_ERROR;
    }

    if (!g_mainControler->initRakVoice()) {
        return INIT_RAKVOICE_ERROR;
    }
#endif

    bool connect_server();
    if (!connect_server()) {
        return SERVER_NO_REPLY;
    }

    debug_(DEBUG_INFO, "init_network_engine finish\n");
    return INIT_SUCC;
}
#if 0
INIT_NAT_RESULT init_nat_punchthrough(void) {
    if (g_rakPeer == NULL) {
        return INIT_NAT_NOT_INIT_NETWORK;
    }

    if (g_mainControler == NULL) {
        return INIT_NAT_NOT_INIT_CONTROLER;
    }

    return g_mainControler->initNatPunchthrough();
}
#endif
START_NETWORK_RESULT start_network_engine() {
    debug_(DEBUG_INFO, "start_network_engine start\n");

    if (g_rakPeer == NULL) {
        return NETWORK_NOT_INIT;
    }

    UPacketProcessor *p_processor = UPacketProcessor::getInstance();
    p_processor->processPacketLoop();

    debug_(DEBUG_INFO, "start_network_engine finish\n");
    return START_NETWORK_SUCC;
}

STOP_NETWORK_RESULT stop_network_engine() {
    debug_(DEBUG_INFO, "stop_network_engine start\n");

    if ((g_rakPeer == NULL) || (g_mainControler == NULL)) {
        return ENGINE_NOT_START;
    }

    g_mainControler->freePlugins();

    debug_(DEBUG_INFO, "stop_network_engine stop\n");
    return STOP_NETWORK_SUCC;
}

REG_CALLBACK_RESULT regist_callback(unsigned int msg_identify, func_pointer callback) {
    UPacketProcessor *p_processor = UPacketProcessor::getInstance();
    return p_processor->registCallback(msg_identify, callback);
}

FREE_REG_RESULT free_callback(unsigned int msg_identify) {
    UPacketProcessor *p_processor = UPacketProcessor::getInstance();
    return p_processor->freeCallback(msg_identify);
}

char * get_network_guid() {
    if (g_rakPeer == NULL) {
        uprintf("network not init\n");
        return NULL;
    }

    return const_cast<char *> (g_rakPeer->GetMyGUID().ToString());
}

OPEN_NAT_RESULT open_client_nat(char *remote_guid) {
    debug_(DEBUG_INFO, "open_client_nat start\n");
    if (remote_guid == NULL) {
        uprintf("error remote guid\n");
        return OPEN_NAT_ERROR;
    }

    if (g_rakPeer == NULL) {
        uprintf("network not init\n");
        return OPEN_NAT_NOT_INIT_NETWORK;
    }

    if (g_mainControler == NULL) {
        uprintf("controler not init\n");
        return OPEN_NAT_NOT_INIT_CONTROLER;
    }

    RakNet::RakNetGUID remoteSystem;
    remoteSystem.FromString(remote_guid);

    if (!g_mainControler->openClientNat(remoteSystem)) {
        uprintf("open nat fail\n");
        return OPEN_NAT_ACTION_FAIL;
    }

    debug_(DEBUG_INFO, "open_client_nat finish\n");
    return OPEN_NAT_SUCC;
}

CONNECT_PEER_RESULT connect_peer(char *remote_ip, unsigned short remote_port) {
    debug_(DEBUG_INFO, "connect_peer start\n");

    if (g_rakPeer == NULL) {
        return CONNECT_PEER_NOT_INIT_NETWORK;
    }

    if (g_mainControler == NULL) {
        return CONNECT_PEER_NOT_INIT_CONTROLER;
    }

    if (remote_ip == NULL) {
        return CONNECT_PEER_NULL_IP;
    }

    if (RakNet::CONNECTION_ATTEMPT_STARTED != g_rakPeer->Connect(remote_ip, remote_port, 0, 0)) {
        return CONNECT_PEER_RAKNET_CORE_ERROR;
    }

    debug_(DEBUG_INFO, "connect_peer finish\n");
    return CONNECT_PEER_SUCC;
}

SEND_MSG_EASY_RESULT send_message_easy(char * msg, int msg_length, char *ip_port) {
    debug_(DEBUG_INFO, "send_message_easy start\n");

    if (g_rakPeer == NULL) {
        return SEND_MSG_EASY_NOT_INIT_NETWORK;
    }

    if (g_mainControler == NULL) {
        return SEND_MSG_EASY_NOT_INIT_CONTROLER;
    }

    if (msg_length <= 0) {
        return SEND_MSG_EASY_ERROR_LENGTH;
    }

    if (msg == NULL) {
        return SEND_MSG_NULL_MSG;
    }

    if (ip_port == NULL) {
        return SEND_MSG_NULL_ADDRESS;
    }

    RakNet::SystemAddress remote_peer;
    remote_peer.FromString(ip_port);

    if (g_rakPeer->GetGuidFromSystemAddress(remote_peer) ==
            RakNet::UNASSIGNED_RAKNET_GUID) {
        return SEND_MSG_PEER_NOT_CONNECT;
    }

    int rst = g_rakPeer->Send(msg, msg_length, MEDIUM_PRIORITY, RELIABLE, 0, remote_peer, false);
    if (rst == 0) {
        return SEND_MSG_BAD_INPUT;
    }

    debug_(DEBUG_INFO, "send_message_easy finish\n");
    return SEND_MSG_EASY_SUCC;
}

SEND_MSG_ADVANCE_RESULT send_message_advance(char *msg, int msg_length, char *remote_guid) {
    debug_(DEBUG_INFO, "send_message_advance start\n");

    debug_(DEBUG_INFO, "send_message_advance finish\n");
    return SEND_MSG_ADVANCE_SUCC;
}

START_VOIP_RESULT start_voip(char *ip_port) {
    debug_(DEBUG_INFO, "start_voip start\n");
    
    if (g_rakPeer == NULL) {
        return START_VOIP_NOT_INIT_NETWORK;
    }
    
    if (g_mainControler == NULL) {
        return START_VOIP_NOT_INIT_CONTROLER;
    }
    
    if (ip_port == NULL) {
        return START_VOIP_NULL_ERROR;
    }
    
    RakNet::SystemAddress remote_peer;
    remote_peer.FromString(ip_port);
    if (g_rakPeer->GetGuidFromSystemAddress(remote_peer) ==
            RakNet::UNASSIGNED_RAKNET_GUID) {
        return START_VOIP_PEER_NOT_CONNECT;
    }
    
    if (!g_mainControler->requestVoip(g_rakPeer->GetGuidFromSystemAddress(remote_peer)) )
    {
        return START_VOIP_FAIL;
    }
    
    debug_(DEBUG_INFO, "start_voip finish\n");
    return START_VOIP_SUCC;
}

OPEN_SOUND_RESULT open_sound() {
    debug_(DEBUG_INFO, "open_sound start\n");
    
    if (g_rakPeer == NULL) {
        return OPEN_SOUND_NOT_INIT_NETWORK;
    }
    
    if (g_mainControler == NULL) {
        return OPEN_SOUND_NOT_INIT_CONTROLER;
    }
    
    if (!g_mainControler->openLocalSound()) {
        return OPEN_SOUND_FAIL;
    }
    
    g_mainControler->startUpdate(true);
    debug_(DEBUG_INFO, "open_sound finish\n");
    return OPEN_SOUND_SUCC;
}

#if 0
INIT_VOIP_RESULT init_voip() {
    debug_(DEBUG_INFO, "init_voip start\n");
    
    if (g_rakPeer == NULL) {
        return INIT_VOIP_NOT_INIT_NETWORK;
    }
    
    if (g_mainControler == NULL) {
        return INIT_VOIP_NOT_INIT_CONTROLER;
    }
    
    if (!g_mainControler->initFmod()) {
        return INIT_VOIP_FMOD_ERROR;
    }
    
    if (!g_mainControler->initRakVoice()) {
        return INIT_VOIP_RAKVOICE_ERROR;
    }
    
    debug_(DEBUG_INFO, "init_voip finish\n");
    return INIT_VOIP_SUCC;
}
#endif


#if 0

void show_init_engine_result(INIT_ENGINE_RESULT para) {
    switch (para) {
        case INIT_SUCC:
            uprintf("INIT_SUCC\n");
            break;
        case INIT_AREADY:
            uprintf("INIT_AREADY\n");
            break;
        case ERROR_CONFIG:
            uprintf("ERROR_CONFIG\n");
            break;
        case START_UP_FAIL:
            uprintf("START_UP_FAIL\n");
            break;
        case SERVER_NO_REPLY:
            uprintf("SERVER_NO_REPLY\n");
            break;
        case INIT_NAT_ERROR:
            uprintf("INIT_NAT_ERROR\n");
            break;
        case INIT_FMOD_ERROR:
            uprintf("INIT_FMOD_ERROR");
            break;
        case INIT_RAKVOICE_ERROR:
            uprintf("INIT_RAKVOICE_ERROR");
            break;
        default:
            uprintf("undefined result\n");
    }
}

void show_regist_callback_result(REG_CALLBACK_RESULT para) {
    switch (para) {
        case REG_CALLBACK_SUCC:
            uprintf("REG_CALLBACK_SUCC\n");
            break;
        case REG_CALLBACK_ALREADY:
            uprintf("REG_CALLBACK_ALREADY\n");
            break;
        case ERROR_CALLBACK_POINTER:
            uprintf("ERROR_CALLBACK_POINTER\n");
            break;
        default:
            uprintf("undefined result\n");
    }
}

void show_free_callback_result(FREE_REG_RESULT para) {
    switch (para) {
        case FREE_REG_SUCC:
            uprintf("FREE_REG_SUCC\n");
            break;
        case FREE_NOT_REG:
            uprintf("FREE_NOT_REG\n");
            break;
        default:
            uprintf("undefined result\n");
    }
}

void show_start_engine_result(START_NETWORK_RESULT para) {
    switch (para) {
        case START_NETWORK_SUCC:
            uprintf("START_NETWORK_SUCC\n");
            break;
        case NETWORK_NOT_INIT:
            uprintf("NETWORK_NOT_INIT\n");
            break;
        default:
            uprintf("undefined result\n");
    }
}
#endif