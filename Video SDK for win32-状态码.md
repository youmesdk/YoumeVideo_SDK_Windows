# Video SDK 状态码

## YouMeEvent类型定义

枚举常量 |值| 含义
-------|------|------
YOUME_EVENT_INIT_OK                         | 0| SDK初始化成功
YOUME_EVENT_INIT_FAILED                     | 1| SDK初始化失败
YOUME_EVENT_JOIN_OK                         | 2| 进入语音频道成功
YOUME_EVENT_JOIN_FAILED                     | 3| 进入语音频道失败
YOUME_EVENT_LEAVED_ONE                      | 4| 退出单个语音频道完成
YOUME_EVENT_LEAVED_ALL                      | 5| 退出所有语音频道完成
YOUME_EVENT_PAUSED                          | 6| 暂停语音频道完成
YOUME_EVENT_RESUMED                         | 7| 恢复语音频道完成
YOUME_EVENT_SPEAK_SUCCESS                   | 8| 切换对指定频道讲话成功（适用于多频道模式）
YOUME_EVENT_SPEAK_FAILED                    | 9|  切换对指定频道讲话失败（适用于多频道模式）
YOUME_EVENT_RECONNECTING                    | 10| 断网了，正在重连
YOUME_EVENT_RECONNECTED                     | 11| 断网重连成功
YOUME_EVENT_REC_PERMISSION_STATUS           | 12| 通知录音权限状态，成功获取权限时错误码为YOUME_SUCCESS，获取失败为YOUME_ERROR_REC_NO_PERMISSION（此时不管麦克风mute状态如何，都没有声音输出）
YOUME_EVENT_BGM_STOPPED                     | 13| 通知背景音乐播放结束
YOUME_EVENT_BGM_FAILED                      | 14| 通知背景音乐播放失败
YOUME_EVENT_OTHERS_MIC_ON                   | 16| 其他用户麦克风打开
YOUME_EVENT_OTHERS_MIC_OFF                  | 17| 其他用户麦克风关闭
YOUME_EVENT_OTHERS_SPEAKER_ON               | 18| 其他用户扬声器打开
YOUME_EVENT_OTHERS_SPEAKER_OFF              | 19| 其他用户扬声器关闭
YOUME_EVENT_OTHERS_VOICE_ON                 | 20| 其他用户进入讲话状态
YOUME_EVENT_OTHERS_VOICE_OFF                | 21| 其他用户进入静默状态
YOUME_EVENT_MY_MIC_LEVEL                    | 22| 麦克风的语音级别
YOUME_EVENT_MIC_CTR_ON                      | 23| 麦克风被其他用户打开
YOUME_EVENT_MIC_CTR_OFF                     | 24| 麦克风被其他用户关闭
YOUME_EVENT_SPEAKER_CTR_ON                  | 25| 扬声器被其他用户打开
YOUME_EVENT_SPEAKER_CTR_OFF                 | 26| 扬声器被其他用户关闭
YOUME_EVENT_LISTEN_OTHER_ON                 | 27| 取消屏蔽某人语音
YOUME_EVENT_LISTEN_OTHER_OFF                | 28| 屏蔽某人语音
YOUME_EVENT_LOCAL_MIC_ON                    | 29| 自己的麦克风打开
YOUME_EVENT_LOCAL_MIC_OFF                   | 30| 自己的麦克风关闭
YOUME_EVENT_LOCAL_SPEAKER_ON	            | 31| 自己的扬声器打开
YOUME_EVENT_LOCAL_SPEAKER_OFF	            | 32| 自己的扬声器关闭
YOUME_EVENT_GRABMIC_START_OK                | 33| 发起抢麦活动成功
YOUME_EVENT_GRABMIC_START_FAILED            | 34| 发起抢麦活动失败
YOUME_EVENT_GRABMIC_STOP_OK                 | 35| 停止抢麦活动成功
YOUME_EVENT_GRABMIC_STOP_FAILED             | 36| 停止抢麦活动失败
YOUME_EVENT_GRABMIC_REQUEST_OK	            | 37| 抢麦成功（可以说话）
YOUME_EVENT_GRABMIC_REQUEST_FAILED          | 38| 抢麦失败
YOUME_EVENT_GRABMIC_REQUEST_WAIT            | 39| 进入抢麦等待队列（仅权重模式下会回调此事件）
YOUME_EVENT_GRABMIC_RELEASE_OK              | 40| 释放麦成功
YOUME_EVENT_GRABMIC_RELEASE_FAILED          | 41| 释放麦失败
YOUME_EVENT_GRABMIC_ENDMIC                  | 42| 不再占用麦（到麦使用时间或者其他原因）
YOUME_EVENT_GRABMIC_NOTIFY_START            | 43| [通知]抢麦活动开始
YOUME_EVENT_GRABMIC_NOTIFY_STOP             | 44| [通知]抢麦活动结束
YOUME_EVENT_GRABMIC_NOTIFY_HASMIC           | 45| [通知]有麦可以抢
YOUME_EVENT_GRABMIC_NOTIFY_NOMIC            | 46| [通知]没有麦可以抢
YOUME_EVENT_INVITEMIC_SETOPT_OK             | 47| 连麦设置成功
YOUME_EVENT_INVITEMIC_SETOPT_FAILED         | 48| 连麦设置失败
YOUME_EVENT_INVITEMIC_REQUEST_OK            | 49| 请求连麦成功（连上了，需等待对方回应）
YOUME_EVENT_INVITEMIC_REQUEST_FAILED        | 50| 请求连麦失败
YOUME_EVENT_INVITEMIC_RESPONSE_OK           | 51| 响应连麦成功（被叫方无论同意/拒绝都会收到此事件，错误码是YOUME_ERROR_INVITEMIC_REJECT表示拒绝）
YOUME_EVENT_INVITEMIC_RESPONSE_FAILED       | 52| 响应连麦失败
YOUME_EVENT_INVITEMIC_STOP_OK               | 53| 停止连麦成功
YOUME_EVENT_INVITEMIC_STOP_FAILED           | 54| 停止连麦失败
YOUME_EVENT_INVITEMIC_CAN_TALK              | 55| 双方可以通话了（响应方已经同意）
YOUME_EVENT_INVITEMIC_CANNOT_TALK           | 56| 双方不可以再通话了（有一方结束了连麦或者连麦时间到）
YOUME_EVENT_INVITEMIC_NOTIFY_CALL           | 57| [通知]有人请求与你连麦
YOUME_EVENT_INVITEMIC_NOTIFY_ANSWER         | 58| [通知]对方对你的连麦请求作出了响应（同意/拒绝/超时，同意的话双方就可以通话了）
YOUME_EVENT_INVITEMIC_NOTIFY_CANCEL         | 59| [通知]连麦过程中，对方结束了连麦或者连麦时间到
YOUME_EVENT_SEND_MESSAGE_RESULT             | 60| sendMessage成功与否的通知，param为回传的requestID
YOUME_EVENT_MESSAGE_NOTIFY                  | 61| 收到Message, param为message内容
YOUME_EVENT_KICK_RESULT                     | 64| 踢人的应答, param: 被踢者ID
YOUME_EVENT_KICK_NOTIFY                     | 65| 被踢通知   ,param: （踢人者ID，被踢原因，被禁时间）
YOUME_EVENT_FAREND_VOICE_LEVEL              | 66| 远端说话人音量大小
YOUME_EVENT_OTHERS_BE_KICKED                | 67| 房间里其他人被踢出房间
YOUME_EVENT_AUDIO_START_FAIL                | 72| 音频启动失败，可能是设备被其他应用占用
YOUME_EVENT_AUDIO_INPUT_DEVICE_CONNECT      | 73| 音频采集设备插入，移动端无效
YOUME_EVENT_AUDIO_INPUT_DEVICE_DISCONNECT   | 74| 音频采集设备拔出，移动端无效
YOUME_EVENT_SWITCH_OUTPUT                   | 75| 切换扬声器/听筒
YOUME_EVENT_OTHERS_VIDEO_ON                 | 200| 收到其它用户的视频流
YOUME_EVENT_MASK_VIDEO_BY_OTHER_USER        | 204| 视频被其他用户屏蔽
YOUME_EVENT_RESUME_VIDEO_BY_OTHER_USER      | 205| 视频被其他用户恢复
YOUME_EVENT_MASK_VIDEO_FOR_USER             | 206| 屏蔽了谁的视频
YOUME_EVENT_RESUME_VIDEO_FOR_USER           | 207| 恢复了谁的视频
YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN          | 208| 其它用户的视频流断开（包含网络中断的情况）
YOUME_EVENT_OTHERS_VIDEO_INPUT_START        | 209| 其他用户视频输入开始（内部采集下开启摄像头/外部输入下开始input）
YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP         | 210| 其他用户视频输入停止（内部采集下停止摄像头/外部输入下停止input）
YOUME_EVENT_MEDIA_DATA_ROAD_PASS            | 211| 音视频数据通路连通，定时检测，一开始收到数据会收到PASS事件，之后变化的时候会发送
YOUME_EVENT_MEDIA_DATA_ROAD_BLOCK           | 212| 音视频数据通路不通
YOUME_EVENT_QUERY_USERS_VIDEO_INFO          | 213| 查询用户视频信息返回
YOUME_EVENT_SET_USERS_VIDEO_INFO            | 214| 设置用户接收视频信息返回
YOUME_EVENT_LOCAL_VIDEO_INPUT_START         | 215| 本地视频输入开始（内部采集下开始摄像头/外部输入下开始input）
YOUME_EVENT_LOCAL_VIDEO_INPUT_STOP          | 216| 本地视频输入停止（内部采集下停止摄像头/外部输入下停止input）
YOUME_EVENT_START_PUSH                      | 217| 设置startPush的返回事件
YOUME_EVENT_SET_PUSH_MIX                    | 218| 设置setPushMix的返回事件
YOUME_EVENT_ADD_PUSH_MIX_USER               | 219| 设置addPushMixUser的返回事件，参数userID
YOUME_EVENT_OTHER_SET_PUSH_MIX              | 220| 在自己调用了setPushMix还没停止的情况下，房间内有别人调用setPushMix，自己被踢
YOUME_EVENT_LOCAL_SHARE_INPUT_START         | 221| 本地共享视频输入开始
YOUME_EVENT_LOCAL_SHARE_INPUT_STOP          | 222| 本地共享视频输入停止
YOUME_EVENT_OTHERS_SHARE_INPUT_START        | 223| 其他用户共享视频输入开始
YOUME_EVENT_OTHERS_SHARE_INPUT_STOP         | 224| 其他用户共享视频输入停止
YOUME_EVENT_OTHERS_DATA_ERROR               | 300| 数据错误
YOUME_EVENT_OTHERS_NETWORK_BAD              | 301| 网络不好
YOUME_EVENT_OTHERS_BLACK_FULL               | 302| 黑屏
YOUME_EVENT_OTHERS_GREEN_FULL               | 303| 绿屏
YOUME_EVENT_OTHERS_BLACK_BORDER             | 304| 黑边
YOUME_EVENT_OTHERS_GREEN_BORDER             | 305| 绿边
YOUME_EVENT_OTHERS_BLURRED_SCREEN           | 306| 花屏
YOUME_EVENT_OTHERS_ENCODER_ERROR            | 307| 编码错误
YOUME_EVENT_OTHERS_DECODER_ERROR            | 308| 解码错误
YOUME_EVENT_CAMERA_DEVICE_CONNECT           | 400| 摄像头设备插入，移动端无效
YOUME_EVENT_CAMERA_DEVICE_DISCONNECT        | 401| 摄像头设备拔出，移动端无效
YOUME_EVENT_EOF                             |1000|

