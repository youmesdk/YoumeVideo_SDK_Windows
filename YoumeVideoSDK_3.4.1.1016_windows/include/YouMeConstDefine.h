 /**
 @file YouMeConstDefine.h
 @brief 游密音频通话引擎回调事件和错误码定义
 
 该文件主要用于定义游密音频通话引擎回调事件和错误码
 
 @version 1.0 Copyright(c) 2015-2020 YOUME All rights reserved.
 @author YOUME

 */

#ifndef cocos2d_x_sdk_YouMeErrorCode_h
#define cocos2d_x_sdk_YouMeErrorCode_h

#define MAX_DEVICE_ID_LENGTH 512        //audio设备名的长度

/// 用户角色
typedef enum YouMeUserRole {
    YOUME_USER_NONE = 0,         ///< 非法用户，调用API时不能传此参数
    YOUME_USER_TALKER_FREE,      ///< 自由讲话者，适用于小组通话（建议小组成员数最多10个），每个人都可以随时讲话, 同一个时刻只能在一个语音频道里面
    YOUME_USER_TALKER_ON_DEMAND, ///< 需要通过抢麦等请求麦克风权限之后才可以讲话，适用于较大的组或工会等（比如几十个人），同一个时刻只能有一个或几个人能讲话, 同一个时刻只能在一个语音频道里面
    YOUME_USER_LISTENER,         ///< 听众，主播/指挥/嘉宾的听众，同一个时刻只能在一个语音频道里面，只听不讲
    YOUME_USER_COMMANDER,        ///< 指挥，国家/帮派等的指挥官，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
    YOUME_USER_HOST,             ///< 主播，广播型语音频道的主持人，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
    YOUME_USER_GUSET,            ///< 嘉宾，主播或指挥邀请的连麦嘉宾，同一个时刻只能在一个语音频道里面， 可以随时讲话
} YouMeUserRole_t;

typedef enum YouMeAVStatisticType
{
    YOUME_AVS_AUDIO_CODERATE = 1,               //音频传输码率，userid是自己:上行码率，userid其它人:下行码率，单位Bps
    YOUME_AVS_VIDEO_CODERATE = 2,               //camera视频传输码率，userid是自己:上行码率，userid其它人:下行码率，单位Bps
    YOUME_AVS_VIDEO_FRAMERATE = 3,              //视频帧率，userid是自己:上行帧率，userid其它人:下行帧率
    YOUME_AVS_AUDIO_PACKET_UP_LOSS_RATE = 4,    //音频上行丢包率(全程),千分比
    YOUME_AVS_AUDIO_PACKET_DOWN_LOSS_RATE = 5,  //音频下行丢包率(全程),千分比
    YOUME_AVS_VIDEO_PACKET_UP_LOSS_RATE = 6,    //视频上行丢包率(全程),千分比
    YOUME_AVS_VIDEO_PACKET_DOWN_LOSS_RATE = 7,  //视频下行丢包率(全程),千分比
    YOUME_AVS_AUDIO_DELAY_MS = 8,               //音频延迟(RTT)，单位毫秒
    YOUME_AVS_VIDEO_DELAY_MS = 9,               //视频延迟(RTT)，单位毫秒
    YOUME_AVS_VIDEO_BLOCK = 10,                 //视频卡顿,是否发生过卡顿
    YOUME_AVS_AUDIO_PACKET_UP_LOSS_HALF = 11,   //音频上行的服务器丢包率(半程)，千分比
    YOUME_AVS_VIDEO_PACKET_UP_LOSS_HALF = 12,   //视频上行的服务器丢包率(半程)，千分比
    YOUME_AVS_RECV_DATA_STAT = 13,              //下行带宽,单位Bps
    YOUME_AVS_VIDEO_SHARE_CODERATE  = 14,       //共享视频传输码率，userid是自己:上行码率，userid其它人:下行码率，单位Bps
    YOUME_AVS_VIDEO_SHARE_FRAMERATE = 15,       //共享视频传输帧率，userid是自己:上行帧率，userid其它人:下行帧率
    YOUME_AVS_VIDEO_RESOLUTION = 16,            //视频分辨率上报, userid是自己:上行分辨率，userid其它人:下行分辨率
    YOUME_AVS_VIDEO_SHARE_RESOLUTION = 17,      //共享流分辨率上报, userid是自己:上行分辨率，userid其它人:下行分辨率
    YOUME_AVS_SEND_DATA_STAT = 18,              //上行带宽,单位Bps
} YouMeAVStatisticType_t;

typedef enum YouMeAudioRouteType
{
    YOUME_AUDIO_ROUTE_SPEAKER               = 0,    // 手机扬声器
    YOUME_AUDIO_ROUTE_EARPIECE              = 1,    // 听筒
    YOUME_AUDIO_ROUTE_HEADSET               = 2,    // 耳机
    YOUME_AUDIO_ROUTE_HEADSET_BLUETOOTH     = 3,    // 蓝牙耳机
} YouMeAudioRouteType_t;

