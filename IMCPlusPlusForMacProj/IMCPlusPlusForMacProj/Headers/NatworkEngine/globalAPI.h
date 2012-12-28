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

/* function name:regist_callback
 * input para   :unsigned int 代表注册的ID，func_pointer 代表对应ID的回调函数
 *      char * 代表数据存储，如果不存在则传入NULL
 * output para  :void
 * return value :注册结果的错误码
 * details      :注册对应ID的回调函数。
 */
interface__ REG_CALLBACK_RESULT  regist_callback(unsigned char, func_pointer);

/* function name:free_callback
 * input para   :unsigned int 代表解除注册的ID
 * output para  :void
 * return value :解除注册结果的错误码
 * details      :解除注册对应ID的回调函数。
 */
interface__ FREE_REG_RESULT      free_callback(unsigned char);

/* function name:start_network_engine
 * input para   :void
 * output para  :void
 * return value :启动网络引擎的错误码
 * details      :启动接受网络包的事件循环。
 */
interface__ START_NETWORK_RESULT start_network_engine(void);

/* function name:stop_network_engine
 * input para   :void
 * output para  :void
 * return value :停止网络引擎的错误码
 * details      :停止网络引擎
 */
interface__ STOP_NETWORK_RESULT stop_network_engine();

/* function name:get_local_guid
 * input para   :void
 * output para  :void
 * return value :NULL代表网络未初始化，char *代表获取到的guid
 * details      :获取本地网络GUID
 */
interface__ char * get_local_guid(void);

/* function name:get_peer_ip
 * input para   :char *guid 表示需要得到IP的guid,如果传入的
 *      guid为0(NULL),将会获取本地的外部IP地址和端口
 * ouput para   :void
 * return value :获取过程出现的错误码
 * details      :发送对应guid的外部的IP和端口
 */
//interface__ GET_PEER_IP_RESULT get_peer_ip(char * guid);

/* function name:open_client_nat
 * input para   :char * 代表对方的guid,该guid从PHP获得
 * output para  :void
 * return value :进行NAT穿透的错误码
 * details      :和服务器之间进行NAT穿透交互
 */
interface__ OPEN_NAT_RESULT open_client_nat(char *);

/* function name:connect_peer
 * input para   :char *guid 表示需要连接的guid
 * output para  :void
 * return value :连接的错误码
 * details      :进行Peer对Peer连接的API，该连接状态是一个异步
 *      处理过程，返回值不能当作连接建立的标志，连接建立成功是通过
 *      收到ID_CONNECTION_REQUEST_ACCEPTED为标志的包来指出。
 */
interface__ CONNECT_PEER_RESULT connect_peer(char *guid);

/* function name:send_message_easy
 * input para   :char *message 代表需要发送的消息内容
 *              :int message_length 代表需要发送的消息内容长度
 *              :char *guid 代表需要发送到的guid
 * output para  :void
 * return value :发送消息的错误码
 * details      :在调用该发送函数之前，首先确保已经建立连接，如果未
 *      建立连接，该函数会返回未建立连接的相关错误码。该发送是异步发
 *      送，不能通过该函数的返回值来标志发送是否成功，只能通过异常的
 *      收包来确定发送失败的原因。发送成功可以通过业务层逻辑来添加，
 *      当然这种处理方式并不必要。
 */
interface__ SEND_MSG_EASY_RESULT send_message_easy(char *message,
        int message_length, char *guid);

/* function name:start_voip
 * input para   :char *guid 代表需要开启VOIP端的guid
 * output para  :void
 * return value :启动VOIP时出现的错误码
 * details      :在调用该函数前，首先确保已经建立连接，而且启动
 *      消息处理循环。该函数是异步发送，不能通过该函数的返回值来标志
 *      是否发送成功，只能通过收到的包来确定是否开启成功。而且这个在
 *      确定收包成功之后，需要调用open_sound来进行内部刷新。
 */
interface__ START_VOIP_RESULT start_voip(char *guid);

/* function name:open_sound
 * input para   :void
 * output para  :void
 * return value :打开本地音频资源的的相关错误码
 * details      :在调用该函数前，首先确保已经建立连接，而且启动
 *      消息处理循环。该函数会受注册回调机制的复杂度的影响，所以
 *      要注意。
 */
interface__ OPEN_SOUND_RESULT open_sound(void);

/* function name:stop_voip
 * input para   :char *guid
 * output para  :void
 * return value :停止VOIP的错误码
 */
interface__ STOP_VOIP_RESULT stop_voip(char *guid);

#if 0
interface__ SEND_MSG_ADVANCE_RESULT send_message_advance(char *message,int ,char *);

interface__ void show_init_engine_result(INIT_ENGINE_RESULT);

interface__ void show_regist_callback_result(REG_CALLBACK_RESULT);

interface__ void show_free_callback_result(FREE_REG_RESULT);

interface__ void show_start_engine_result(START_NETWORK_RESULT);
#endif

#endif	/* GLOBALAPI_H */

