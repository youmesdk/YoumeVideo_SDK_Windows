/**
 @file IYouMeVoiceEngine.h
 @brief 游密音频通话引擎接口
 
 该文件主要用于定义游密音频通话引擎的接口
 
 @version 1.0 Copyright(c) 2015-2020 YOUME All rights reserved.
 @author YOUME

 */
 
#ifndef cocos2d_x_sdk_IYouMeVoiceEngine_h
#define cocos2d_x_sdk_IYouMeVoiceEngine_h
#include <string>
#include <vector>
#include "IYouMeEventCallback.h"
#include "IYouMeVideoCallback.h"
#include "YouMeConstDefine.h"

#ifdef WIN32
#include <wtypes.h>
#ifdef YOUMEDLL_EXPORTS
#define YOUMEDLL_API __declspec(dllexport)
#else
#define YOUMEDLL_API __declspec(dllimport)
#endif
#else
#define YOUMEDLL_API __attribute ((visibility("default")))
#endif
class YOUMEDLL_API IYouMeVoiceEngine
{
public:
    /**
     *  功能描述:获取引擎实例指针
     *
     *  @return 引擎实例指针
     */
    static IYouMeVoiceEngine *getInstance ();
    
    /**
     *  功能描述:销毁引擎实例，释放内存
     *
     *  @return 无
     */
    static void destroy ();

public:
    /**
     *  功能描述:初始化引擎
     *
     *  @param pCommonCallback:通用回调类地址，需要继承IYouMeCommonCallback并实现其中的回调函数
     *  @param pConferenceCallback:会议回调类地址，需要继承IYouMeConferenceCallback并实现其中的回调函数
     *  @param strAPPKey:在申请SDK注册时得到的App Key，也可凭账号密码到http://gmx.dev.net/createApp.html查询
     *  @param strAPPSecret:在申请SDK注册时得到的App Secret，也可凭账号密码到http://gmx.dev.net/createApp.html查询
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode init (IYouMeEventCallback * pEventCallback, const char* pAPPKey, const char* pAPPSecret,
                         YOUME_RTC_SERVER_REGION serverRegionId, const char* pExtServerRegionName);

    /**
     *  功能描述:设置身份验证的token和用户加入房间的时间
     *  @param pToken: 身份验证用token，设置为NULL或者空字符串，清空token值。
     *  @param uTimeStamp: 用户加入房间的时间
     *  @return 无
     */
    void setToken( const char* pToken, uint32_t uTimeStamp = 0 );
    
    /**
     *  功能描述:反初始化引擎
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */

    YouMeErrorCode unInit ();

	/**
	*  功能描述:判断是否初始化完成
	*
	*  @return true——完成，false——还未完成
	*/
	// 是否初始化成功
	bool isInited();

    /**
     *  功能描述: 设置用户自定义Log路径
     *  @param pFilePath Log文件的路径
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setUserLogPath(const char* pFilePath);
    

	/**
	*  功能描述: 设置是否使用TCP 传输语音视频数据，必须在进入房间之前调用
	*  @param iUseTCP 默认情况下使用UDP， 在某些UDP被禁用的网络可以切换成TCP，但是TCP模式下延迟等将不可控，除非必要，不要调用
	*  @return YOUME_SUCCESS - 成功
	*          其他 - 具体错误码
	*/
	YouMeErrorCode setTCPMode(int iUseTCP);


    /**
     *  功能描述:设置服务器区域
     *  @param region: YOUME_RTC_SERVER_REGION枚举可选的服务器区域
     *  @return 无
     */
    void setServerRegion(YOUME_RTC_SERVER_REGION regionId, const char* extRegionName, bool bAppend);
    
    /**
     *  功能描述:切换语音输出设备
     *  默认输出到扬声器，在加入房间成功后设置（iOS受系统限制，如果已释放麦克风则无法切换到听筒）
     *
     *  @param bOutputToSpeaker:true——使用扬声器，false——使用听筒
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOutputToSpeaker (bool bOutputToSpeaker);
    
    /**
     *  功能描述:设置扬声器静音
     *
     *  @param bOn:true——静音，false——取消静音
     *  @return 无
     */
    void setSpeakerMute (bool bOn);

    /**
     *  功能描述:获取扬声器静音状态
     *
     *  @return true——静音，false——没有静音
     */
    bool getSpeakerMute ();

    /**
     *  功能描述:获取麦克风静音状态
     *
     *  @return true——静音，false——没有静音
     */
    bool getMicrophoneMute ();

    /**
     *  功能描述:设置麦克风静音
     *
     *  @param bOn:true——静音，false——取消静音
     *  @return 无
     */
    void setMicrophoneMute (bool mute);
    
    /**
     *  功能描述:设置是否通知其他人自己的开关麦克风和扬声器的状态
     *
     *  @param bAutoSend:true——通知，false——不通知
     *  @return 无
     */
    void setAutoSendStatus( bool bAutoSend );

    /**
     *  功能描述:获取音量大小,此音量值为程序内部的音量，与系统音量相乘得到程序使用的实际音量
     *
     *  @return 音量值[0,100]
     */
    unsigned int getVolume ();

    /**
     *  功能描述:设置音量，取值范围是[0-100] 100表示最大音量， 默认音量是100
     *
     *  @return 无
     */
    void setVolume (const unsigned int &uiVolume);

    /**
     *  功能描述:是否可使用移动网络
     *
     *  @return true-可以使用，false-禁用
     */
    bool getUseMobileNetworkEnabled ();

    /**
     *  功能描述:启用/禁用移动网络
     *
     *  @param bEnabled:true-可以启用，false-禁用，默认禁用
     *
     *  @return 无
     */
    void setUseMobileNetworkEnabled (bool bEnabled);

