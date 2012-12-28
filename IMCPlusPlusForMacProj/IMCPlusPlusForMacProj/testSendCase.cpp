#if 1
/* 
 * File:   testSendCase.cpp
 * Author: easydigital-001
 *
 * Created on 2012年12月17日, 下午2:53
 */

#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include "RakPeerInterface.h"
#include "RakNetSmartPtr.h"
#include "RakNetSocket.h"
#include "globalAPI.h"
#include "communicationProtocol.h"

using namespace std;

//#define isConnectFlag


pthread_t pid;
bool isConnect = false;

void *send_thread(void *) {
#ifdef isConnectFlag
    connect_peer("1480902057");
    void send_local_msg(unsigned char *, unsigned int, char *);
    regist_callback(ID_CONNECTION_REQUEST_ACCEPTED, send_local_msg);
#else
    printf("%s\n", get_local_guid());
    void deal_message(unsigned char *packet, unsigned int length, char *data);
    regist_callback(ID_USER_START, deal_message);
#endif

}

void deal_message(unsigned char *packet, unsigned int length, char *data) {
    printf("len:%d\n", length);
    for (int i = 1; i < length; i++) {
        printf("%c", packet[i]);
    }
    printf("\n");
}

void send_local_msg(unsigned char * packet, unsigned int length, char *data) {
    char message[40] = " hello world!";
    message[0] = ID_USER_START;
    send_message_easy(message, strlen(message), "1480902057");
}

int main(int argc, char** argv) {

    int rest = init_network_engine();

    printf("rest is %d\n", rest);
    if (rest == INIT_SUCC) {
        pthread_create(&pid, NULL, send_thread, NULL);

        start_network_engine();
    }




    return 0;
}
#endif
