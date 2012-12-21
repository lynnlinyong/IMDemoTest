/* 
 * File:   UMainControler.cpp
 * Author: easydigital-001
 * 
 * Created on 2012年11月28日, 上午10:31
 */

#include "fmod.h"
#include "RakPeerInterface.h"
#include "RakNetSmartPtr.h"
#include "RakNetSocket.h"
#include "upnpcommands.h"
#include "miniupnpc.h"
#include "Itoa.h"
#include "UPacketProcessor.h"
#include "UMainControler.h"
#include "privateDefine.h"
#include "upnperrors.h"

UMainControler UMainControler::instance;

UMainControler *UMainControler::getInstance() {
    return &instance;
}

UMainControler::UMainControler() : p_npc(NULL),
p_npclog(NULL), p_npcprint(NULL), p_rakVoice(NULL),
p_fmodSystem(NULL), serverAddress(SERVER_IP, SERVER_PORT),
p_adapter(RakNet::FMODVoiceAdapter::Instance()) {
    debug_(DEBUG_INFO, "UMainControler start\n");

    debug_(DEBUG_INFO, "UMainControler finish\n");
}

UMainControler::~UMainControler() {
    if (p_npc != NULL) {
        delete p_npc;
    }
    if (p_npclog != NULL) {
        delete p_npclog;
    }
    if (p_npcprint != NULL) {
        delete p_npcprint;
    }
    if (p_rakVoice != NULL) {
        delete p_rakVoice;
    }
    if (p_fmodSystem != NULL) {
        delete p_fmodSystem;
    }
}

void UMainControler::freePlugins() {
    //    extern RakNet::RakPeerInterface *g_rakPeer;
    //#ifdef __use_rakvoice__
    //    g_rakPeer->DetachPlugin(p_rakVoice);
    //    delete p_rakVoice;
    //    p_rakVoice = NULL;
    //#endif
    //    
    //#ifdef __use_natplugin__
    //    
    //#endif
}

#ifdef __use_rakvoice__

bool UMainControler::initFmod() {
    debug_(DEBUG_INFO, "initFmod start\n");

    if (p_fmodSystem != NULL) {
        uprintf("fmod init already\n");
        return false;
    }

    FMOD_RESULT result;
    unsigned int version;

    result = FMOD::System_Create(&p_fmodSystem);
    if (result != FMOD_OK) {
        uprintf("fmod system create fail\n");
        return false;
    }

    result = p_fmodSystem->getVersion(&version);
    if (result != FMOD_OK) {
        uprintf("fmod get version error\n");
        return false;
    }

    if (version < FMOD_VERSION) {
        uprintf("current fmod version %08x,need version %08x\n", version, FMOD_VERSION);
        return false;
    }

    result = p_fmodSystem->init(100, FMOD_INIT_NORMAL, 0);
    if (result != FMOD_OK) {
        uprintf("fmod init error\n");
        return false;
    }

    debug_(DEBUG_INFO, "initFmod finish\n");
    return true;
}

bool UMainControler::initRakVoice() {
    if (p_rakVoice != NULL) {
        uprintf("RakVoice init already\n");
        return false;
    }

    p_rakVoice = new RakNet::RakVoice;
    p_rakVoice->Init(SAMPLE_RATE, FRAMES_PER_BUFFER * sizeof (SAMPLE));

    extern RakNet::RakPeerInterface *g_rakPeer;
    g_rakPeer->AttachPlugin(p_rakVoice);

    if (!RakNet::FMODVoiceAdapter::Instance()->SetupAdapter(p_fmodSystem, p_rakVoice)) {
        uprintf("FMODVoiceAdapter setupAdapter error\n");
        return false;
    }
    
    p_rakVoice->SetVAD(false);
    p_rakVoice->SetVBR(false);
    p_rakVoice->SetNoiseFilter(true);

    return true;
}

bool UMainControler::requestVoip(RakNet::RakNetGUID guid) {
    if (p_fmodSystem == NULL) {
        return false;
    }

    if (p_rakVoice == NULL) {
        return false;
    }

    p_rakVoice->RequestVoiceChannel(guid);
    return true;
}