    /**
     *  功能描述:设置本地连接信息，用于p2p传输，本接口在join房间之前调用
     *
     *  @param pLocalIP:本端ip
     *  @param iLocalPort:本端数据端口
     *  @param pRemoteIP:远端ip
     *  @param iRemotePort:远端数据端口
     *  @param iNetType: 0:ipv4, 1:ipv6, 目前仅支持ipv4
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setLocalConnectionInfo(const char* pLocalIP, int iLocalPort, const char* pRemoteIP, int iRemotePort, int iNetType);

    /**
     *  功能描述:清除本地局域网连接信息，强制server转发
     *
     *
     *  @return 无
     */
    void clearLocalConnectionInfo();

    /**
     *  功能描述:设置是否切换server通路
     *
     *  @param enable: 设置是否切换server通路标志
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setRouteChangeFlag(bool enable);
    
    //---------------------多人语音接口---------------------//

    /**
     *  功能描述:加入语音频道
     *
     * @param strUserID:用户ID，要保证全局唯一
     *  @param strRoomID:频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */

    /**
     *  功能描述:加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）
     *
     *  @param pUserID: 用户ID，要保证全局唯一
     *  @param pChannelID: 频道ID，要保证全局唯一
     *  @param eUserRole: 用户角色，用于决定讲话/播放背景音乐等权限
     *  @param bVideoAutoRecv: 进入房间成功后，是否自动接收视频，默认为true
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, bool bVideoAutoRecv = true);

    
    /**
     *  功能描述：加入语音频道（多频道模式，可以同时在多个语音频道里面）
     *
     *  @param pUserID: 用户ID，要保证全局唯一
     *  @param pChannelID: 频道ID，要保证全局唯一
     *  @param eUserRole: 用户角色，用于决定讲话/播放背景音乐等权限
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode joinChannelMultiMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole);
    
    /**
     *  功能描述:加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）
     *
     *  @param pUserID: 用户ID，要保证全局唯一
     *  @param pChannelID: 频道ID，要保证全局唯一
     *  @param eUserRole: 用户角色，用于决定讲话/播放背景音乐等权限
     *  @param pJoinAppKey: 加入房间用额外的appkey
     *  @param bVideoAutoRecv: 进入房间成功后，是否自动接收视频，默认为true
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, const char* pJoinAppKey, bool bVideoAutoRecv = true);
    
    /**
     *  功能描述：对指定频道说话
     *
     *  @param pChannelID: 频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode speakToChannel(const char* pChannelID);
    
    /**
     *  功能描述:退出多频道模式下的某个语音频道
     *
     *  @param pChannelID:频道ID，要保证全局唯一
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode leaveChannelMultiMode (const char* pChannelID);
    
    /**
     *  功能描述:退出所有语音频道
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode leaveChannelAll ();
    
	/**
	*  功能描述:切换身份(仅支持单频道模式，进入房间以后设置)
	*
	*  @param eUserRole: 用户身份
	*
	*  @return 错误码，详见YouMeConstDefine.h定义
	*/
	YouMeErrorCode setUserRole(YouMeUserRole_t eUserRole);

	/**
	*  功能描述:获取身份(仅支持单频道模式)
	*
	*  @return 身份定义，详见YouMeConstDefine.h定义
	*/
	YouMeUserRole_t getUserRole();


	/**
	*  功能描述:查询是否在某个语音频道内
	*
	*  @param pChannelID:要查询的频道ID
	*
	*  @return true——在频道内，false——没有在频道内
	*/
	// 
	bool isInChannel(const char* pChannelID);
    
    /**
     *  功能描述:查询是否在语音频道内
     *
     *  @return true——在频道内，false——没有在频道内
     */
    //
    bool isInChannel();

    /**
     *  功能描述:查询频道的用户列表
     *  @param channelID:要查询的频道ID
     *  @param maxCount:想要获取的最大数量，-1表示获取全部
     *  @param notifyMemChagne: 其他用户进出房间时，是否要收到通知
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode getChannelUserList( const char*  channelID, int maxCount, bool notifyMemChange );
    
    /**
     *  功能描述:控制其他人的麦克风开关
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param mute: true 静音对方的麦克风，false 取消静音对方麦克风
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOtherMicMute (const char* pUserID,bool mute);
    
    /**
     *  功能描述:控制其他人的扬声器开关
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param mute: true 静音对方的扬声器，false 取消静音对方扬声器
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setOtherSpeakerMute (const char* pUserID,bool mute);
    
    /**
     *  功能描述:选择消除其他人的语音
     *
     *  @param pUserID:用户ID，要保证全局唯一
     *  @param on: false屏蔽对方语音，true取消屏蔽
     *
     *  @return 错误码，详见YouMeConstDefine.h定义
     */
    YouMeErrorCode setListenOtherVoice (const char* pUserID, bool on );

	/**
	* 功能描述: 视频数据输入，软件处理方式(七牛接口，房间内其它用户会收到YOUME_EVENT_OTHERS_VIDEO_INPUT_START事件)
	* @param data 视频帧数据
	* @param len 视频数据大小
	* @param width 视频图像宽
	* @param height 视频图像高
	* @param fmt 视频格式
    * @param rotation 视频角度
    * @param mirror 镜像
	* @param timestamp 时间戳
    * @param streamID 视频流ID，仅在视频格式 fmt 为 VIDEO_FMT_H264和VIDEO_FMT_ENCRYPT 时有效
	* @return YOUME_SUCCESS - 成功
	*         其他 - 具体错误码
	*/
	YouMeErrorCode inputVideoFrame(void* data, int len, int width, int	height, int fmt, int rotation, int mirror, uint64_t timestamp, int streamID = 0);

    /**
    * 功能描述: 共享视频数据输入，自带preview，不需要sdk来进行预览，和摄像头视频流一起发送出去
    * @param data 视频帧数据
    * @param len 视频数据大小
    * @param width 视频图像宽
    * @param height 视频图像高
    * @param fmt 视频格式
    * @param rotation 视频角度
    * @param mirror 镜像
    * @param timestamp 时间戳
    * @return YOUME_SUCCESS - 成功
    *         其他 - 具体错误码
    */    
    YouMeErrorCode inputVideoFrameForShare(void* data, int len, int width, int  height, int fmt, int rotation, int mirror, uint64_t timestamp);
    
