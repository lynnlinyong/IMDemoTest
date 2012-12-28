/* 
 * File:   communicationProtocol.h
 * Author: easydigital-001
 *
 * Created on 2012年11月29日, 下午3:11
 * Details:本文件是用户通讯协议拓展，
 * 需要添加通讯新的通讯协议，只需要添加新的
 * 枚举成员
 */

#ifndef COMMUNICATIONPROTOCOL_H
#define	COMMUNICATIONPROTOCOL_H

#include "MessageIdentifiers.h"

enum {
    ID_USER_START = ID_USER_PACKET_ENUM,
    //用户如果需要添加新的通讯标志，如下所示：
    //eg.ID_MY_FLAG
};

struct ip_request_struct {
    unsigned char struct_identify; //通讯标志
    char ipString[30];             //消息内容，回复结果eg."127.0.0.1|65535"
};

#endif	/* COMMUNICATIONPROTOCOL_H */