## YouMeErrorCode类型定义

枚举常量|值|含义
----|------|-----
YOUME_SUCCESS                            | 0| 成功
YOUME_ERROR_API_NOT_SUPPORTED            |-1| 正在使用的SDK不支持特定的API
YOUME_ERROR_INVALID_PARAM                |-2| 传入参数错误
YOUME_ERROR_ALREADY_INIT                 |-3| 已经初始化
YOUME_ERROR_NOT_INIT                     |-4| 还没有初始化，在调用某函数之前要先调用初始化并且要据返回值确保初始化成功
YOUME_ERROR_CHANNEL_EXIST                |-5| 要加入的频道已经存在
YOUME_ERROR_CHANNEL_NOT_EXIST            |-6| 要退出的频道不存在，或者其它操作指定的频道不存在
YOUME_ERROR_WRONG_STATE                  |-7| 状态错误
YOUME_ERROR_NOT_ALLOWED_MOBILE_NETWROK   |-8| 不允许使用移动网络
YOUME_ERROR_WRONG_CHANNEL_MODE           |-9| 在单频道模式下调用了多频道接口，或者反之
YOUME_ERROR_TOO_MANY_CHANNELS            |-10| 同时加入了太多频道
YOUME_ERROR_TOKEN_ERROR                  |-11| 传入的token认证错误
YOUME_ERROR_NOT_IN_CHANNEL               |-12| 用户不在该频道
YOUME_ERROR_BE_KICK                      |-13| 被踢了，还在禁止时间内，不允许进入房间
YOUME_ERROR_DEVICE_NOT_VALID             |-14| 设置的设备不可用
YOUME_ERROR_API_NOT_ALLOWED              |-15| 没有特定功能的权限，需要的话请联系我们
YOUME_ERROR_MEMORY_OUT                   |-100| 内存错误
YOUME_ERROR_START_FAILED                 |-101| 启动引擎失败
YOUME_ERROR_STOP_FAILED                  |-102| 停止引擎失败
YOUME_ERROR_ILLEGAL_SDK                  |-103| 非法使用SDK
YOUME_ERROR_SERVER_INVALID               |-104| 语音服务不可用
YOUME_ERROR_NETWORK_ERROR                |-105| 网络错误
YOUME_ERROR_SERVER_INTER_ERROR           |-106| 服务器内部错误
YOUME_ERROR_QUERY_RESTAPI_FAIL           |-107| 请求RestApi信息失败了
YOUME_ERROR_USER_ABORT                   |-108| 用户请求中断当前操作
YOUME_ERROR_SEND_MESSAGE_FAIL            |-109| 发送消息失败
YOUME_ERROR_SET_PUSH_PARAM_FAIL          |-110| 向服务器设置Push参数失败
YOUME_ERROR_INIT_SHARE_FAIL              |-111| 初始化共享设备失败
YOUME_ERROR_START_SHARE_FAIL             |-112| 开始视频共享失败
YOUME_ERROR_REC_INIT_FAILED              |-201| 录音模块初始化失败
YOUME_ERROR_REC_NO_PERMISSION            |-202| 没有录音权限
YOUME_ERROR_REC_NO_DATA                  |-203| 虽然初始化成功，但没有音频数据输出，比如oppo系列机在录音权限被禁止的时候
YOUME_ERROR_REC_OTHERS                   |-204| 其他录音模块的错误
YOUME_ERROR_REC_PERMISSION_UNDEFINED     |-205| 录音权限未确定，iOS显示是否允许录音权限对话框时，回的是这个错误码
YOUME_ERROR_GRABMIC_FULL				 |-301| 抢麦失败，人数满
YOUME_ERROR_GRABMIC_HASEND				 |-302| 抢麦失败，活动已经结束
YOUME_ERROR_INVITEMIC_NOUSER			 |-401| 连麦失败，用户不存在
YOUME_ERROR_INVITEMIC_OFFLINE			 |-402| 连麦失败，用户已离线
YOUME_ERROR_INVITEMIC_REJECT			 |-403| 连麦失败，用户拒绝
YOUME_ERROR_INVITEMIC_TIMEOUT			 |-404| 连麦失败，两种情况：1.连麦时，对方超时无应答 2.话中，双方通话时间到
YOUME_ERROR_UNKNOWN                      |-1000| 未知错误