    /**
     * 功能描述: ios摄像头视频数据输入，硬件处理方式
     * @param pixelbuffer CVPixelBuffer
     * @param width 视频图像宽
     * @param height 视频图像高
     * @param fmt 视频格式
     * @param rotation 视频角度
     * @param mirror 镜像
     * @param timestamp 时间戳
     * @return YOUME_SUCCESS - 成功
     *         其他 - 具体错误码
     */
    YouMeErrorCode inputVideoFrameForIOS(void* pixelbuffer, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);
    
    /**
     * 功能描述: ios共享/录屏视频输入，无预览，硬件处理方式， AppExtension建议用此接口输入视频数据
     * @param pixelbuffer CVPixelBuffer
     * @param width 视频图像宽
     * @param height 视频图像高
     * @param fmt 视频格式
     * @param rotation 视频角度
     * @param mirror 镜像
     * @param timestamp 时间戳
     * @return YOUME_SUCCESS - 成功
     *         其他 - 具体错误码
     */
    YouMeErrorCode inputVideoFrameForIOSShare(void* pixelbuffer, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);

 #if ANDROID
    /**
     * 功能描述: android视频数据输入，硬件处理方式
     * @param textureId 纹理id
     * @param matrix 纹理矩阵
     * @param width 视频图像宽
     * @param height 视频图像高
     * @param fmt 视频格式
     * @param rotation 视频角度
     * @param mirror 镜像
     * @param timestamp 时间戳
     * @return YOUME_SUCCESS - 成功
     *         其他 - 具体错误码
     */
    YouMeErrorCode inputVideoFrameForAndroid(int textureId, float* matrix, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);

    /**
     * 功能描述: android共享视频数据输入，硬件处理方式
     * @param textureId 纹理id
     * @param matrix 纹理矩阵
     * @param width 视频图像宽
     * @param height 视频图像高
     * @param fmt 视频格式
     * @param rotation 视频角度
     * @param mirror 镜像
     * @param timestamp 时间戳
     * @return YOUME_SUCCESS - 成功
     *         其他 - 具体错误码
     */
    YouMeErrorCode inputVideoFrameForAndroidShare(int textureId, float* matrix, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);
#endif
    /**
     * 功能描述: 停止视频数据输入（在inputVideoFrame之后调用，房间内其它用户会收到YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP事件)
     * @return YOUME_SUCCESS - 成功
     *         其他 - 具体错误码
     */
    YouMeErrorCode stopInputVideoFrame();
    
    /**
      * 功能描述: 停止共享数据输入（在inputVideoFrameForShare之后调用，房间内其它用户会收到YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP事件)
      * @return YOUME_SUCCESS - 成功
      *         其他 - 具体错误码
      */
    YouMeErrorCode stopInputVideoFrameForShare();
    
    /**
     *  功能描述: (七牛接口)将提供的音频数据混合到麦克风或者扬声器的音轨里面。
     *  @param data 指向PCM数据的缓冲区
     *  @param len  音频数据的大小
     *  @param timestamp 时间戳
	 * 	@param channels  声道数，1:单声道，2:双声道，其它非法
	 *  @param binterleaved 音频数据打包格式（仅对双声道有效）
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode inputAudioFrame(void* data, int len, uint64_t timestamp, int channels = 1, int bInterleaved = 0);

    /**
     *  功能描述: 将多路音频数据流混合到麦克风或者扬声器的音轨里面。
     *  @param streamId  音频数据的流id
     *  @param data 指向PCM数据的缓冲区
     *  @param len  音频数据的大小
     *  @param frameInfo 音频数据的格式信息
     *  @param timestamp 时间戳
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode inputAudioFrameForMix(int streamId, void* data, int len, YMAudioFrameInfo frameInfo, uint64_t timestamp);
    
    /**
     *  功能描述: 播放背景音乐，并允许选择混合到扬声器输出麦克风输入
     *  @param pFilePath 音乐文件的路径
     *  @param bRepeat 是否重复播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode playBackgroundMusic(const char* pFilePath, bool bRepeat);

    /**
     *  功能描述: 如果当前正在播放背景音乐的话，暂停播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseBackgroundMusic();
    
    /**
     *  功能描述: 如果当前背景音乐处于暂停状态的话，恢复播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeBackgroundMusic();
    
    /**
     *  功能描述: 如果当前正在播放背景音乐的话，停止播放
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopBackgroundMusic();

	/**
	*  功能描述:背景音乐是否在播放
	*
	*  @return true——正在播放，false——没有播放
	*/
	bool isBackgroundMusicPlaying();

