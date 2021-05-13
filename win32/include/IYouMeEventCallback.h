//
//  IYouMeEventCallback.h
//  youme_voice_engine
//
//  Created by fire on 2016/12/14.
//  Copyright © 2016年 Youme. All rights reserved.
//

#ifndef IYouMeEventCallback_h
#define IYouMeEventCallback_h

#include "YouMeConstDefine.h"
#include <list>
#include <string>

class IYouMeEventCallback
{
public:
    virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param) = 0;
};

class IYouMePcmCallback
{
public:
    //需要先调用setPcmCallBackEnable
    //远端pcm数据回调
    virtual void onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) = 0;
    //本地录音pcm数据回调
    virtual void onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) = 0;
    //远端pcm和本地录音pcm的混合pcm数据回调
    virtual void onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) = 0;
};

class IYouMeTranscriberCallback
{
public:
	virtual void onSentenceBegin( std::string userid , int sentenceIndex) = 0 ;
	virtual void onSentenceEnd(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "") = 0;
	virtual void onSentenceChanged(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "") = 0;
};

class IYouMeTranslateCallback
{
public:
    /*
     * 功能：文本翻译回调
     * @param errorcode：错误码
     * @param requestID：请求ID（与translateText接口输出参数requestID一致）
     * @param text：翻译结果
     * @param srcLangCode：源语言编码
     * @param destLangCode：目标语言编码
     */
    virtual void onTranslateTextComplete(YouMeErrorCode errorcode, unsigned int requestID, const std::string& text, YouMeLanguageCode srcLangCode, YouMeLanguageCode destLangCode) = 0 ;
};

class IYouMeVideoPreDecodeCallback
{
public:
    /*
     * 功能：视频数据回调（需要先调用setVideoPreDecodeCallBackEnable）
     * @param userId: 用户ID
     * @param data: 视频数据
     * @param dataSizeInByte: 视频数据长度 
     * @param timestamp: 视频时间戳
     * @param type: 视频数据类型，0: h264; 1: yuv420;
     */
    virtual void onVideoPreDecode(const char* userId, void* data, int dataSizeInByte, unsigned long long timestamp, int type) = 0;
};

class IRestApiCallback{
public:
    virtual void onRequestRestAPI( int requestID, const YouMeErrorCode &iErrorCode, const char* strQuery, const char*  strResult ) = 0;
};

struct MemberChange{
    const char* userID;
    bool isJoin;
};


class IYouMeMemberChangeCallback
{
public:
    virtual void onMemberChange( const char* channel, const char* listMemberChangeJson, bool bUpdate ) = 0 ;
    virtual void onMemberChange( const char*  channel, const char* userID,bool isJoin, bool bUpdate) { } ;
};


class IYouMeChannelMsgCallback
{
public:
	virtual void onBroadcast(const YouMeBroadcast bc, const char* channel, const char* param1, const char* param2, const char* strContent) = 0;
};

class IYouMeCustomDataCallback
{
public:
	virtual void OnCustomDataNotify(const void* pData, int iDataLen, unsigned long long ulTimeSpan) = 0;
};

#endif /* IYouMeEventCallback_h */