## YouMeAVStatisticType 类型定义

枚举常量|值|含义
----|------|-----
YOUME_AVS_AUDIO_CODERATE                 | 1 |  音频传输码率，userid是自己:上行码率，userid其它人:下行码率，单位Bps, *8/1000 可以转换为kbps
YOUME_AVS_VIDEO_CODERATE                 | 2 |  视频传输码率，userid是自己:上行码率，userid其它人:下行码率，单位Bps, *8/1000 可以转换为kbps
YOUME_AVS_VIDEO_FRAMERATE                | 3 |  视频帧率，userid是自己:上行帧率(编码前)，userid其它人:下行帧率(解码后)
YOUME_AVS_AUDIO_PACKET_UP_LOSS_RATE      | 4 |  音频上行丢包率,千分比
YOUME_AVS_AUDIO_PACKET_DOWN_LOSS_RATE    | 5 |  音频下行丢包率,千分比
YOUME_AVS_VIDEO_PACKET_UP_LOSS_RATE      | 6 |  视频上行丢包率,千分比
YOUME_AVS_VIDEO_PACKET_DOWN_LOSS_RATE    | 7 |  视频下行丢包率,千分比
YOUME_AVS_AUDIO_DELAY_MS                 | 8 |  音频延迟，单位毫秒
YOUME_AVS_VIDEO_DELAY_MS                 | 9 |  视频延迟，单位毫秒
YOUME_AVS_VIDEO_BLOCK                    |10 |  视频卡顿,是否发生过卡顿
YOUME_AVS_AUDIO_PACKET_UP_LOSS_HALF      |11 |  音频上行的服务器丢包率，千分比
YOUME_AVS_VIDEO_PACKET_UP_LOSS_HALF      |12 |  视频上行的服务器丢包率，千分比
YOUME_AVS_RECV_DATA_STAT                 |13 |  下行带宽,单位Bps

## YOUME_RTC_SERVER_REGION类型定义

枚举常量|值|含义
----|------|-----
    RTC_CN_SERVER       | 0| 中国
    RTC_HK_SERVER       | 1| 香港
    RTC_US_SERVER       | 2| 美国东部
    RTC_SG_SERVER       | 3| 新加坡
    RTC_KR_SERVER       | 4| 韩国
    RTC_AU_SERVER       | 5| 澳洲
    RTC_DE_SERVER       | 6| 德国
    RTC_BR_SERVER       | 7| 巴西
    RTC_IN_SERVER       | 8| 印度
    RTC_JP_SERVER       | 9| 日本
    RTC_IE_SERVER       | 10| 爱尔兰
    RTC_USW_SERVER      | 11| 美国西部
    RTC_USM_SERVER      | 12| 美国中部
    RTC_CA_SERVER       | 13| 加拿大
    RTC_LON_SERVER      | 14| 伦敦
    RTC_FRA_SERVER      | 15| 法兰克福
    RTC_DXB_SERVER      | 16| 迪拜
    RTC_EXT_SERVER      |10000| 使用扩展服务器
    RTC_DEFAULT_SERVER  |10001| 缺省服务器


## YouMeKickReason类型定义
枚举常量|值|含义
----|------|-----
YOUME_KICK_ADMIN    |1     | 管理员踢人
YOUME_KICK_RELOGIN  |2     | 多端登录被踢

## YouMeBroadcast房间内的广播消息
枚举常量|值|含义
----|------|-----
YOUME_BROADCAST_NONE    |0|
YOUME_BROADCAST_GRABMIC_BROADCAST_GETMIC  |1| 有人抢到了麦
YOUME_BROADCAST_GRABMIC_BROADCAST_FREEMIC    |2| 有人释放了麦
YOUME_BROADCAST_INVITEMIC_BROADCAST_CONNECT  |3| A和B正在连麦
YOUME_BROADCAST_INVITEMIC_BROADCAST_DISCONNECT    |4| A和B取消了连麦


## YOUME_LOG_LEVEL类型定义
枚举常量|值|含义
----|------|-----
LOG_DISABLED    | 0|禁用日志
LOG_FATAL       | 1|严重错误
LOG_ERROR       | 10|错误
LOG_WARNING     | 20|警告
LOG_INFO        | 40|信息
LOG_DEBUG       | 50|调试
LOG_VERBOSE     | 60|所有日志

## YOUME_SAMPLE_RATE类型定义
枚举常量|值
----|------
SAMPLE_RATE_8  | 8000
SAMPLE_RATE_16 | 16000
SAMPLE_RATE_24 | 24000
SAMPLE_RATE_32 | 32000
SAMPLE_RATE_44 | 44100
SAMPLE_RATE_48 | 48000