    /**
     *  功能描述: 设置背景音乐播放的音量
     *  @param vol 背景音乐的音量，范围 0-100
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setBackgroundMusicVolume(int vol);

    /**
     *  功能描述: 设置是否用耳机监听自己的声音或背景音乐，当不插耳机或外部输入模式时，这个设置不起作用
     *  @param micEnabled 是否监听麦克风 true 监听，false 不监听
     *  @param bgmEnabled 是否监听背景音乐 true 监听，false 不监听
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true);
    
    /**
     *  功能描述: 设置是否开启主播混响模式
     *  @param enabled, true 开启，false 关闭
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setReverbEnabled(bool enabled);
    
    /**
     *  功能描述: 设置是否开启语音检测回调
     *  @param enabled, true 开启，false 关闭
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVadCallbackEnabled(bool enabled);

    /**
     *  功能描述: 设置是否开启讲话音量回调, 并设置相应的参数
     *  @param maxLevel, 音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数。
     *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
     *                   设 0 表示关闭回调。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setMicLevelCallback(int maxLevel);
    
    /**
     *  功能描述: 设置是否开启远端语音音量回调, 并设置相应的参数
     *  @param maxLevel, 音量最大时对应的级别，最大可设100。
     *                   比如你只在UI上呈现10级的音量变化，那就设10就可以了。
     *                   设 0 表示关闭回调。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setFarendVoiceLevelCallback(int maxLevel);
    
    /**
     *  功能描述: 设置当麦克风静音时，是否释放麦克风设备，在初始化之后、加入房间之前调用
     *  @param enabled,
     *      true 当麦克风静音时，释放麦克风设备，此时允许第三方模块使用麦克风设备录音。在Android上，语音通过媒体音轨，而不是通话音轨输出。
     *      false 不管麦克风是否静音，麦克风设备都会被占用。
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setReleaseMicWhenMute(bool enabled);
    
    /**
     *  功能描述: 设置插入耳机时，是否自动退出系统通话模式(禁用手机硬件提供的回声消除等信号前处理)
     *          系统提供的前处理效果包括回声消除、自动增益等，有助于抑制背景音乐等回声噪音，减少系统资源消耗
     *          由于插入耳机可从物理上阻断回声产生，故可设置禁用该效果以保留背景音乐的原生音质效果
     *          注：Windows和macOS不支持该接口
     *  @param enabled,
     *      true 当插入耳机时，自动禁用系统硬件信号前处理，拔出时还原
     *      false 插拔耳机不做处理
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setExitCommModeWhenHeadsetPlugin(bool enabled);

    /**
     *  功能描述: 暂停通话，释放麦克风等设备资源
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode pauseChannel();

    /**
     *  功能描述: 恢复通话
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resumeChannel();
    
    /**
     *  功能描述: 设置当前录音的时间戳
     *  @return  None
     */
    void setRecordingTimeMs(unsigned int timeMs);
    
    /**
     *  功能描述: 设置当前播放的时间戳
     *  @return  None
     */
    void setPlayingTimeMs(unsigned int timeMs);
    
    /**
     *  功能描述: 设置PCM数据回调对象
     *  @param  pcmCallback 回调方法
     *  @param  flag:有3种pcm回调，分别为远端pcm,本地录音pcm及远端和录音的混合pcm。flag用于标记打开哪几种回调，形如PcmCallbackFlag_Remote| PcmCallbackFlag_Record|PcmCallbackFlag_Mix。
     *  @param  outputToSpeaker 是否扬声器静音:true 不静音;false 静音
     *  @param  nOutputSampleRate pcm callback重采样的采样率
     *  @param  nOutputChannel pcm callback重采样的通道数
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setPcmCallbackEnable(IYouMePcmCallback* pcmCallback, int flag,  bool bOutputToSpeaker = true, int nOutputSampleRate=16000, int nOutputChannel=1);
    
    /**
     *  功能描述: 设置是否开启会议纪要
     *  @param  enable: true,开启，false，不开启，默认不开启
     *  @param  transcriberCallback 回调方法
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setTranscriberEnabled(bool enable, IYouMeTranscriberCallback* transcriberCallback );

    /**
     *  功能描述: 设置是否回调视频解码前H264数据，需要在加入房间之前设置
     *  @param  preDecodeCallback 回调方法
     *  @param  needDecodeandRender 是否需要解码并渲染:true 需要;false 不需要
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoPreDecodeCallbackEnable(IYouMeVideoPreDecodeCallback* preDecodeCallback, bool needDecodeandRender = true);

	/**
     *  功能描述: 设置是否回调视频编码参数
     *  @param  isReport 是否需要上报true 需要;false 不需要
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoEncodeParamCallbackEnable(bool isReport);

    /**
     *  功能描述:获取SDK 版本号
     *
     *
     *  @return 整形数字版本号
     */
    int getSDKVersion ();
	
	  /**
     *  功能描述:Rest API , 向服务器请求额外数据
     *  @param requestID: 回传id,回调的时候传回，标识消息
     *  @param strCommand: 请求的命令字符串
     *  @param strQueryBody: 请求需要的数据,json格式，内容参考restAPI
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode  requestRestApi( const char* strCommand , const char* strQueryBody , int* requestID = NULL  );
    
	/**
     *  功能描述:requestRestApi的回调消息
     *  @param cb: requestRestApi的回调， 需要继承IRestApiCallback并实现其中的回调函数
     *
     *  @return None
     */
    void setRestApiCallback(IRestApiCallback* cb );
    
    /**
     *  功能描述:getChannelUserList的回调消息
     *  @param cb: getChannelUserList的回调， 需要继承IYouMeMemberChangeCallback并实现其中的回调函数
     *
     *  @return None
     */
    void setMemberChangeCallback( IYouMeMemberChangeCallback* cb );

	/**
	 * 功能描述:    设置频道内的广播消息回调(抢麦、连麦等）
	 * @param cb: 抢麦、连麦等的广播回调，需要继承IYouMeNotifyCallback并实现其中的回调函数
	 * @return   void: 
	 */
	 void setNotifyCallback(IYouMeChannelMsgCallback* cb);

