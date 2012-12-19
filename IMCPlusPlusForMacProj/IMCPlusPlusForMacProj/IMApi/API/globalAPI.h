/* 
 * File:   globalAPI.h
 * Author: easydigital-001
 *
 * Created on 2012年11月23日, 下午4:32
 * Details:在使用本文件之前，请阅读位于本文件夹下的README，
 * 获取怎么使用这些API，以及需要注意的各种问题。
 */

#ifndef GLOBALAPI_H
#define	GLOBALAPI_H

#include "debug.h"
#include "errorNumber.h"

/* function name:init_network_engine
 * input para   :void
 * output para  :void
 * return value :初始化结果的错误码
 * details      :初始化网络引擎，该函数是
 * 所有其他API调用之前必须调用。
 */
interface__ INIT_ENGINE_RESULT   init_network_engine(void);

#if 0
/* function name:init_nat_punchthrough
 * input para   :void
 * output para  :void
 * return value :初始化NAT结果的错误码
 * details      :初始化NAT穿透功能，该函数需要在
 *      start_network_engine()之后调用
 */
interface__ INIT_NAT_RESULT init_nat_punchthrough(void);
#endif
/* function name:regist_callback
 * input para   :unsigned int 代表注册的ID，func_pointer 代表对应ID的回调函数
 * output para  :void
 * return value :注册结果的错误码
 * details      :注册对应ID的回调函数。
 */
interface__ REG_CALLBACK_RESULT  regist_callback(unsigned int, func_pointer);

/* function name:free_callback
 * input para   :unsigned int 代表解除注册的ID
 * output para  :void
 * return value :解除注册结果的错误码
 * details      :解除注册对应ID的回调函数。
 */
interface__ FREE_REG_RESULT      free_callback(unsigned int);

/* function name:start_network_engine
 * input para   :void
 * output para  :void
 * return value :启动网络引擎的错误码
 * details      :启动接受网络包的事件循环。
 */
interface__ START_NETWORK_RESULT start_network_engine(void);

/* function name:get_network_guid
 * input para   :void
 * output para  :void
 * return value :NULL代表网络未初始化，char *代表获取到的guid
 * details      :获取网络GUID
 */
interface__ char * get_network_guid(void);

/* function name:open_client_nat
 * input para   :char * 代表对方的guid,该guid从PHP获得
 * output para  :void
 * return value :进行NAT穿透的错误码
 * details      :和服务器之间进行NAT穿透交互
 */
interface__ OPEN_NAT_RESULT open_client_nat(char *);

/* function name:connect_peer
 * input para   :char *ip 代表需要连接的ip地址
 *               unsigned short port代表需要连接的端口地址
 * output para  :void
 * return value :连接的错误码
 * details      :进行Peer对Peer连接的API，该连接状态是一个异步
 *      处理过程，返回值不能当作连接建立的标志，连接建立成功是通过
 *      收到ID_CONNECTION_REQUEST_ACCEPTED为标志的包来指出。
 */
interface__ CONNECT_PEER_RESULT connect_peer(char *ip, unsigned short port);

/* function name:send_message_easy
 * input para   :char *message 代表需要发送的消息内容
 *              :int message_length 代表需要发送的消息内容长度
 *              :char *ip_port 代表需要发送到的ip地址和端口
 * output para  :void
 * return value :发送消息的错误码
 * details      :在调用该发送函数之前，首先确保已经建立连接，如果未
 *      建立连接，该函数会返回未建立连接的相关错误码。该发送是异步发
 *      送，不能通过该函数的返回值来标志发送是否成功，只能通过异常的
 *      收包来确定发送失败的原因。发送成功可以通过业务层逻辑来添加，
 *      当然这种处理方式并不必要。
 */
interface__ SEND_MSG_EASY_RESULT send_message_easy(char *message,
        int message_length, char *ip_port);

/* function name:send_message_advance
 * input para   :char *message
 */
interface__ SEND_MSG_ADVANCE_RESULT send_message_advance(char *message,int ,char *);

interface__ STOP_NETWORK_RESULT stop_network_engine();

/* function name:start_voip
 * input para   :char *guid 代表需要开启VOIP端的guid
 * output para  :void
 * return value :启动VOIP时出现的错误码
 * details      :
 */
interface__ START_VOIP_RESULT start_voip(char *guid);

interface__ OPEN_SOUND_RESULT open_sound();

interface__ STOP_VOIP_RESULT stop_voip(char *guid);
#if 0
interface__ INIT_VOIP_RESULT init_voip();
#endif



#if 0
interface__ void show_init_engine_result(INIT_ENGINE_RESULT);

interface__ void show_regist_callback_result(REG_CALLBACK_RESULT);

interface__ void show_free_callback_result(FREE_REG_RESULT);

interface__ void show_start_engine_result(START_NETWORK_RESULT);
#endif

#endif	/* GLOBALAPI_H */