bool UMainControler::openLocalSound() {
    if (p_fmodSystem == NULL) {
        return false;
    }
    
    if (p_rakVoice == NULL) {
        return false;
    }
    
    return p_adapter->StartSoundIO();
}

bool UMainControler::updateVoice() {
    if (p_fmodSystem == NULL) {
        return false;
    }
    
    if (p_rakVoice == NULL) {
        return false;
    }
    printf("update ");
    p_fmodSystem->update();
    p_adapter->Update();
    
    return true;
}

void UMainControler::startUpdate(bool para) {
    UPacketProcessor::getInstance()->setUpdateVoice(para);
}

#endif

INIT_NAT_RESULT UMainControler::initNatPunchthrough() {
    if (p_npc != NULL) {
        uprintf("NATPunchthrough init already\n");
        return INIT_NAT_AREADY;
    }
    p_npc = new RakNet::NatPunchthroughClient;
    p_npcprint = new RakNet::NatPunchthroughDebugInterface_Printf;

    p_npc->SetDebugInterface(p_npcprint);

    extern RakNet::RakPeerInterface *g_rakPeer;
    g_rakPeer->AttachPlugin(p_npc);

    if (!initMiniupnpc()) {
        return INIT_MINIUPNPC_FAIL;
    }

    return INIT_NAT_SUCC;
}

bool UMainControler::openClientNat(RakNet::RakNetGUID guid) {
    if (p_npc == NULL) {
        uprintf("NATPunchthrough not init\n");
        return false;
    }

    return p_npc->OpenNAT(guid, serverAddress);
}

bool UMainControler::initMiniupnpc() {
    struct UPNPDev * devlist = 0;
    devlist = upnpDiscover(2000, 0, 0, 0, 0, 0);
    if (devlist) {
        debug_(DEBUG_INFO, "List of UPNP devices found on the network:\n");
        struct UPNPDev * device;
        for (device = devlist; device; device = device->pNext) {
            debug_(DEBUG_INFO, " desc: %s\n st: %s\n\n", device->descURL, device->st);
        }

        char lanaddr[64];
        struct UPNPUrls urls;
        struct IGDdatas data;
        if (UPNP_GetValidIGD(devlist, &urls, &data, lanaddr, sizeof (lanaddr)) == 1) {

            DataStructures::List<RakNet::RakNetSmartPtr<RakNet::RakNetSocket> > sockets;
            extern RakNet::RakPeerInterface *g_rakPeer;
            if (g_rakPeer == NULL) {
                debug_(DEBUG_INFO, "NULL rakPeer\n");
                freeUPNPDevlist(devlist);
                return false;
            }
            g_rakPeer->GetSockets(sockets);

            char iport[32];
            Itoa(sockets[0]->boundAddress.GetPort(), iport, 10);
            char eport[32];
            strcpy(eport, iport);

            int r = UPNP_AddPortMapping(urls.controlURL, data.first.servicetype,
                    eport, iport, lanaddr, 0, "UDP", 0, "0");

            if (r != UPNPCOMMAND_SUCCESS) {
                uprintf("AddPortMapping(%s, %s, %s) failed with code %d (%s)\n",
                        eport, iport, lanaddr, r, strupnperror(r));
                freeUPNPDevlist(devlist);
                return false;
            }

            char intPort[6];
            char intClient[16];

            char desc[128];
            char enabled[128];
            char leaseDuration[128];
            r = UPNP_GetSpecificPortMappingEntry(urls.controlURL,
                    data.first.servicetype,
                    eport, "UDP",
                    intClient, intPort,
                    desc, enabled, leaseDuration);

            if (r != UPNPCOMMAND_SUCCESS) {
                uprintf("GetSpecificPortMappingEntry() failed with code %d (%s)\n",
                        r, strupnperror(r));
                freeUPNPDevlist(devlist);
                return false;
            }
        }
        freeUPNPDevlist(devlist);
    }

    return true;
}
