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

#include <MessageIdentifiers.h>

enum {
    ID_USER_START = ID_USER_PACKET_ENUM,
    //用户如果需要添加新的通讯标志，如下所示：
    //eg.ID_MY_FLAG
    
};



#endif	/* COMMUNICATIONPROTOCOL_H */

