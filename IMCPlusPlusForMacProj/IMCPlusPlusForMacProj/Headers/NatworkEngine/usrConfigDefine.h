/* 
 * File:   usrConfigDefine.h
 * Author: easydigital-001
 *
 * Created on 2012年11月26日, 下午3:12
 * Details:该文件是用户配置文件，
 * 需要注意配置方法,各个可以配置的条件在下列代码已经给出，
 * 用户只需要取消注释，然后定义自己想要的值即可。
 * eg.我们需要定义服务器地址，则取消//#define SERVER_IP
 * 这段代码的注释，然后后面添加服务器IP地址
 * #define SERVER_IP "127.0.0.1"
 */

#ifndef USRCONFIGDEFINE_H
#define	USRCONFIGDEFINE_H

//调试开关，注释该宏将关闭调试
#define __start_debug__

//音频功能开启开关，注释该宏表示不使用音频
#define __use_rakvoice__

//是否使用upnp功能，注释该宏表示不使用upnp
//#define __use_upnp__

//android调试开关，注释该宏表示不再android平台调试
//#define ANDROID

//服务器IP地址,IP地址以string形式给出
//eg."127.0.0.1"
#define SERVER_IP "202.75.221.149"
//#define SERVER_IP "127.0.0.1"

//服务器端口，端口以int形式给出
//eg.61111
#define SERVER_PORT 61111

//本地端口设置,端口以int形式给出，
//设置为0表示让系统随机挑选端口，
//建议使用0
//#define RAKPEER_PORT  41111

//最大总连接数限制，以unsigned short形式给出,
//取值范围1-65535，最大连接数包括2部分，outgo连接和income连接
//#define MAX_CONNECT_COUNT

//最大income连接限制，以unsigned short形式给出，
//取值范围1-65535，并且小于MAX_CONNECT_COUNT
//#define MAX_INCOME_COUNT

//音频采样频率，可以定义的值
//8000,16000,32000,推荐使用8000
//#define SAMPLE_RATE 


#endif	/* USRCONFIGDEFINE_H */