## YOUME_AUDIO_QUALITY类型定义
枚举常量|值
----|------
LOW_QUALITY  | 0
HIGH_QUALITY | 1

## YouMeVideoRenderMode类型定义
枚举常量|值|含义
----|------|-----
SCALE_ASPECT_FILL  | 0| 填充
SCALE_ASPECT_FIT | 1| 裁剪
SCALE_ASPECT_BALANCED | 2| 自适应

## YOUME_VIDEO_FMT类型定义
枚举常量|值
----|------
VIDEO_FMT_RGBA32 |0
VIDEO_FMT_BGRA32 |1
VIDEO_FMT_YUV420P |2
VIDEO_FMT_NV21 |3
VIDEO_FMT_YV12 |4
VIDEO_FMT_CVPIXELBUFFER |5
VIDEO_FMT_TEXTURE |6
VIDEO_FMT_TEXTURE_OES |7

## YouMeUserRole类型定义

枚举常量|值|含义
----|------|-----
YOUME_USER_NONE             |0| 非法用户，调用API时不能传此参数
YOUME_USER_TALKER_FREE      |1| 自由讲话者，适用于小组通话（建议小组成员数最多10个），每个人都可以随时讲话, 同一个时刻只能在一个语音频道里面
YOUME_USER_TALKER_ON_DEMAND |2| 需要通过抢麦等请求麦克风权限之后才可以讲话，适用于较大的组或工会等（比如几十个人），同一个时刻只能有一个或几个人能讲话, 同一个时刻只能在一个语音频道里面
YOUME_USER_LISTENER         |3| 听众，主播/指挥/嘉宾的听众，同一个时刻只能在一个语音频道里面，只听不讲
YOUME_USER_COMMANDER        |4| 指挥，国家/帮派等的指挥官，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
YOUME_USER_HOST             |5| 主播，广播型语音频道的主持人，同一个时刻只能在一个语音频道里面，可以随时讲话，可以播放背景音乐，戴耳机情况下可以监听自己语音
YOUME_USER_GUSET            |6| 嘉宾，主播或指挥邀请的连麦嘉宾，同一个时刻只能在一个语音频道里面， 可以随时讲话

## YouMeVideoMirrorMode类型定义

枚举常量|值|含义
----|------|-----
YOUME_VIDEO_MIRROR_MODE_AUTO        |0| 内部采集自适应镜像，外部采集为关闭镜像
YOUME_VIDEO_MIRROR_MODE_ENABLED     |1| 近端和远端都镜像
YOUME_VIDEO_MIRROR_MODE_DISABLED    |2| 关闭镜像
YOUME_VIDEO_MIRROR_MODE_NEAR        |3| 近端镜像
YOUME_VIDEO_MIRROR_MODE_FAR         |4| 远端镜像