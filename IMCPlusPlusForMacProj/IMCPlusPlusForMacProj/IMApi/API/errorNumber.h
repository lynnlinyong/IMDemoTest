/* 
 * File:   errerNumber.h
 * Author: easydigital-001
 *
 * Created on 2012年11月26日, 下午2:21
 */

#ifndef ERRERNUMBER_H
#define	ERRERNUMBER_H

//该枚举代表初始化网络引擎结果
#define INIT_ENGINE_RESULT unsigned int

enum INIT_ENGINE_RESULT_ENUM {
    //首次初始化成功
    INIT_SUCC,
    //已经初始化
    INIT_AREADY,
    //错误的配置
    ERROR_CONFIG,
    //RakNet启动失败
    START_UP_FAIL,
    //服务器无回应
    SERVER_NO_REPLY,
    //Nat穿透插件载入失败
    INIT_NAT_ERROR,
    //Fmod初始化失败
    INIT_FMOD_ERROR,
    //RakVoice初始化失败
    INIT_RAKVOICE_ERROR,
    //错误的控制器初始化
    ERROR_INIT_CONTROLER
    
};

//该枚举代表检测配置结果
#define CHECK_CONFIG_RESULT unsigned int

enum CHECK_CONFIG_RESULT_ENUM {
    //配置正确
    CONFIG_SUCC,
    //IP配置错误
    ERROR_IP,
    //端口配置错误
    ERROR_PORT,
    //错误的rakPeer端口设置
    ERROR_RAKPEER_PORT,
    //错误的最大连接数
    ERROR_MAX_CONNECT_COUNT,
    //错误的income连接数
    ERROR_MAX_INCOME_COUNT,
    //错误的音频采样频率
    ERROR_SAMPLE_RATE
            
};

//该枚举代表注册回调结果
#define REG_CALLBACK_RESULT unsigned int

enum REG_CALLBACK_RESULT_ENUM {
    //注册回调成功
    REG_CALLBACK_SUCC,
    //messageIdentify已经注册
    REG_CALLBACK_ALREADY,
    //错误的回调指针
    ERROR_CALLBACK_POINTER,
};

//该枚举代表释放注册结果
#define FREE_REG_RESULT unsigned int

enum FREE_REG_RESULT_ENUM {
    //释放成功
    FREE_REG_SUCC,
    //messageIdentify未注册
    FREE_NOT_REG
};

//该枚举代表启动网络事件循环结果
#define START_NETWORK_RESULT unsigned int

enum START_NETWORK_RESULT_ENUM {
    //启动网络引擎成功
    START_NETWORK_SUCC,
    //网络引擎未初始化
    NETWORK_NOT_INIT
};

//该枚举代表停止网络事件循环结果
#define STOP_NETWORK_RESULT unsigned int

enum STOP_NETWORK_RESULT_ENUM {
    //停止网络引擎成功
    STOP_NETWORK_SUCC,
    //网络引擎未启动
    ENGINE_NOT_START
};

//该枚举代表初始化Nat穿透插件结果
#define INIT_NAT_RESULT unsigned int

enum INIT_NAT_RESULT_ENUM {
    //初始化NAT成功
    INIT_NAT_SUCC,
    //NAT已经初始化
    INIT_NAT_AREADY,
    //miniupnpc初始化失败
    INIT_MINIUPNPC_FAIL,
};

//该枚举代表NAT穿透结果
#define OPEN_NAT_RESULT unsigned int

enum OPEN_NAT_RESULT_ENUM {
    //开启NAT功能成功
    OPEN_NAT_SUCC,
    //错误的GUID标识
    OPEN_NAT_ERROR,
    //网络未初始化
    OPEN_NAT_NOT_INIT_NETWORK,
    //主控类未初始化
    OPEN_NAT_NOT_INIT_CONTROLER,
    //NAT穿透调用失败
    OPEN_NAT_ACTION_FAIL
            
};

//该枚举代表连接端点的结果
#define CONNECT_PEER_RESULT unsigned int

enum CONNECT_PEER_RESULT_ENUM {
    //连接成功
    CONNECT_PEER_SUCC,
    //网络未初始化
    CONNECT_PEER_NOT_INIT_NETWORK,
    //主控类未初始化
    CONNECT_PEER_NOT_INIT_CONTROLER,
    //空IP地址
    CONNECT_PEER_NULL_IP,
    //RakNet内部错误，需要重点跟踪
    CONNECT_PEER_RAKNET_CORE_ERROR
};

//该枚举代表发送消息结果
#define SEND_MSG_EASY_RESULT unsigned int

enum SEND_MSG_EASY_RESULT_ENUM {
    //发送消息成功
    SEND_MSG_EASY_SUCC,
    //网络未初始化
    SEND_MSG_EASY_NOT_INIT_NETWORK,
    //主控类未初始化
    SEND_MSG_EASY_NOT_INIT_CONTROLER,
    //错误的消息长度
    SEND_MSG_EASY_ERROR_LENGTH,
    //接受端未建立连接
    SEND_MSG_PEER_NOT_CONNECT,
    //错误的输入参数
    SEND_MSG_BAD_INPUT,
    //空消息内容
    SEND_MSG_NULL_MSG,
    //空接受地址
    SEND_MSG_NULL_ADDRESS
};

#define SEND_MSG_ADVANCE_RESULT unsigned int 

enum SEND_MSG_ADVANCE_RESULT_ENUM {
    //
    SEND_MSG_ADVANCE_SUCC
};

#define INIT_VOIP_RESULT unsigned int 

enum INIT_VOIP_RESULT_ENUM {
    //
    INIT_VOIP_SUCC,
    //
    INIT_VOIP_NOT_INIT_NETWORK,
    //
    INIT_VOIP_NOT_INIT_CONTROLER,
    //
    INIT_VOIP_FMOD_ERROR,
    //
    INIT_VOIP_RAKVOICE_ERROR
};

#define START_VOIP_RESULT unsigned int 

enum START_VOIP_RESULT_ENUM {
    //
    START_VOIP_SUCC,
    //
    START_VOIP_NOT_INIT_NETWORK,
    //
    START_VOIP_NOT_INIT_CONTROLER,
    //
    START_VOIP_NULL_ERROR,
    //
    START_VOIP_PEER_NOT_CONNECT,
    //
    START_VOIP_FAIL
};

#define OPEN_SOUND_RESULT unsigned int

enum OPEN_SOUND_RESULT_ENUM {
    //
    OPEN_SOUND_SUCC,
    //
    OPEN_SOUND_NOT_INIT_NETWORK,
    //
    OPEN_SOUND_NOT_INIT_CONTROLER,
    //
    OPEN_SOUND_FAIL
            
};

#define STOP_VOIP_RESULT unsigned int 

enum STOP_VOIP_RESULT_ENUM {
    //
    STOP_VOIP_SUCC
};
#endif	/* ERRERNUMBER_H */