/// 事件通知
typedef enum YouMeEvent {
    YOUME_EVENT_INIT_OK                      = 0,   ///< SDK初始化成功
    YOUME_EVENT_INIT_FAILED                  = 1,   ///< SDK初始化失败
    YOUME_EVENT_JOIN_OK                      = 2,   ///< 进入语音频道成功
    YOUME_EVENT_JOIN_FAILED                  = 3,   ///< 进入语音频道失败
    YOUME_EVENT_LEAVED_ONE                   = 4,   ///< 退出单个语音频道完成
    YOUME_EVENT_LEAVED_ALL                   = 5,   ///< 退出所有语音频道完成
    YOUME_EVENT_PAUSED                       = 6,   ///< 暂停语音频道完成
    YOUME_EVENT_RESUMED                      = 7,   ///< 恢复语音频道完成
    YOUME_EVENT_SPEAK_SUCCESS                = 8,   ///< 切换对指定频道讲话成功（适用于多频道模式）
    YOUME_EVENT_SPEAK_FAILED                 = 9,   ///< 切换对指定频道讲话失败（适用于多频道模式）
    YOUME_EVENT_RECONNECTING                 = 10,  ///< 断网了，正在重连
    YOUME_EVENT_RECONNECTED                  = 11,  ///< 断网重连成功
    YOUME_EVENT_REC_PERMISSION_STATUS        = 12,  ///< 通知录音权限状态，成功获取权限时错误码为YOUME_SUCCESS，获取失败为YOUME_ERROR_REC_NO_PERMISSION（此时不管麦克风mute状态如何，都没有声音输出）
    YOUME_EVENT_BGM_STOPPED                  = 13,  ///< 通知背景音乐播放结束
    YOUME_EVENT_BGM_FAILED                   = 14,  ///< 通知背景音乐播放失败
    //YOUME_EVENT_MEMBER_CHANGE              = 15,  ///< 频道成员变化

    YOUME_EVENT_OTHERS_MIC_ON                = 16,  ///< 其他用户麦克风打开
    YOUME_EVENT_OTHERS_MIC_OFF               = 17,  ///< 其他用户麦克风关闭
    YOUME_EVENT_OTHERS_SPEAKER_ON            = 18,  ///< 其他用户扬声器打开
    YOUME_EVENT_OTHERS_SPEAKER_OFF           = 19,  ///< 其他用户扬声器关闭
    YOUME_EVENT_OTHERS_VOICE_ON              = 20,  ///< 其他用户进入讲话状态
    YOUME_EVENT_OTHERS_VOICE_OFF             = 21,  ///< 其他用户进入静默状态
    YOUME_EVENT_MY_MIC_LEVEL                 = 22,  ///< 麦克风的语音级别
        
    YOUME_EVENT_MIC_CTR_ON                   = 23,  ///< 麦克风被其他用户打开
    YOUME_EVENT_MIC_CTR_OFF                  = 24,  ///< 麦克风被其他用户关闭    
    YOUME_EVENT_SPEAKER_CTR_ON               = 25,  ///< 扬声器被其他用户打开
    YOUME_EVENT_SPEAKER_CTR_OFF              = 26,  ///< 扬声器被其他用户关闭
    
    YOUME_EVENT_LISTEN_OTHER_ON              = 27,  ///< 取消屏蔽某人语音
    YOUME_EVENT_LISTEN_OTHER_OFF             = 28,  ///< 屏蔽某人语音
	
    YOUME_EVENT_LOCAL_MIC_ON		         = 29,  ///< 自己的麦克风打开
    YOUME_EVENT_LOCAL_MIC_OFF		         = 30,  ///< 自己的麦克风关闭
    YOUME_EVENT_LOCAL_SPEAKER_ON	         = 31,  ///< 自己的扬声器打开
    YOUME_EVENT_LOCAL_SPEAKER_OFF	         = 32,  ///< 自己的扬声器关闭

    YOUME_EVENT_GRABMIC_START_OK             = 33,  ///< 发起抢麦活动成功
    YOUME_EVENT_GRABMIC_START_FAILED         = 34,  ///< 发起抢麦活动失败
    YOUME_EVENT_GRABMIC_STOP_OK              = 35,  ///< 停止抢麦活动成功
    YOUME_EVENT_GRABMIC_STOP_FAILED          = 36,  ///< 停止抢麦活动失败
    YOUME_EVENT_GRABMIC_REQUEST_OK	         = 37,  ///< 抢麦成功（可以说话）
    YOUME_EVENT_GRABMIC_REQUEST_FAILED       = 38,  ///< 抢麦失败
    YOUME_EVENT_GRABMIC_REQUEST_WAIT         = 39,  ///< 进入抢麦等待队列（仅权重模式下会回调此事件）
    YOUME_EVENT_GRABMIC_RELEASE_OK           = 40,  ///< 释放麦成功
    YOUME_EVENT_GRABMIC_RELEASE_FAILED       = 41,  ///< 释放麦失败
    YOUME_EVENT_GRABMIC_ENDMIC               = 42,  ///< 不再占用麦（到麦使用时间或者其他原因）

    YOUME_EVENT_GRABMIC_NOTIFY_START         = 43,  ///< [通知]抢麦活动开始
    YOUME_EVENT_GRABMIC_NOTIFY_STOP          = 44,  ///< [通知]抢麦活动结束
    YOUME_EVENT_GRABMIC_NOTIFY_HASMIC        = 45,  ///< [通知]有麦可以抢
    YOUME_EVENT_GRABMIC_NOTIFY_NOMIC         = 46,  ///< [通知]没有麦可以抢

    YOUME_EVENT_INVITEMIC_SETOPT_OK          = 47,  ///< 连麦设置成功
    YOUME_EVENT_INVITEMIC_SETOPT_FAILED      = 48,  ///< 连麦设置失败
    YOUME_EVENT_INVITEMIC_REQUEST_OK         = 49,  ///< 请求连麦成功（连上了，需等待对方回应）
    YOUME_EVENT_INVITEMIC_REQUEST_FAILED     = 50,  ///< 请求连麦失败
    YOUME_EVENT_INVITEMIC_RESPONSE_OK        = 51,  ///< 响应连麦成功（被叫方无论同意/拒绝都会收到此事件，错误码是YOUME_ERROR_INVITEMIC_REJECT表示拒绝）
    YOUME_EVENT_INVITEMIC_RESPONSE_FAILED    = 52,  ///< 响应连麦失败
    YOUME_EVENT_INVITEMIC_STOP_OK            = 53,  ///< 停止连麦成功
    YOUME_EVENT_INVITEMIC_STOP_FAILED        = 54,  ///< 停止连麦失败

    YOUME_EVENT_INVITEMIC_CAN_TALK           = 55,  ///< 双方可以通话了（响应方已经同意）
    YOUME_EVENT_INVITEMIC_CANNOT_TALK        = 56,  ///< 双方不可以再通话了（有一方结束了连麦或者连麦时间到）

    YOUME_EVENT_INVITEMIC_NOTIFY_CALL        = 57,  ///< [通知]有人请求与你连麦
    YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER      = 58,  ///< [通知]对方对你的连麦请求作出了响应（同意/拒绝/超时，同意的话双方就可以通话了）
    YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL      = 59,  ///< [通知]连麦过程中，对方结束了连麦或者连麦时间到
	
	YOUME_EVENT_SEND_MESSAGE_RESULT          = 60,  ///< sendMessage成功与否的通知，param为回传的requestID
    YOUME_EVENT_MESSAGE_NOTIFY               = 61,  ///< 收到Message, param为message内容
    
    YOUME_EVENT_KICK_RESULT                  = 64,  ///< 踢人的应答
    YOUME_EVENT_KICK_NOTIFY                  = 65,  ///< 被踢通知   ,param: （踢人者ID，被踢原因，被禁时间）
    
    YOUME_EVENT_FAREND_VOICE_LEVEL           = 66,  ///< 远端说话人音量大小
    
    YOUME_EVENT_OTHERS_BE_KICKED             = 67,  ///< 房间里其他人被踢出房间
    //68-71 talk已占用
	YOUME_EVENT_SPEAK_RECORD_ON				 = 68,	///< 扬声器内录开启通知（成功、失败）
	YOUME_EVENT_SPEAK_RECORD_OFF			 = 69,	///< 扬声器内录关闭通知（成功、失败）
	YOUME_EVENT_SPEAK_RECORD_RESET			 = 70,	///< 扬声器内录重启通知（成功、失败）
    
    YOUME_EVENT_EFFECT_PLAY_COMPLETE            = 71,   ///< 音效播放完成
    YOUME_EVENT_AUDIO_START_FAIL                = 72,   ///< 音频启动失败，可能是设备被其他应用占用
    YOUME_EVENT_AUDIO_INPUT_DEVICE_CONNECT      = 73,   ///< 音频采集设备插入，移动端无效
    YOUME_EVENT_AUDIO_INPUT_DEVICE_DISCONNECT   = 74,   ///< 音频采集设备拔出，移动端无效

    YOUME_EVENT_SWITCH_OUTPUT                = 75, ///< 切换扬声器/听筒
	YOUME_EVENT_BGM_OR_SPEAR_RECORD          = 76, ///< 背景音乐 或者 内录，同一时间，只能打开一个  
    YOUME_EVENT_AUDIO_ROUTE_CHANGE           = 77, ///< 音频路由改变事件 (YouMeAudioRouteType_t)

    YOUME_EVENT_OTHERS_VIDEO_ON              = 200, ///< 收到其它用户的视频流

    YOUME_EVENT_MASK_VIDEO_BY_OTHER_USER     = 204, ///< 视频被其他用户屏蔽
    YOUME_EVENT_RESUME_VIDEO_BY_OTHER_USER   = 205, ///< 视频被其他用户恢复
    YOUME_EVENT_MASK_VIDEO_FOR_USER          = 206, ///< 屏蔽了谁的视频
    YOUME_EVENT_RESUME_VIDEO_FOR_USER        = 207, ///< 恢复了谁的视频
    YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN       = 208, ///< 其它用户的视频流断开（包含网络中断的情况）
    YOUME_EVENT_OTHERS_VIDEO_INPUT_START     = 209, ///< 其他用户视频输入开始（内部采集下开启摄像头/外部输入下开始input）
    YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP      = 210, ///< 其他用户视频输入停止（内部采集下停止摄像头/外部输入下停止input）
    
    YOUME_EVENT_MEDIA_DATA_ROAD_PASS         = 211, ///< 音视频数据通路连通，定时检测，一开始收到数据会收到PASS事件，之后变化的时候会发送
    YOUME_EVENT_MEDIA_DATA_ROAD_BLOCK        = 212, ///< 音视频数据通路不通
    
    YOUME_EVENT_QUERY_USERS_VIDEO_INFO       = 213, ///< 查询用户视频信息返回
    YOUME_EVENT_SET_USERS_VIDEO_INFO         = 214, ///< 设置用户接收视频信息返回
    
    YOUME_EVENT_LOCAL_VIDEO_INPUT_START      = 215, ///< 本地视频输入开始（内部采集下开始摄像头/外部输入下开始input）
    YOUME_EVENT_LOCAL_VIDEO_INPUT_STOP       = 216, ///< 本地视频输入停止（内部采集下停止摄像头/外部输入下停止input）
    
    YOUME_EVENT_START_PUSH                   = 217, ///< 设置startPush的返回事件
    YOUME_EVENT_SET_PUSH_MIX                 = 218, ///< 设置setPushMix的返回事件
    YOUME_EVENT_ADD_PUSH_MIX_USER            = 219, ///< 设置addPushMixUser的返回事件，参数userID
    YOUME_EVENT_OTHER_SET_PUSH_MIX           = 220, ///< 在自己调用了setPushMix还没停止的情况下，房间内有别人调用setPushMix，自己被踢

    YOUME_EVENT_LOCAL_SHARE_INPUT_START      = 221, ///< 本地共享视频输入开始
    YOUME_EVENT_LOCAL_SHARE_INPUT_STOP       = 222, ///< 本地共享视频输入停止
    YOUME_EVENT_OTHERS_SHARE_INPUT_START     = 223, ///< 其他用户共享视频输入开始
    YOUME_EVENT_OTHERS_SHARE_INPUT_STOP      = 224, ///< 其他用户共享视频输入停止
    
    YOUME_EVENT_SET_USERS_VIDEO_INFO_NOTIFY  = 225, ///< 设置用户接收视频信息给发送方的通知
    
    YOUME_EVENT_OTHER_PLAY_BACKGRAOUND_MUSIC = 226, ///其他人播放背景音乐
    YOUME_EVENT_OTHER_STOP_BACKGRAOUND_MUSIC = 227, ///其他人停止背景音乐

    YOUME_EVENT_OTHERS_DATA_ERROR            = 300, ///< 数据错误
    YOUME_EVENT_OTHERS_NETWORK_BAD           = 301, ///< 网络不好
    YOUME_EVENT_OTHERS_BLACK_FULL            = 302, ///< 黑屏
    YOUME_EVENT_OTHERS_GREEN_FULL            = 303, ///< 绿屏
    YOUME_EVENT_OTHERS_BLACK_BORDER          = 304, ///< 黑边
    YOUME_EVENT_OTHERS_GREEN_BORDER          = 305, ///< 绿边
    YOUME_EVENT_OTHERS_BLURRED_SCREEN        = 306, ///< 花屏
    YOUME_EVENT_OTHERS_ENCODER_ERROR         = 307, ///< 编码错误
    YOUME_EVENT_OTHERS_DECODER_ERROR         = 308, ///< 解码错误
    
    YOUME_EVENT_CAMERA_DEVICE_CONNECT        = 400, ///< 摄像头设备插入，移动端无效
    YOUME_EVENT_CAMERA_DEVICE_DISCONNECT     = 401, ///< 摄像头设备拔出，移动端无效

    YOUME_EVENT_AUDIO_HOWLING_DETECTION      = 450, ///< 检测到啸叫

    // video encode param report
    YOUME_EVENT_VIDEO_ENCODE_PARAM_REPORT    = 500,
    YOUME_EVENT_VIDEO_DECODE_PARAM_REPORT    = 501,

    // p2p/server route
    YOUME_EVENT_RTP_ROUTE_P2P                = 600, ///< P2P通路检测ok, 当前通路为P2P
    YOUME_EVENT_RTP_ROUTE_SEREVER            = 601, ///< P2P通路检测失败, 当前通路为server转发
    YOUME_EVENT_RTP_ROUTE_CHANGE_TO_SERVER   = 602, ///< 运行过程中P2P 检测失败，切换到server转发
    YOUME_EVENT_RTP_ROUTE_SERVER_WITH_P2P_PROBE   = 603, ///< server转发模式下，P2P探测成功

    YOUME_EVENT_RECOGNIZE_MODULE_INIT_START  = 700, ///< 语音识别初始化开始
    YOUME_EVENT_RECOGNIZE_MODULE_INIT_END    = 701, ///< 语音识别初始化完成
    YOUME_EVENT_RECOGNIZE_MODULE_UNINIT      = 702, ///< 语音识别结束
    YOUME_EVENT_RECOGNIZE_MODULE_ERR         = 703, ///< 语音识别出错

    // for windows/mac share
	YOUME_EVENT_LOCAL_SHARE_WINDOW_CLOSED	 = 725, ///< 共享窗口被关闭
    YOUME_EVENT_LOCAL_SHARE_WINDOW_INVSIABLE = 726, ///< 共享窗口被隐藏，不可见
    YOUME_EVENT_LOCAL_SHARE_WINDOW_ISICONIC  = 727, ///< 共享窗口被最小化
    YOUME_EVENT_LOCAL_SHARE_WINDOW_NORMAL    = 728, ///< 共享窗口恢复正常
	YOUME_EVENT_LOCAL_SHARE_WINDOW_MOVE		 = 729, ///< 共享窗口位置发生变化

    YOUME_EVENT_EOF                          = 1000,
    
} YouMeEvent_t;

