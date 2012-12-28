/* 
 * File:   debug.h
 * Author: easydigital-001
 *
 * Created on 2012年7月10日, 下午1:56
 * Details:file to debug
 */

#ifndef DEBUG_H
#define	DEBUG_H
#include <stdio.h>
#include "privateDefine.h"

#ifdef	__cplusplus
extern "C" {
#endif

    enum {
        DEBUG_ALL_OPEN,
        DEBUG_PACKET,
        DEBUG_INFO,
        DEBUG_CONFIG,
        DEBUG_ERROR,
        DEBUG_ALL_CLOSE
    };
#define DEBUG_LEVEL DEBUG_INFO
#define IS_NEED_FILE_INFO DEBUG_ALL_CLOSE

#ifdef __start_debug__
#ifdef ANDROID
#define debug_(LEVEL,...)\
do\
{\
if(LEVEL >= DEBUG_LEVEL)\
{__android_log_print(ANDROID_LOG_INFO, "JNIMsg", __VA_ARGS__);\
if(LEVEL >= IS_NEED_FILE_INFO)\
{__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "file is %s,line is %s\n", __FILE__, __LINE__);}}\
}\
while(0)
#else
#define debug_(LEVEL,...)\
do\
{\
if(LEVEL >= DEBUG_LEVEL) {printf(__VA_ARGS__);\
if(LEVEL >= IS_NEED_FILE_INFO) {printf("file is %s, line is %d\n", __FILE__, __LINE__);}}\
}\
while(0)
#endif
#else
#define debug_(LEVEL,...)
#endif

#ifdef ANDROID
#define uprintf(...) __android_log_print(ANDROID_LOG_INFO, "JNIMsg", __VA_ARGS__);
#else
#define uprintf(...) printf(__VA_ARGS__);
#endif

#define interface__ //表示即将定义的是接口

#define getter__     //表示即将定义的是获取器

#define setter__     //表示即将定义的是设置器

#define private_method__     //表示即将定义的是私有方法

#define function_return_value__ //表示即将定义的是函数返回值见errornumber.h

#define flags__      //表示即将定义的是标志

#define forbid__     //表示即将定义的构造函数禁止调用

#define test__       //表示即将定义的成员为调试所使用，禁止调用

    typedef void (*func_pointer)(unsigned char *, unsigned int, char *);

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */
