#if 1
/* 
 * File:   testVoipCase.cpp
 * Author: ben
 *
 * Created on 2012年12月19日, 上午1:09
 */

#include <cstdlib>
#include <pthread.h>
#include "MessageIdentifiers.h"
#include "globalAPI.h"

using namespace std;

pthread_t pid;

#define isSender

void sender_callback(char *data) {
    free_callback(ID_CONNECTION_REQUEST_ACCEPTED);
    
    if (start_voip("127.0.0.1|41111") == START_VOIP_SUCC) {
        printf("\nnow send voice request\n");
    }
}

void sender_callback1(char *data) {
    free_callback(ID_RAKVOICE_OPEN_CHANNEL_REPLY);
    
    if (open_sound() == OPEN_SOUND_SUCC) {
        printf("\nsender now open sound\n");
    }
}

void recv_callback(char *data) {
    free_callback(ID_RAKVOICE_OPEN_CHANNEL_REQUEST);
    
    if (open_sound() == OPEN_SOUND_SUCC) {
        printf("\nrecv now open sound\n");
    }
}

void *test_thread(void *) {
#ifdef isSender
    connect_peer("127.0.0.1", 41111);
    
    regist_callback(ID_CONNECTION_REQUEST_ACCEPTED, sender_callback);
    regist_callback(ID_RAKVOICE_OPEN_CHANNEL_REPLY, sender_callback1);
    
#else
    regist_callback(ID_RAKVOICE_OPEN_CHANNEL_REQUEST, recv_callback);
#endif
    
}

int main(int argc, char** argv) {

    init_network_engine();
    
    pthread_create(&pid, NULL, test_thread, NULL);
    
    start_network_engine();
    return 0;
}
#endif