typedef enum YouMeKickReason
{
    YOUME_KICK_ADMIN = 1,           ///< 管理员踢人
    YOUME_KICK_RELOGIN = 2,         ///< 多端登录被踢
} YouMeKickReason_t;

/// 房间内的广播消息
typedef enum YouMeBroadcast
{
	YOUME_BROADCAST_NONE = 0,
	YOUME_BROADCAST_GRABMIC_BROADCAST_GETMIC = 1,	    ///< 有人抢到了麦
	YOUME_BROADCAST_GRABMIC_BROADCAST_FREEMIC = 2,	    ///< 有人释放了麦
	YOUME_BROADCAST_INVITEMIC_BROADCAST_CONNECT = 3,	///< A和B正在连麦
	YOUME_BROADCAST_INVITEMIC_BROADCAST_DISCONNECT = 4, ///< A和B取消了连麦
}YouMeBroadcast_t;

typedef enum YouMeErrorCode {
    YOUME_SUCCESS                            = 0,    ///< 成功
    
    // 参数和状态检查
    YOUME_ERROR_API_NOT_SUPPORTED            = -1,   ///< 正在使用的SDK不支持特定的API
    YOUME_ERROR_INVALID_PARAM                = -2,   ///< 传入参数错误
    YOUME_ERROR_ALREADY_INIT                 = -3,   ///< 已经初始化
    YOUME_ERROR_NOT_INIT                     = -4,   ///< 还没有初始化，在调用某函数之前要先调用初始化并且要根据返回值确保初始化成功
    YOUME_ERROR_CHANNEL_EXIST                = -5,   ///< 要加入的频道已经存在
    YOUME_ERROR_CHANNEL_NOT_EXIST            = -6,   ///< 要退出的频道不存在，或者其它操作指定的频道不存在
    YOUME_ERROR_WRONG_STATE                  = -7,   ///< 状态错误
    YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK   = -8,   ///< 不允许使用移动网络
    YOUME_ERROR_WRONG_CHANNEL_MODE           = -9,   ///< 在单频道模式下调用了多频道接口，或者反之
    YOUME_ERROR_TOO_MANY_CHANNELS            = -10,  ///< 同时加入了太多频道
    YOUME_ERROR_TOKEN_ERROR                  = -11,  ///< 传入的token认证错误
    YOUME_ERROR_NOT_IN_CHANNEL               = -12,  ///< 用户不在该频道
    YOUME_ERROR_BE_KICK                      = -13,  ///< 被踢了，还在禁止时间内，不允许进入房间
    YOUME_ERROR_DEVICE_NOT_VALID             = -14,  ///< 设置的设备不可用
    YOUME_ERROR_API_NOT_ALLOWED              = -15,  ///< 没有特定功能的权限
    YOUME_ERROR_NO_LANG_CODE                 = -16,  ///< 翻译功能指定了不存在的语言

    // 内部操作错误
    YOUME_ERROR_MEMORY_OUT                   = -100, ///< 内存错误
    YOUME_ERROR_START_FAILED                 = -101, ///< 启动引擎失败
    YOUME_ERROR_STOP_FAILED                  = -102, ///<  停止引擎失败
    YOUME_ERROR_ILLEGAL_SDK                  = -103, ///< 非法使用SDK
    YOUME_ERROR_SERVER_INVALID               = -104, ///< 语音服务不可用
    YOUME_ERROR_NETWORK_ERROR                = -105, ///< 网络错误
    YOUME_ERROR_SERVER_INTER_ERROR           = -106, ///< 服务器内部错误
    YOUME_ERROR_QUERY_RESTAPI_FAIL           = -107, ///< 请求RestApi信息失败了
    YOUME_ERROR_USER_ABORT                   = -108, ///< 用户请求中断当前操作
    YOUME_ERROR_SEND_MESSAGE_FAIL            = -109, ///< 发送消息失败
    YOUME_ERROR_SET_PUSH_PARAM_FAIL          = -110, ///< 向服务器设置Push参数失败
    YOUME_ERROR_INIT_SHARE_FAIL              = -111, ///< 初始化共享设备失败
    YOUME_ERROR_START_SHARE_FAIL             = -112, ///< 开始视频共享失败
    YOUME_ERROR_SHARE_NO_PERMISSION          = -113, ///< 共享视频没有权限

    
    // 麦克风错误
    YOUME_ERROR_REC_INIT_FAILED              = -201, ///< 录音模块初始化失败
    YOUME_ERROR_REC_NO_PERMISSION            = -202, ///< 没有录音权限
    YOUME_ERROR_REC_NO_DATA                  = -203, ///< 虽然初始化成功，但没有音频数据输出，比如oppo系列手机在录音权限被禁止的时候
    YOUME_ERROR_REC_OTHERS                   = -204, ///< 其他录音模块的错误
    YOUME_ERROR_REC_PERMISSION_UNDEFINED     = -205, ///< 录音权限未确定，iOS显示是否允许录音权限对话框时，返回的是这个错误码
    
	// 抢麦错误
	YOUME_ERROR_GRABMIC_FULL				 = -301, ///< 抢麦失败，人数满
	YOUME_ERROR_GRABMIC_HASEND				 = -302, ///< 抢麦失败，活动已经结束

	// 连麦错误
	YOUME_ERROR_INVITEMIC_NOUSER			 = -401, ///< 连麦失败，用户不存在
	YOUME_ERROR_INVITEMIC_OFFLINE			 = -402, ///< 连麦失败，用户已离线
	YOUME_ERROR_INVITEMIC_REJECT			 = -403, ///< 连麦失败，用户拒绝
	YOUME_ERROR_INVITEMIC_TIMEOUT			 = -404, ///< 连麦失败，两种情况：1.连麦时，对方超时无应答 2.通话中，双方通话时间到

    YOUME_ERROR_CAMERA_OPEN_FAILED           = -501, ///打开摄像头失败
    YOUME_ERROR_CAMERA_EXCEPTION             = -502, /// camera设备异常

	YOUME_ERROR_NOT_PROCESS                  = -601, ///不做任何改变
   
    YOUME_ERROR_UNKNOWN                      = -1000,///< 未知错误

} YouMeErrorCode_t;

typedef enum SERVER_MODE {
    SERVER_MODE_FORMAL               = 0,
    SERVER_MODE_TEST                 = 1,
    SERVER_MODE_DEV                  = 2,
    SERVER_MODE_DEMO                 = 3,
    SERVER_MODE_FIXED_IP_VALIDATE    = 4,
    SERVER_MODE_FIXED_IP_REDIRECT    = 5,
    SERVER_MODE_FIXED_IP_MCU         = 6,
    SERVER_MODE_FIXED_IP_PRIVATE_SERVICE = 7
}SERVER_MODE_t;

typedef enum YOUME_RTC_SERVER_REGION {
    RTC_CN_SERVER       = 0,  // 中国
    RTC_HK_SERVER       = 1,  // 香港
    RTC_US_SERVER       = 2,  // 美国东部
    RTC_SG_SERVER       = 3,  // 新加坡
    RTC_KR_SERVER       = 4,  // 韩国
    RTC_AU_SERVER       = 5,  // 澳洲
    RTC_DE_SERVER       = 6,  // 德国
    RTC_BR_SERVER       = 7,  // 巴西
    RTC_IN_SERVER       = 8,  // 印度
    RTC_JP_SERVER       = 9,  // 日本
    RTC_IE_SERVER       = 10, // 爱尔兰
    RTC_USW_SERVER      = 11, // 美国西部
    RTC_USM_SERVER      = 12, // 美国中部
    RTC_CA_SERVER       = 13, // 加拿大
    RTC_LON_SERVER      = 14, // 伦敦
    RTC_FRA_SERVER      = 15, // 法兰克福
    RTC_DXB_SERVER      = 16, // 迪拜
    
    RTC_EXT_SERVER     = 10000, // 使用扩展服务器
    RTC_DEFAULT_SERVER = 10001, // 缺省服务器
}YOUME_RTC_SERVER_REGION_t;

typedef enum YOUME_LOG_LEVEL{
    LOG_DISABLED = 0,
    LOG_FATAL = 1,
    LOG_ERROR = 10,
    LOG_WARNING = 20,
    LOG_INFO = 40,
    LOG_DEBUG = 50,
    LOG_VERBOSE = 60
} YOUME_LOG_LEVEL_t;

typedef enum YOUME_SAMPLE_RATE{
    SAMPLE_RATE_8 = 8000,
    SAMPLE_RATE_16 = 16000,
    SAMPLE_RATE_24 = 24000,
    SAMPLE_RATE_32 = 32000,
    SAMPLE_RATE_44 = 44100,
    SAMPLE_RATE_48 = 48000
} YOUME_SAMPLE_RATE_t;

typedef enum YOUME_AUDIO_QUALITY {
    LOW_QUALITY = 0,
    HIGH_QUALITY
} YOUME_AUDIO_QUALITY_t;

typedef enum YouMeVideoRenderMode {
    YOUME_VIDEO_RENDER_MODE_HIDDEN = 0,
    YOUME_VIDEO_RENDER_MODE_FIT = 1,
    YOUME_VIDEO_RENDER_MODE_ADAPTIVE = 2,
    YOUME_VIDEO_RENDER_MODE_STRETCH = 3
}YouMeVideoRenderMode_t;

typedef enum YouMeVideoMirrorMode {
    YOUME_VIDEO_MIRROR_MODE_AUTO = 0,            //内部采集自适应镜像，外部采集为关闭镜像
    YOUME_VIDEO_MIRROR_MODE_ENABLED = 1,         //近端和远端都镜像
    YOUME_VIDEO_MIRROR_MODE_DISABLED = 2,        //关闭镜像
    YOUME_VIDEO_MIRROR_MODE_NEAR = 3,            //近端镜像
    YOUME_VIDEO_MIRROR_MODE_FAR = 4              //远端镜像
}YouMeVideoMirrorMode_t;


typedef enum YOUME_VIDEO_FMT{
    VIDEO_FMT_RGBA32 = 0,
    VIDEO_FMT_BGRA32 = 1,
    VIDEO_FMT_YUV420P = 2,
    VIDEO_FMT_NV21 = 3,
    VIDEO_FMT_YV12 = 4,
    VIDEO_FMT_CVPIXELBUFFER  = 5,
    VIDEO_FMT_TEXTURE = 6,
    VIDEO_FMT_TEXTURE_OES = 7,
    VIDEO_FMT_RGB24 = 8,
    VIDEO_FMT_NV12 = 9,
    VIDEO_FMT_H264 = 10,
    VIDEO_FMT_ABGR32 = 11,
    VIDEO_FMT_TEXTURE_YUV = 12,
    VIDEO_FMT_ENCRYPT = 13,
}YOUME_VIDEO_FMT_t;

typedef enum YOUME_VIDEO_SHARE_TYPE {
    VIDEO_SHARE_TYPE_DEVICE = 1,    // device capture(eg:camera)
    VIDEO_SHARE_TYPE_WINDOW = 2,    // window capture
    VIDEO_SHARE_TYPE_SCREEN = 3,    // screen capture
    VIDEO_SHARE_TYPE_UNKNOW,
}YOUME_VIDEO_SHARE_TYPE_t;

typedef enum PcmCallBackFlag{
    PcmCallbackFlag_Remote = 0x1,       //远端pcm回调
    PcmCallbackFlag_Record = 0x2,       //本地录音回调
    PcmCallbackFlag_Mix = 0x4,          //本地录音和远端pcm进行mix之后的回调
} PcmCallBackFlag_t;

typedef enum  YouMeLanguageCode
{
    LANG_AUTO,
    LANG_AF,            // 南非荷兰语
    LANG_AM,            // 阿姆哈拉语
    LANG_AR,            // 阿拉伯语
    LANG_AR_AE,            // 阿拉伯语+阿拉伯联合酋长国
    LANG_AR_BH,            // 阿拉伯语+巴林
    LANG_AR_DZ,            // 阿拉伯语+阿尔及利亚
    LANG_AR_KW,            // 阿拉伯语+科威特
    LANG_AR_LB,            // 阿拉伯语+黎巴嫩
    LANG_AR_OM,            // 阿拉伯语+阿曼
    LANG_AR_SA,            // 阿拉伯语+沙特阿拉伯
    LANG_AR_SD,            // 阿拉伯语+苏丹
    LANG_AR_TN,            // 阿拉伯语+突尼斯
    LANG_AZ,            // 阿塞拜疆
    LANG_BE,            // 白俄罗斯语
    LANG_BG,            // 保加利亚语
    LANG_BN,            // 孟加拉
    LANG_BS,            // 波斯尼亚语
    LANG_CA,            // 加泰罗尼亚语
    LANG_CA_ES,            // 加泰罗尼亚语+西班牙
    LANG_CO,            // 科西嘉
    LANG_CS,            // 捷克语
    LANG_CY,            // 威尔士语
    LANG_DA,            // 丹麦语
    LANG_DE,            // 德语
    LANG_DE_CH,            // 德语+瑞士
    LANG_DE_LU,            // 德语+卢森堡
    LANG_EL,            // 希腊语
    LANG_EN,            // 英语
    LANG_EN_CA,            // 英语+加拿大
    LANG_EN_IE,            // 英语+爱尔兰
    LANG_EN_ZA,            // 英语+南非
    LANG_EO,            // 世界语
    LANG_ES,            // 西班牙语
    LANG_ES_BO,            // 西班牙语+玻利维亚
    LANG_ES_AR,            // 西班牙语+阿根廷
    LANG_ES_CO,            // 西班牙语+哥伦比亚
    LANG_ES_CR,            // 西班牙语+哥斯达黎加
    LANG_ES_ES,            // 西班牙语+西班牙
    LANG_ET,            // 爱沙尼亚语
    LANG_ES_PA,            // 西班牙语+巴拿马
    LANG_ES_SV,            // 西班牙语+萨尔瓦多
    LANG_ES_VE,            // 西班牙语+委内瑞拉
    LANG_ET_EE,            // 爱沙尼亚语+爱沙尼亚
    LANG_EU,            // 巴斯克
    LANG_FA,            // 波斯语
    LANG_FI,            // 芬兰语
    LANG_FR,            // 法语
    LANG_FR_BE,            // 法语+比利时
    LANG_FR_CA,            // 法语+加拿大
    LANG_FR_CH,            // 法语+瑞士
    LANG_FR_LU,            // 法语+卢森堡
    LANG_FY,            // 弗里斯兰
    LANG_GA,            // 爱尔兰语
    LANG_GD,            // 苏格兰盖尔语
    LANG_GL,            // 加利西亚
    LANG_GU,            // 古吉拉特文
    LANG_HA,            // 豪撒语
    LANG_HI,            // 印地语
    LANG_HR,            // 克罗地亚语
    LANG_HT,            // 海地克里奥尔
    LANG_HU,            // 匈牙利语
    LANG_HY,            // 亚美尼亚
    LANG_ID,            // 印度尼西亚
    LANG_IG,            // 伊博
    LANG_IS,            // 冰岛语
    LANG_IT,            // 意大利语
    LANG_IT_CH,            // 意大利语+瑞士
    LANG_JA,            // 日语
    LANG_KA,            // 格鲁吉亚语
    LANG_KK,            // 哈萨克语
    LANG_KN,            // 卡纳达
    LANG_KM,            // 高棉语
    LANG_KO,            // 朝鲜语
    LANG_KO_KR,            // 朝鲜语+南朝鲜
    LANG_KU,            // 库尔德
    LANG_KY,            // 吉尔吉斯斯坦
    LANG_LA,            // 拉丁语
    LANG_LB,            // 卢森堡语
    LANG_LO,            // 老挝
    LANG_LT,            // 立陶宛语
    LANG_LV,            // 拉托维亚语+列托
    LANG_MG,            // 马尔加什
    LANG_MI,            // 毛利
    LANG_MK,            // 马其顿语
    LANG_ML,            // 马拉雅拉姆
    LANG_MN,            // 蒙古
    LANG_MR,            // 马拉地语
    LANG_MS,            // 马来语
    LANG_MT,            // 马耳他
    LANG_MY,            // 缅甸
    LANG_NL,            // 荷兰语
    LANG_NL_BE,            // 荷兰语+比利时
    LANG_NE,            // 尼泊尔
    LANG_NO,            // 挪威语
    LANG_NY,            // 齐切瓦语
    LANG_PL,            // 波兰语
    LANG_PS,            // 普什图语
    LANG_PT,            // 葡萄牙语
    LANG_PT_BR,            // 葡萄牙语+巴西
    LANG_RO,            // 罗马尼亚语
    LANG_RU,            // 俄语
    LANG_SD,            // 信德
    LANG_SI,            // 僧伽罗语
    LANG_SK,            // 斯洛伐克语
    LANG_SL,            // 斯洛语尼亚语
    LANG_SM,            // 萨摩亚
    LANG_SN,            // 修纳
    LANG_SO,            // 索马里
    LANG_SQ,            // 阿尔巴尼亚语
    LANG_SR,            // 塞尔维亚语
    LANG_ST,            // 塞索托语
    LANG_SU,            // 巽他语
    LANG_SV,            // 瑞典语
    LANG_SV_SE,            // 瑞典语+瑞典
    LANG_SW,            // 斯瓦希里语
    LANG_TA,            // 泰米尔
    LANG_TE,            // 泰卢固语
    LANG_TG,            // 塔吉克斯坦
    LANG_TH,             //泰语
    LANG_TL,            // 菲律宾
    LANG_TR,            // 土耳其语
    LANG_UK,            // 乌克兰语
    LANG_UR,            // 乌尔都语
    LANG_UZ,            // 乌兹别克斯坦
    LANG_VI,            // 越南
    LANG_XH,            // 科萨
    LANG_YID,            // 意第绪语
    LANG_YO,            // 约鲁巴语
    LANG_ZH,            // 汉语
    LANG_ZH_TW,         // 繁体
    LANG_ZU               // 祖鲁语
} YouMeLanguageCode_t;

