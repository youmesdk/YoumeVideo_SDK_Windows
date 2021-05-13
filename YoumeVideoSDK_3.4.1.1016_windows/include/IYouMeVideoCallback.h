//
//  IYouMeVideoCallback.h
//  youme_voice_engine
//
//  Created by fire on 2017/3/27.
//  Copyright © 2017年 Youme. All rights reserved.
//

#ifndef IYouMeFrameCallback_h
#define IYouMeFrameCallback_h
#include <stdint.h>
#include <string>
#include "YouMeConstDefine.h"

//废弃不用
//class IYouMeVideoCallback
//{
//public:
//    virtual void frameRender(int renderId, int nWidth, int nHeight, int nRotationDegree, int nBufSize, const void * buf) = 0;
//    virtual void frameRenderGLES(int renderId, int nWidth, int nHeight, int nRotationDegree, const void* buf) = 0;
//};

class IYouMeVideoFrameCallback {
public:
    //软件处理方式回调YUV数据格式，android不支持硬编码机型和pc回调 fmt:VIDEO_FMT_YUV420P
    virtual void onVideoFrameCallback(const char* userId, void * data, int len, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallback(void * data, int len, int width, int height, int fmt, uint64_t timestamp){};
	virtual void onVideoFramePreviewCallback(void * data, int len, int width, int height, int fmt, uint64_t timestamp, int rotation,int mirror){};
    
    //ios 硬件处理方式回调，目前所有iphone ios>=8.0机型兼容，fmt:VIDEO_FMT_CVPIXELBUFFER
	virtual void onVideoFrameCallbackGLESForIOS(const char* userId, void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallbackGLESForIOS(void* pixelBuffer, int width, int height, int fmt, uint64_t timestamp){};
 
    //android 硬件处理方式回调，支持硬编码机型回调，fmt：VIDEO_FMT_TEXTURE ，VIDEO_FMT_TEXTURE_OES
	virtual void onVideoFrameCallbackGLESForAndroid(const char* userId, int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp){};
    virtual void onVideoFrameMixedCallbackGLESForAndroid(int textureId, float* matrix, int width, int height, int fmt, uint64_t timestamp){};
  
    //自定义滤镜
    virtual int  onVideoRenderFilterCallback(int textureId, int width, int height, int rotation, int mirror){return 0;};
};

class IYouMeAudioFrameCallback {
public:
	virtual void onAudioFrameCallback(const char* userId, void* data, int len, uint64_t timestamp) = 0;
    virtual void onAudioFrameMixedCallback(void* data, int len, uint64_t timestamp) = 0;
};

class IYouMeAVStatisticCallback
{
public:
    virtual void onAVStatistic( YouMeAVStatisticType type,  const char* userID,  int value ) = 0 ;
};


class IYouMeAVStatisticNewCallback
{
public:
    virtual void onAVStatisticNew( YouMeAVStatisticType type,  const char* userID,  int value, const char* param) = 0 ;
};

#endif /* IYouMeFrameCallback_h */