	//---------------------抢麦接口---------------------//
	 /**
	 * 功能描述:    抢麦相关设置（抢麦活动发起前调用此接口进行设置）
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param int mode: 抢麦模式（1:先到先得模式；2:按权重分配模式）
	 * @param int maxAllowCount: 允许能抢到麦的最大人数
	 * @param int maxTalkTime: 允许抢到麦后使用麦的最大时间（秒）
	 * @param unsigned int voteTime: 抢麦仲裁时间（秒），过了X秒后服务器将进行仲裁谁最终获得麦（仅在按权重分配模式下有效）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	 YouMeErrorCode setGrabMicOption(const char* pChannelID, int mode, int maxAllowCount, int maxTalkTime, unsigned int voteTime);

	/**
	 * 功能描述:    发起抢麦活动
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	YouMeErrorCode startGrabMicAction(const char* pChannelID, const char* pContent);

	/**
	 * 功能描述:    停止抢麦活动
	 * @param const char * pChannelID: 抢麦活动的频道id
	 * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	YouMeErrorCode stopGrabMicAction(const char* pChannelID, const char* pContent);

	 /**
	  * 功能描述:    发起抢麦请求
	  * @param const char * pChannelID: 抢麦的频道id
	  * @param int score: 积分（权重分配模式下有效，游戏根据自己实际情况设置）
	  * @param bool isAutoOpenMic: 抢麦成功后是否自动开启麦克风权限
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode requestGrabMic(const char* pChannelID, int score, bool isAutoOpenMic, const char* pContent);

	 /**
	  * 功能描述:    释放抢到的麦
	  * @param const char * pChannelID: 抢麦活动的频道id
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode releaseGrabMic(const char* pChannelID);


	//---------------------连麦接口---------------------//
	 /**
	 * 功能描述:    连麦相关设置（角色是频道的管理者或者主播时调用此接口进行频道内的连麦设置）
	 * @param const char * pChannelID: 连麦的频道id
	 * @param int waitTimeout: 等待对方响应超时时间（秒）
	 * @param int maxTalkTime: 最大通话时间（秒）
	 * @return   YOUME_SUCCESS - 成功
	 *          其他 - 具体错误码
	 */
	 YouMeErrorCode setInviteMicOption(const char* pChannelID, int waitTimeout, int maxTalkTime);

	 /**
	  * 功能描述:    发起与某人的连麦请求（主动呼叫）
	  * @param const char * pUserID: 被叫方的用户id
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode requestInviteMic(const char* pChannelID, const char* pUserID, const char* pContent);

	 /**
	  * 功能描述:    对连麦请求做出回应（被动应答）
	  * @param const char * pUserID: 主叫方的用户id
	  * @param bool isAccept: 是否同意连麦
	  * @param const char * pContent: 游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode responseInviteMic(const char* pUserID, bool isAccept, const char* pContent);

	 /**
	  * 功能描述:    停止连麦
	  * @return   YOUME_SUCCESS - 成功
	  *          其他 - 具体错误码
	  */
	 YouMeErrorCode stopInviteMic();
	 
	/**
     * 功能描述:   向房间广播消息
     * @param pChannelID: 广播房间
     * @param pContent: 广播内容-文本串
     * @param pUserID: 接收端用户ID
     * @param requestID:返回消息标识，回调的时候会回传该值
     * @return   YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
	YouMeErrorCode  sendMessage( const char* pChannelID,  const char* pContent, const char* pUserID, int* requestID );
    
    /**
     * 功能描述:   设置是否由外部输入音视频
     * @param bInputModeEnabled: true:外部输入模式，false:SDK内部采集模式
     */
    void setExternalInputMode( bool bInputModeEnabled );
    
	/**
     *  功能描述: 设置是否开启视频编码器
     *  @param pFilePath: yuv文件的绝对路径
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode openVideoEncoder(const char* pFilePath);
    
    
    /**
     *  功能描述: 创建渲染
     *  @param : userId 用户ID
     *  @return 大于等于0 - renderId
     *          小于0 - 具体错误码
     */
    int createRender(const char * userId);
    
    /**
     *  功能描述: 删除渲染
     *  @param : renderId
     *  @return 等于0 - success
     *          小于0 - 具体错误码
     */
    int deleteRender(int renderId);
    
    /**
     *  功能描述: 删除渲染
     *  @param : userId
     *  @return 等于0 - success
     *          小于0 - 具体错误码
     */
    int deleteRender(const char * userId);
    
    /**
     *  功能描述: 屏蔽视频流
     *  @param : userId 用户ID
     *  @param : mask 1 屏蔽, 0 恢复
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode maskVideoByUserId(const char * userId, bool mask);
    
    /***
     * 功能描述：设置视频回调
     * @param cb
     * @return YOUME_SUCCESS  - 成功
     *         其它           - 具体错误码
     */
    YouMeErrorCode setVideoCallback(IYouMeVideoFrameCallback * cb);
    
    /**
     *  功能描述: 开始camera capture
     *  @param
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode startCapture();
    
    /**
     *  功能描述: 停止camera capture
     *  @param
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopCapture();
  
    /**
     *  功能描述: 设置预览帧率
     *  @param  fps:帧率（1-60），默认15帧
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoPreviewFps(int fps);

    /**
     *  功能描述: 设置帧率
     *  @param  fps:帧率（1-60），默认15帧
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoFps(int fps);

    /**
     *  功能描述: 设置小流帧率 (如果大于大流帧率，以大流帧率为准)
     *  @param  fps:帧率（1-30），默认15帧
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoFpsForSecond(int fps);

    /**
     *  功能描述: 设置共享视频帧率
     *  @param  fps:帧率（1-30），默认15帧
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoFpsForShare(int fps);

    /**
     *  功能描述: 设置本地视频渲染回调的分辨率
     *  @param width:宽
     *  @param height:高
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoLocalResolution(int width, int height);
    
    /**
     *  功能描述: 设置是否前置摄像头
     *  @param
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setCaptureFrontCameraEnable(bool enable);
    
    /**
     *  功能描述: 切换前置/后置摄像头
     *  @param
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode switchCamera();
    
    /**
     *  功能描述: 权限检测结束后重置摄像头
     *  @param
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resetCamera();
    
    
    /**
     *  功能描述: 把某人踢出房间
     *  @param  pUserID: 被踢的用户ID
     *  @param  pChannelID: 从哪个房间踢出
     *  @param  lastTime: 踢出后，多长时间内不允许再次进入
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode kickOtherFromChannel( const char* pUserID, const char* pChannelID , int lastTime );
    
    /**
     *  功能描述: 设置日志等级
     *  @param consoleLevel: 控制台日志等级
     *  @param fileLevel: 文件日志等级
     */
    void setLogLevel( YOUME_LOG_LEVEL consoleLevel, YOUME_LOG_LEVEL fileLevel);
    
