/* 
 * File:   UMainControler.h
 * Author: easydigital-001
 *
 * Created on 2012年11月28日, 上午10:31
 */

#ifndef UMAINCONTROLER_H
#define	UMAINCONTROLER_H

#include "NatPunchthroughClient.h"
#include "RakVoice.h"
#include "fmod.hpp"
#include "FMODVoiceAdapter.h"
#include "debug.h"
#include "errorNumber.h"

class UMainControler {
public:
    virtual ~UMainControler();

public:
    interface__ static UMainControler *getInstance();
    interface__ void freePlugins();
    
#ifdef __use_rakvoice__
    interface__ bool initFmod();
    interface__ bool initRakVoice();
    
    interface__ bool requestVoip(RakNet::RakNetGUID);
    interface__ bool openLocalSound();
    interface__ void startUpdate(bool);
    private_method__ bool updateVoice();
#endif

    interface__ INIT_NAT_RESULT initNatPunchthrough();
    interface__ bool openClientNat(RakNet::RakNetGUID);
    
private:
    forbid__ UMainControler();
    forbid__ UMainControler(const UMainControler& orig);   
    
    private_method__ bool initMiniupnpc();

    
private:
    static UMainControler instance;
    RakNet::NatPunchthroughClient *p_npc;
    RakNet::NatPunchthroughDebugInterface_PacketLogger *p_npclog;
    RakNet::NatPunchthroughDebugInterface_Printf *p_npcprint;
    RakNet::FMODVoiceAdapter *p_adapter;
    RakNet::RakVoice *p_rakVoice;
    FMOD::System *p_fmodSystem;
    
private:
    RakNet::SystemAddress serverAddress;
};

#endif	/* UMAINCONTROLER_H */