typedef enum YoumeTransRouteType {
    YOUME_TRANS_ROUTE_SERVER = 0,   // 传输路径为server转发
    YOUME_TRANS_ROUTE_P2P    = 1,   // 传输路径为局域网
}YoumeRtpRouteType_t;

typedef struct YMAudioFrameInfo {
    int channels;
    int sampleRate;
    int bytesPerFrame;
    int isFloat;
    int isBigEndian;
    int isSignedInteger;
    int isNonInterleaved;
    unsigned long long timestamp;
} YMAudioFrameInfo_t;

typedef enum YMVideoCodecType{
    YOUME_VIDEO_CODEC_H264 = 0,
    YOUME_VIDEO_CODEC_H265,
    YOUME_VIDEO_CODEC_VP8,
    YOUME_VIDEO_CODEC_VP9,
}YMVideoCodecType_t;

//订阅视频流类型，0:大流 1:小流 2:共享流 3:大流+共享流 4:小流+共享流
typedef enum YMVideoStreamType{
    YOUME_VIDEO_STREAM_MAIN = 0,
    YOUME_VIDEO_STREAM_SUB,
    YOUME_VIDEO_STREAM_SHARE,
    YOUME_VIDEO_STREAM_MAIN_AND_SHARE,
    YOUME_VIDEO_STREAM_SUB_AND_SHARE,
}YMVideoStreamType_t;

#endif // cocos2d_x_sdk_YouMeErrorCode_h