    /**
     *  功能描述: 设置外部输入模式的语音采样率
     *  @param inputSampleRate: 输入语音采样率
     *  @param mixedCallbackSampleRate: mix后输出语音采样率
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setExternalInputSampleRate( YOUME_SAMPLE_RATE inputSampleRate, YOUME_SAMPLE_RATE mixedCallbackSampleRate);
    
    /**
     *  功能描述: 设置视频网络传大小流自动调整
     *  @param mode: 0: 自动调整；1: 上层设置大小流接收选择
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoNetAdjustmode( int mode );

    /**
     *  功能描述: 设置视频网络传输过程的分辨率,高分辨率
     *  @param width:宽
     *  @param height:高
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoNetResolution( int width, int height );
    
    /**
     *  功能描述: 设置视频网络传输过程的分辨率，低分辨率
     *  @param width:宽
     *  @param height:高
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoNetResolutionForSecond( int width, int height );

    /**
     *  功能描述: 设置共享视频网络传输过程的分辨率
     *  @param width:宽
     *  @param height:高
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoNetResolutionForShare( int width, int height );

    /**
     *  功能描述: 设置音视频统计数据时间间隔
     *  @param interval: 时间间隔，单位毫秒
     */
    void setAVStatisticInterval( int interval  );
    
    /**
     *  功能描述: 设置Audio,Video的统计数据的回调接口
     *  @param cb: 需要继承IYouMeAVStatisticCallback并实现其中的回调函数
     *
     *  @return None
     */
    void setAVStatisticCallback( IYouMeAVStatisticCallback* cb );
    
    /**
     *  功能描述: 设置Audio的传输质量
     *  @param quality: 0: low 1: high
     *
     *  @return None
     */
    void setAudioQuality( YOUME_AUDIO_QUALITY quality );
    
    /**
     *  功能描述: 设置视频数据上行的码率的上下限。
     *  @param maxBitrate: 最大码率，单位kbps.  0：使用默认值
     *  @param minBitrate: 最小码率，单位kbps.  0：使用默认值
     
     *  @return None
     *
     *  @warning:需要在进房间之前设置
     */
    void setVideoCodeBitrate( unsigned int maxBitrate,  unsigned int minBitrate );
    
    /**
     *  功能描述: 设置视频数据上行的码率的上下限,第二路(默认不传)
     *  @param maxBitrate: 最大码率，单位kbps.  0：使用默认值
     *  @param minBitrate: 最小码率，单位kbps.  0：使用默认值
     
     *  @return None
     *
     *  @warning:需要在进房间之前设置
     */
    void setVideoCodeBitrateForSecond( unsigned int maxBitrate,  unsigned int minBitrate );
    
    /**
     *  功能描述: 设置共享视频数据上行的码率的上下限
     *  @param maxBitrate: 最大码率，单位kbps.  0：使用默认值
     *  @param minBitrate: 最小码率，单位kbps.  0：使用默认值
     
     *  @return None
     *
     *  @warning:需要在进房间之前设置
     */
    void setVideoCodeBitrateForShare( unsigned int maxBitrate,  unsigned int minBitrate );

    /**
     *  功能描述: 获取视频数据上行的当前码率。
     *
     *  @return 视频数据上行的当前码率
     */
    unsigned int getCurrentVideoCodeBitrate( );
    
    /**
     *  功能描述: 设置视频编码是否采用VBR动态码率方式
     *
     *  @return None
     *
     *  @warning: 需要在进房间之前设置
     */
    YouMeErrorCode setVBR( bool useVBR );
    
    /**
     *  功能描述: 设置小流视频编码是否采用VBR动态码率方式
     *
     *  @return None
     *
     *  @warning:需要在进房间之前设置
     */
    YouMeErrorCode setVBRForSecond( bool useVBR );
    
    /**
     *  功能描述: 设置共享流视频编码是否采用VBR动态码率方式
     *
     *  @return None
     *
     *  @warning:需要在进房间之前设置
     */
    YouMeErrorCode setVBRForShare( bool useVBR );

    /**
     *  功能描述: 设置视频数据是否同意开启硬编硬解
     *  @param bEnable: true:开启，false:不开启
     *
     *  @return None
     *
     *  @note: 实际是否开启硬解，还跟服务器配置及硬件是否支持有关，要全部支持开启才会使用硬解。并且如果硬编硬解失败，也会切换回软解。
     *  @warning:需要在进房间之前设置
     */
    void setVideoHardwareCodeEnable( bool bEnable );
    
    /**
     *  功能描述: 获取视频数据是否同意开启硬编硬解
     *  @return true:开启，false:不开启， 默认为true;
     *
     *  @note: 实际是否开启硬解，还跟服务器配置及硬件是否支持有关，要全部支持开启才会使用硬解。并且如果硬编硬解失败，也会切换回软解。
     */
    bool getVideoHardwareCodeEnable( );
    
    /**
     *  功能描述: 获取android下是否启用GL
     *  @return true:开启，false:不开启， 默认为true;
     *
     *  @note: 获取android下是否启用GL。
     */
    bool getUseGL( );
    
    /**
     *  功能描述: 设置视频无帧渲染的等待超时时间，超过这个时间会给上层回调YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN
     *  @param timeout: 超时时间，单位为毫秒
     */
    void setVideoNoFrameTimeout(int timeout);
    
    
    /**
     *  功能描述: 查询多个用户视频信息（支持分辨率）
     *  @param userList: 用户ID列表
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode queryUsersVideoInfo(std::vector<std::string>& userList);
    
    
    //用户对应分辨率
     struct userVideoInfo
     {
         std::string userId;
         int resolutionType;   //支持分辨率
     };
    
    /**
     *  功能描述: 设置多个用户视频信息（支持分辨率）
     *  @param videoinfoList: 用户对应分辨率列表
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setUsersVideoInfo(std::vector<IYouMeVoiceEngine::userVideoInfo>& videoInfoList);
    
    /**
     *  功能描述: 美颜开关，默认是关闭美颜
     *  @param open: true表示开启美颜，false表示关闭美颜
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode openBeautify(bool open) ;
    
    /**
     *  功能描述: 美颜强度参数设置
     *  @param param: 美颜参数，0.0 - 1.0 ，默认为0，几乎没有美颜效果，0.5左右效果明显
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode beautifyChanged(float param) ;
    
//    /**
//     *  功能描述: 瘦脸开关
//     *  @param param: true 开启瘦脸，false关闭，默认 false
//     *  @return YOUME_SUCCESS - 成功
//     *          其他 - 具体错误码
//     */
//    YouMeErrorCode stretchFace(bool stretch) ;
    
    /**
     *  功能描述: 调用后同步完成麦克风释放，只是为了方便使用 IM 的录音接口时切换麦克风使用权。
     *  @return bool - 成功
     */
    bool releaseMicSync();
    
    /**
     *  功能描述: 调用后恢复麦克风到释放前的状态，只是为了方便使用 IM 的录音接口时切换麦克风使用权。
     *  @return bool - true 成功
     */
    bool resumeMicSync();
 
    /**
     *  功能描述: 获取windwos/macos平台，摄像头个数
     *  @return int - 数目，摄像头id为0-count
     */
    int getCameraCount();
   
    /**
     *  功能描述: 获取windows/macos平台cameraId 对应名称
     *  @param  cameraId:摄像头id
     *  @return const char* - 成功:非空name 失败:空字符串
     */
   const char* getCameraName(int cameraId);
   
    /**
     *  功能描述: 设置windows/macos平台打开摄像头id
     *  @param  cameraId:摄像头id
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setOpenCameraId(int cameraId);
    
    /**
     *  功能描述: 获取windwos/macos平台，audio采集设备数量
     *  @return int - 数目，
     */
    int getRecordDeviceCount();
    
    /**
     *  功能描述: 获取windows/macos平台 record设备 对应信息
     *  @param  index:列表中的位置
     *  @param  deviceName:设备名称
     *  @param  deviceUid:设备唯一ID，用于设置设备
     *  @return bool - 成功:非空name 失败:空字符串
     */
    bool getRecordDeviceInfo(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceUId[MAX_DEVICE_ID_LENGTH]);
    
    /**
     *  功能描述: 设置windows/macos平台打开录音设备id
     *  @param  deviceUId: record设备的Uid
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setRecordDevice( const char* deviceUId);
    
    
    
    /**
     *  功能描述: 设置和流画布大小（不设置则默认为采集视频分辨率）
     *  @param  width:宽度
     *  @param  height:高度
     *  @return void
     */
    void setMixVideoSize(int width, int height);
    
    /**
     * 设置具体的user的视频数据在合流画面中展现的位置和尺寸。
     * @param userId
     * @param x       x
     * @param y       y
     * @param z       z (Z 值小的在前面)
     * @param width
     * @param height
     */
    void addMixOverlayVideo(const char* userId, int x, int y, int z, int width, int height);
    
    /**
     *  功能描述: 移除单个合流画面
     *  @param  userId
     *  @return void
     */
	void removeMixOverlayVideo(const char* userId);
    
    /**
     *  功能描述: 清除所以合流信息
     *  @return void
     */
    void removeAllOverlayVideo();
    
    /**
     *  功能描述: 打开/关闭 外部扩展滤镜回调
     *  @param  enabled:true表示打开回调，false表示关闭回调
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setExternalFilterEnabled(bool enabled);
    
    
    ///////////声网兼容接口//////////////////////////////////////////////
    int enableLocalVideoRender(bool enabled);
    int enableLocalVideoSend(bool enabled);
    int muteAllRemoteVideoStreams(bool mute);
    int setDefaultMuteAllRemoteVideoStreams(bool mute);
    int muteRemoteVideoStream(std::string& uid, bool mute);
    #if TARGET_OS_IPHONE || defined(ANDROID)
    bool isCameraZoomSupported();
    float setCameraZoomFactor(float zoomFactor);
    bool isCameraFocusPositionInPreviewSupported();
    bool setCameraFocusPositionInPreview( float x , float y );
    bool isCameraTorchSupported();
    bool setCameraTorchOn( bool isOn );
    bool isCameraAutoFocusFaceModeSupported();
    bool setCameraAutoFocusFaceModeEnabled( bool enable );
    #endif
    void setLocalVideoMirrorMode( YouMeVideoMirrorMode mode );
    /**
     *  功能描述: 设置本地视频预览镜像模式
     *  @param  enabled:true表示打开镜像，false表示关闭镜像
     *  @return void
     */
    void setLocalVideoPreviewMirror( bool enable );

    /**
     *  功能描述: 设置用户自定义数据的回调
     *  @param  pCallback:收到其它人自定义数据的回调地址，需要继承IYouMeCustomDataCallback并实现其中的回调函数
     *  @return void
     */
	void setRecvCustomDataCallback(IYouMeCustomDataCallback* pCallback);

    /**
     *  功能描述: 设置translateText的回调
     *  @param  pCallback:翻译回调
     *  @return void
     */
    void setTranslateCallback( IYouMeTranslateCallback* pCallback );
    /**
     *  功能描述: 输入用户自定义数据，以广播形式发送到房间内其它成员
     *  @param  data:自定义数据
     *  @param  len:数据长度，不能大于1024
     *  @param  timestamp:时间戳
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
	YouMeErrorCode inputCustomData(const void* data, int len, uint64_t timestamp, std::string userId = "");

    
    /**
     *  功能描述: 设置视频数据回调方式，硬编解码默认回调opengl纹理方式，使用该方法可以回调yuv格式
     *  @param  enabled:true 打开，false 关闭，默认关闭
     *  @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode setVideoFrameRawCbEnabled(bool enabled);
    
    /**
     * 开启服务器推流，推送自己的数据
     * @param pushUrl:推流地址，可以用restApi获取
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode startPush( const char* pushUrl );
    /**
     * 关闭服务器推流，对应startPush
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode stopPush();
    
    /**
     * 开启服务器混流推流，将多个人的画面混到一起，对混流画面就行推流。每个房间只允许一个混流推流。
     * 开启服务器混流推流后，可以通过addPushMixUser/removePushMixUser改变推流的画面。
     * @param pushUrl:推流地址，可以用restApi获取
     * @param width: 推流的画面的宽
     * @param height: 推流的画面的高
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
	YouMeErrorCode setPushMix(const char* pushUrl, int width, int height);
    /**
     * 关闭服务器混流推流，对应setPushMix
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode clearPushMix();
    
    /**
     * 在服务器混流推流中，加入一个user的数据
     * @param userId: 需要加入的用户ID
     * @param x: 用户画面在混流画面中的位置，x
     * @param y: 用户画面在混流画面中的位置，y
     * @param z: 用户画面在混流画面中的位置，z,代表前后关系
     * @param width: 用户画面在混流画面中的宽
     * @param height: 用户画面在混流画面中的高
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
	YouMeErrorCode addPushMixUser(const char* userId, int x, int y, int z, int width, int height);
    /**
     * 删除混流推流中的一个用户
     * @param userId: 需要删除的用户ID
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
	YouMeErrorCode removePushMixUser(const char* userId);

#ifdef WIN32   
    /**
     * 开始采集共享区域视频并开始共享, 设置共享视频流采集模式和参数(windows平台)
     * @param mode: 共享视频采集模式  1：采集设备 2：采集指定窗口 3：采集桌面
     * @param renderHandle: 共享视频preview窗口句柄，必选
     * @param captureHandle: 指定需要采集的窗口句柄，采集桌面则可以设置为NULL
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode StartShareStream(int mode, HWND renderHandle, HWND captureHandle);

    /**
     * 遍历桌面窗口列表，返回句柄和窗口名
     * @return 无返回码
     */
    void GetWindowInfoList(HWND *pHwnd, char *pWinName, int *winCount);

    /**
     * 开始屏幕采集并录像
     * @param filePath:录像文件路径，目前只支持mp4格式
     * @param renderHandle:渲染窗口句柄，调用libscreen必带参数，不为空
     * @param captureHandle:录屏句柄，如果为空，则表示录制整个屏幕；如果不为空，则表示录制某个窗口
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode startSaveScreen(const std::string& filePath, HWND renderHandle, HWND captureHandle);
    
#elif MAC_OS
    /**
    *  检查桌面/窗口共享权限，在开始共享之前调用（主要是macos 10.15增加屏幕录制权限隐私设置）
    * @return   YOUME_SUCCESS - 成功
    *                 YOUME_ERROR_SHARE_NO_PERMISSION - 没有共享权限
    */
    YouMeErrorCode checkSharePermission();
    
    /**
     * 开始采集共享区域视频并开始共享, 设置共享视频流采集模式和参数(mac平台)
     * @param mode: 共享视频采集模式  1：采集设备 2：采集指定窗口 3：采集桌面
     * @param renderHandle: 共享视频preview窗口句柄，必选
     * @param captureHandle: 指定需要采集的窗口句柄，采集桌面则可以设置为NULL
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode StartShareStream(int mode, int windowid);

    /**
     * 遍历桌面窗口列表，返回窗口owner，窗口name， 窗口id，窗口总数
     * @return 无返回码
     */
    void GetWindowInfoList(char *pWinOwner, char *pWinName, int *pWinId, int *winCount);
#endif
    /**
     * 开始屏幕采集并录像
     * @param filePath:录像文件路径，目前只支持mp4格式
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode startSaveScreen( const std::string&  filePath);
    
    /**
     * 结束采集共享区域视频并结束共享
     * @return 无返回码
     */
    void StopShareStream();
    
    /**
     * 停止屏幕采集录像
     * @return 无返回码
     */
    void stopSaveScreen();

    /**
     * 获取共享视频流数据
     * @param len: 共享视频流数据长度
     * @param width: 共享视频流分辨率宽度
     * @param width: 共享视频流分辨率高度
     * @param width: 共享视频流数据格式，默认是yv12
     * @return char *buf - 返回数据buffer
     *          需要检查是否为null
     */
    char *GetShareVideoData(int * len, int * width, int * height, int * fmt);
    
    /**
     * 简化横竖屏切换用的接口，仅在需要这个SDK内置逻辑的情况下使用
     * 通知sdk发生了横屏切换，交换原先设置的编码和预览宽高设置
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode switchResolutionForLandscape();
    
    /**
     * 简化横竖屏切换用的接口，仅在需要这个SDK内置逻辑的情况下使用
     * 通知sdk发生了竖屏切换，还原原先设置的编码和预览宽高设置
     * @return YOUME_SUCCESS - 成功
     *          其他 - 具体错误码
     */
    YouMeErrorCode resetResolutionForPortrait();
    
    /*
     * 功能：国际语言文本翻译
     * @param requestID：请求ID
     * @param text：内容
     * @param destLangCode：目标语言编码
     * @param srcLangCode：源语言编码
     * @return 错误码
     */
    YouMeErrorCode translateText(unsigned int* requestID, const char* text, YouMeLanguageCode destLangCode, YouMeLanguageCode srcLangCode);
    
    
    /**
     * 设置视频编码类型，默认h264
     * @param codecType: 参考YMVideoCodecType
     * @return YOUME_SUCCESS - 成功
     * 其他 - 具体错误码
    */
    YouMeErrorCode setVideoCodecType(int codecType);
private:

    IYouMeVoiceEngine ();
    ~IYouMeVoiceEngine ();
};


#endif
