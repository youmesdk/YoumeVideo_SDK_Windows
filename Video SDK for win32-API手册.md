# Video SDK for win32 API接口手册

## 相关异步/同步处理方法介绍

游密音视频引擎SDK提供的全部为C/C++接口,接口调用都会立即返回,凡是本身需要较长耗时的接口调用都会采用异步回调的方式,所有接口都可以在主线程中直接使用。回调在主线程。

## API调用说明

API的调用可使用`IYouMeVoiceEngine::getInstance ()->`来直接操作，接口使用的基本流程为`初始化`->`收到初始化成功回调通知`->`加入频道`->`收到加入频道成功回调通知`->`使用其它接口`->`离开频道`->`反初始化`，要确保严格按照上述的顺序使用接口。

## 实现回调
主要回调申明在以下头文件：
- `IYouMeEventCallback.h` SDK运行时的各种状态和操作结果事件回调
- `IYouMeVideoCallback.h` 音视频相关数据回调

使用者要继承类`IYouMeEventCallback` 、`IYouMeMemberChangeCallback`、`IYouMeAVStatisticCallback`并实现其纯虚函数（回调函数），在调用初始化函数时传入指向子类的指针。回调都在子线程中执行，不能用于更新UI等耗时操作。

*  首先声明一个类YouMeVoiceEngineImp（类名可自取）来注册回调事件：

  ``` cpp
  class YouMeVoiceEngineImp : public IYouMeEventCallback, public IYouMeMemberChangeCallback, public IYouMeAVStatisticCallback
  {
  public:
      static YouMeVoiceEngineImp *getInstance ();
      virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param);
	  virtual void onAVStatistic( YouMeAVStatisticType type,  const char* userID,  int value );
	  //成员列表变化通知，推荐使用
	  virtual void onMemberChange( const char* channel, const char* listMemberChangeJson, bool bUpdate );
	  //成员列表变化通知，如果stl库有兼容问题，就不能使用该回调
      virtual void onMemberChange( const char*  channel, std::list<MemberChange>& listMemberChange, bool bUpdate);
  }

  ```

* 然后在该类YouMeVoiceEngineImp下必须实现以下方法：

  ``` cpp

  //监听各类回调事件
  void  onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param)
  {
       switch (event)
      {
      //case案例只覆盖了部分，仅供参考，详情请查询枚举类型YouMeEvent
      case YOUME_EVENT_INIT_OK:
				//"初始化成功";
			break;
		case YOUME_EVENT_INIT_FAILED:
				// "初始化失败，错误码：" + errorCode;
			break;
		case YOUME_EVENT_JOIN_OK:
			 //"加入频道成功";
			break;
		case YOUME_EVENT_LEAVED_ALL:
			// "离开频道成功";
			break;
		case YOUME_EVENT_JOIN_FAILED:
			//进入语音频道失败
			break;
		case YOUME_EVENT_REC_PERMISSION_STATUS:
		  // "通知录音权限状态，成功获取权限时错误码为YOUME_SUCCESS，获取失败为YOUME_ERROR_REC_NO_PERMISSION（此时不管麦克风mute状态如何，都没有声音输出）";
			break;
		case YOUME_EVENT_RECONNECTING:
			//"断网了，正在重连";
			break;
		case YOUME_EVENT_RECONNECTED:
			// "断网重连成功";
			break;
		case  YOUME_EVENT_OTHERS_MIC_OFF:
			//其他用户的麦克风关闭：
		    break;
		case YOUME_EVENT_OTHERS_MIC_ON:
			//其他用户的麦克风打开：
			break;
		case YOUME_EVENT_OTHERS_SPEAKER_ON:
			//其他用户的扬声器打开：
			break;
		case YOUME_EVENT_OTHERS_SPEAKER_OFF:
			//其他用户的扬声器关闭
			break;
		case YOUME_EVENT_OTHERS_VOICE_ON:
			//其他用户开始讲话
			break;
		case YOUME_EVENT_OTHERS_VOICE_OFF:
			//其他用户停止讲话
			break;
		case YOUME_EVENT_MY_MIC_LEVEL:
			//麦克风的语音级别，值是放在error这个整形参数了里
			break;
		case YOUME_EVENT_MIC_CTR_ON:
			//麦克风被其他用户打开
			break;
		case YOUME_EVENT_MIC_CTR_OFF:
			//麦克风被其他用户关闭
			break;
		case YOUME_EVENT_SPEAKER_CTR_ON:
			//扬声器被其他用户打开
			break;
		case YOUME_EVENT_SPEAKER_CTR_OFF:
			//扬声器被其他用户关闭
			break;
		case YOUME_EVENT_LISTEN_OTHER_ON:
			//取消屏蔽某人语音
			break;
		case YOUME_EVENT_LISTEN_OTHER_OFF:
			//屏蔽某人语音
			break;
		default:
			//"事件类型" + eventType + ",错误码" +
			break;
		}  
  }

  void onAVStatistic( YouMeAVStatisticType type,  const char* userID,  int value )
  {
	  switch( type ){
		  case YOUME_AVS_VIDEO_CODERATE:
			{
				//userID 对应的视频码率
			}
			break;
		 default:
		 break;
	  }
  }

  //成员列表变化通知，推荐使用
  void onMemberChange( const char* channel, const char* listMemberChangeJson, bool bUpdate )
  {
	  //listMemberChangeJson 数据格式如下：
	  /*
		{"channelid":"2418video","memchange":[{"isJoin":true,"userid":"1001590"},{"isJoin":false,"userid":"1001591"}]}
	  */
  }
  //成员列表变化通知，如果stl库有兼容问题，就不能使用该回调
  void onMemberChange( const char*  channel, std::list<MemberChange>& listMemberChange, bool bUpdate)
  {

  }

  ```

### 初始化
* **语法**

``` c++
YouMeErrorCode init(
const char* strAppKey,
const char* strAPPSecret,
YOUME_RTC_SERVER_REGION serverRegionId,
const char* strExtServerRegionName);
```

* **功能**
初始化音视频引擎，做APP验证和资源初始化。

* **参数说明**
`strAPPKey`：从游密申请到的 app key, 这个你们应用程序的唯一标识。
`strAPPSecret`：对应 strAPPKey 的私钥, 这个需要妥善保存，不要暴露给其他人。
`serverRegionId`：设置首选连接服务器的区域码，如果在初始化时不能确定区域，可以填RTC_DEFAULT_SERVER，后面确定时通过 SetServerRegion 设置。如果YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。
`strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
// YOUME_EVENT_INIT_OK  - 表明初始化成功
// YOUME_EVENT_INIT_FAILED - 表明初始化失败，最常见的失败原因是网络错误或者 AppKey-AppSecret 错误
void  onEvent (const char* strParam);
```

### 判断是否初始化完成

* **语法**

``` c++
bool isInited();
```

* **功能**
判断音视频引擎是否初始化完成。

* **返回值**
true——初始化完成，false——未初始化或者初始化未完成

### 加入语音频道（单频道）

* **语法**

``` c++
YouMeErrorCode joinChannelSingleMode(const char* strUserID, const char* strChannelID, YouMeUserRole_t userRole, bool bVideoAutoRecv = true);
```
* **功能**
加入语音频道（单频道模式，每个时刻只能在一个语音频道里面）。

* **参数说明**
`strUserID`：全局唯一的用户标识，全局指在当前应用程序的范围内。
`strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。
`userRole`：用户在语音频道里面的角色，见YouMeUserRole定义。
`bVideoAutoRecv`: 进入房间成功后，是否自动接收视频，默认为true, 如果设置为false，需要调用`setUsersVideoInfo`后才会接收对方的视频数据

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
//YOUME_EVENT_JOIN_OK - 成功进入语音频道
//YOUME_EVENT_JOIN_FAILED - 进入语音频道失败，可能原因是网络或服务器有问题
void  onEvent (const char* strParam);
```

### 加入语音频道（多频道）

* **语法**

``` c++
YouMeErrorCode joinChannelMultiMode (const char* strUserID, const char* strChannelID, YouMeUserRole_t eUserRole);
```

* **功能**
加入语音频道（多频道模式，可以同时听多个语音频道的内容，但每个时刻只能对着一个频道讲话）。

* **参数说明**
`strUserID`：全局唯一的用户标识，全局指在当前应用程序的范围内。
`strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。
`eUserRole`: 用户角色，用于决定讲话/播放背景音乐等权限

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
//YOUME_EVENT_JOIN_OK - 成功进入语音频道
//YOUME_EVENT_JOIN_FAILED - 进入语音频道失败，可能原因是网络或服务器有问题
void  onEvent (const char* strParam);
```

### 指定讲话频道

* **语法**

``` c++
YouMeErrorCode speakToChannel (const char* strChannelID);
```
* **功能**
多频道模式下，指定当前要讲话的频道。

* **参数说明**
`strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
//YOUME_EVENT_SPEAK_SUCCESS - 成功切入到指定语音频道
//YOUME_EVENT_SPEAK_FAILED - 切入指定语音频道失败，可能原因是网络或服务器有问题
void  onEvent (const char* strParam);
```


### 退出指定的语音频道

* **语法**

``` c++
YouMeErrorCode leaveChannelMultiMode (const char* strChannelID);
```
* **功能**
多频道模式下，退出指定的语音频道。

* **参数说明**
`strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
//YOUME_EVENT_LEAVED_ONE - 成功退出指定语音频道
void  onEvent (const char* strParam);
```

### 退出所有语音频道

* **语法**

``` c++
YouMeErrorCode leaveChannelAll ();
```
* **功能**
退出所有的语音频道（单频道模式下直接调用此函数离开频道即可）。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//涉及到的主要回调事件有：
//YOUME_EVENT_LEAVED_ALL - 成功退出所有语音频道
void  onEvent (const char* strParam);
```

### 设置用户身份

* **语法**

``` c++
YouMeErrorCode setUserRole (YouMeUserRole_t eUserRole);
```
* **功能**
切换身份(仅支持单频道模式，进入房间以后设置)。

* **参数说明**
`eUserRole`：用户身份。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 获取用户身份

* **语法**

``` c++
YouMeUserRole_t getUserRole ();
```
* **功能**
获取身份(仅支持单频道模式)。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 查询是否在某个语音频道内

* **语法**

``` c++
bool isInChannel(const char* pChannelID);
```
* **功能**
查询当前是否在某个语音频道内

* **参数说明**
`pChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

* **返回值**
true——在频道内，false——没有在频道内

### 查询是否在语音频道内

* **语法**

``` c++
bool isInChannel();
```
* **功能**
查询当前是否在语音频道内

* **返回值**
true——在频道内，false——没有在频道内

### 设置扬声器状态

* **语法**

``` c++
void setSpeakerMute (bool mute);
```
* **功能**
打开/关闭扬声器。建议该状态值在加入房间成功后按需再重置一次。

* **参数说明**
`mute`:true——关闭扬声器，false——开启扬声器。


### 获取扬声器状态

* **语法**

``` c++
bool getSpeakerMute();
```

* **功能**
获取当前扬声器状态。

* **返回值**
true——扬声器关闭，false——扬声器开启。


### 设置麦克风状态

* **语法**

``` c++
void setMicrophoneMute (bool mute);
```

* **功能**
打开／关闭麦克风。建议该状态值在加入房间成功后按需再重置一次。

* **参数说明**
`mute`:true——关闭麦克风，false——开启麦克风。


### 获取麦克风状态

* **语法**

``` c++
bool getMicrophoneMute ();
```

* **功能**
获取当前麦克风状态。

* **返回值**
true——麦克风关闭，false——麦克风开启。

### 设置是否通知别人麦克风和扬声器的开关

* **语法**

``` c++
void setAutoSendStatus( bool bAutoSend );
```

* **功能**
设置是否通知别人,自己麦克风和扬声器的开关状态

* **参数说明**
`bAutoSend`:true——通知，false——不通知。

### 设置音量

* **语法**

``` c++
void setVolume (const unsigned int &uiVolume);
```

* **功能**
设置当前程序输出音量大小。建议该状态值在加入房间成功后按需再重置一次。

* **参数说明**
`uiVolume`:当前音量大小，范围[0-100]。

### 获取音量

* **语法**

``` c++
unsigned int getVolume ();
```

* **功能**
获取当前程序输出音量大小。

* **返回值**
当前音量大小，范围[0-100]。


### 设置是否允许使用移动网络

* **语法**

``` c++
void setUseMobileNetworkEnabled (bool bEnabled);
```

* **功能**
设置是否允许使用移动网络。在WIFI和移动网络都可用的情况下会优先使用WIFI，在没有WIFI的情况下，如果设置允许使用移动网络，那么会使用移动网络进行语音通信，否则通信会失败。


* **参数说明**
`bEnabled`:true——允许使用移动网络，false——禁止使用移动网络。


### 获取是否允许使用移动网络

* **语法**

``` c++
bool getUseMobileNetworkEnabled () ;
```

* **功能**
获取是否允许SDK在没有WIFI的情况使用移动网络进行语音通信。

* **返回值**
true——允许使用移动网络，false——禁止使用移动网络，默认情况下允许使用移动网络。

### 控制他人麦克风

* **语法**

``` c++
YouMeErrorCode setOtherMicMute (const char* pUserID,bool mute);
```

* **功能**
控制他人的麦克风状态

* **参数说明**
`pUserID`：要控制的用户ID
`mute`：是否静音。true:静音别人的麦克风，false：开启别人的麦克风

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 控制他人扬声器

* **语法**

``` c++
YouMeErrorCode setOtherSpeakerMute (const char* pUserID,bool mute);
```

* **功能**
控制他人的扬声器状态

* **参数说明**
`pUserID`：要控制的用户ID
`mute`：是否静音。true:静音别人的扬声器，false：开启别人的扬声器

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置是否听某人的语音

* **语法**

``` c++
YouMeErrorCode setListenOtherVoice (const char* userID,bool on);
```

* **功能**
设置是否听某人的语音。

* **参数说明**
`userID`：要控制的用户ID。
`on`：true表示开启接收指定用户的语音，false表示屏蔽指定用户的语音。

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 视频数据输入

* **语法**

``` c++
YouMeErrorCode inputVideoFrame (void* data, int len, int width, int	height, int fmt, int rotation, int mirror, uint64_t timestamp);
```

* **功能**
视频数据输入，软件处理方式(七牛接口，房间内其它用户会收到YOUME_EVENT_OTHERS_VIDEO_INPUT_START事件)

* **参数说明**
`data`：视频帧数据
`len`：视频数据大小
`width`：视频图像宽
`height`：视频图像高
`fmt`：视频格式
`rotation`：视频角度
`mirror`：镜像
`timestamp`：时间戳

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### ios视频数据输入

* **语法**

``` c++
### inputVideoFrameForIOS
YouMeErrorCode inputVideoFrameForIOS (void* pixelbuffer, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);
```

* **功能**
ios视频数据输入，硬件处理方式

* **参数说明**
`pixelbuffer`：CVPixelBuffer
`width`：视频图像宽
`height`：视频图像高
`fmt`：视频格式
`rotation`：视频角度
`mirror`：镜像
`timestamp`：时间戳

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### android视频数据输入

* **语法**

``` c++
### inputVideoFrameForAndroid
YouMeErrorCode inputVideoFrameForAndroid (int textureId, float* matrix, int width, int height, int fmt, int rotation, int mirror, uint64_t timestamp);
```

* **功能**
android视频数据输入，硬件处理方式

* **参数说明**
`textureId`：纹理id
`matrix`：纹理矩阵
`width`：视频图像宽
`height`：视频图像高
`fmt`：视频格式
`rotation`：视频角度
`mirror`：镜像
`timestamp`：时间戳

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 停止视频数据输入

* **语法**

``` c++
### stopInputVideoFrame
YouMeErrorCode stopInputVideoFrame ();
```

* **功能**
停止视频数据输入(七牛接口，在inputVideoFrame之后调用，房间内其它用户会收到YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP事件)

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 音频数据输入

* **语法**

``` c++
### inputAudioFrame
YouMeErrorCode inputAudioFrame (void* data, int len, uint64_t timestamp, int channels = 1, int bInterleaved = 0);
```

* **功能**
(七牛接口)将提供的音频数据混合到麦克风或者扬声器的音轨里面。

* **参数说明**
`data`：指向PCM数据的缓冲区
`len`：音频数据的大小
`timestamp`：时间戳
`channels`：声道数，1:单声道，2:双声道，其它非法
`bInterleaved`：音频数据打包格式（仅对双声道有效）

* **返回值**
如果成功返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 暂停通话

* **语法**

``` c++
YouMeErrorCode pauseChannel();
```

* **功能**
暂停通话，释放对麦克风等设备资源的占用。当需要用第三方模块临时录音时，可调用这个接口。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**
 
``` c++
//主要回调事件：
//YOUME_EVENT_PAUSED - 暂停语音频道完成
void  onEvent (const char* strParam);
```

### 恢复通话

* **语法**

``` c++
YouMeErrorCode resumeChannel();
```

* **功能**
恢复通话，调用PauseChannel暂停通话后，可调用这个接口恢复通话。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//主要回调事件：
//YOUME_EVENT_RESUMED - 恢复语音频道完成
void  onEvent (const char* strParam);
```

### 设置语音检测

* **语法**

``` c++
YouMeErrorCode setVadCallbackEnabled(bool enabled);
```

* **功能**
设置是否开启语音检测回调。开启后频道内有人正在讲话与结束讲话都会发起相应回调通知。

* **参数说明**
`bEnabled`:true——打开，false——关闭。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置音量回调

* **语法**

``` c++
YouMeErrorCode setMicLevelCallback(int maxLevel);
```

* **功能**
设置是否开启讲话音量回调, 并设置相应的参数

* **参数说明**
`maxLevel`:音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数。比如你只在UI上呈现10级的音量变化，那就设10就可以了。设 0 表示关闭回调。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 远端音量回调

* **语法**
 
``` c++
YouMeErrorCode setFarendVoiceLevelCallback(int maxLevel);
```

* **功能**
设置是否开启远端语音音量回调, 并设置相应的参数

* **参数说明**
`maxLevel`:音量最大时对应的级别，最大可设100。根据实际需要设置小于100的值可以减少回调的次数。比如你只在UI上呈现10级的音量变化，那就设10就可以了。设 0 表示关闭回调。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


### 设置释放麦克风

* **语法**

``` c++
YouMeErrorCode setReleaseMicWhenMute(bool enabled);
```

* **功能**
设置当麦克风静音时，是否释放麦克风设备，在初始化之后、加入房间之前调用

* **参数说明**
`enabled`:true 当麦克风静音时，释放麦克风设备，此时允许第三方模块使用麦克风设备录音。在Android上，语音通过媒体音轨，而不是通话音轨输出。
false 不管麦克风是否静音，麦克风设备都会被占用。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置插入耳机时，是否自动退出系统通话模式

* **语法**
``` c++
YouMeErrorCode setExitCommModeWhenHeadsetPlugin(bool enabled);
```

* **功能**
设置插入耳机时，是否自动退出系统通话模式(禁用手机硬件提供的回声消除等信号前处理)
系统提供的前处理效果包括回声消除、自动增益等，有助于抑制背景音乐等回声噪音，减少系统资源消耗
由于插入耳机可从物理上阻断回声产生，故可设置禁用该效果以保留背景音乐的原生音质效果
注：Windows和macOS不支持该接口

* **参数说明**
`enabled`： true--当插入耳机时，自动禁用系统硬件信号前处理，拔出时还原；false--插拔耳机不做处理。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 播放背景音乐

* **语法**

``` c++
YouMeErrorCode playBackgroundMusic (const char* pFilePath, bool bRepeat);
```

* **功能**
播放指定的音乐文件。播放的音乐将会通过扬声器输出，并和语音混合后发送给接收方。这个功能适合于主播/指挥等使用。

* **参数说明**
`pFilePath`：音乐文件的路径。
`bRepeat`：是否重复播放，true——重复播放，false——只播放一次就停止播放。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **异步回调**

``` c++
//主要回调事件：
//YOUME_EVENT_BGM_STOPPED - 通知背景音乐播放结束
//YOUME_EVENT_BGM_FAILED - 通知背景音乐播放失败
void  onEvent(const char* strParam);
```

### 停止播放背景音乐

* **语法**

``` c++
YouMeErrorCode stopBackgroundMusic();
```

* **功能**
停止播放当前正在播放的背景音乐。
这是一个同步调用接口，函数返回时，音乐播放也就停止了。

* **返回值**
如果成功返回YOUME_SUCCESS，表明成功停止了音乐播放流程；否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


### 暂停播放背景音乐

* **语法**

``` c++
YouMeErrorCode pauseBackgroundMusic();
```

* **功能**
如果当前正在播放背景音乐的话，暂停播放

* **返回值**
返回YOUME_SUCCESS表明请求成功，其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


### 恢复播放背景音乐

* **语法**

``` c++
YouMeErrorCode resumeBackgroundMusic();
```

* **功能**
如果当前正在播放背景音乐的话，恢复播放

* **返回值**
返回YOUME_SUCCESS表明请求成功，其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


### 背景音乐是否在播放

* **语法**

``` c++
bool isBackgroundMusicPlaying();
```

* **功能**
是否在播放背景音乐

* **返回值**
true——正在播放，false——没有播放


### 设置背景音乐播放音量

* **语法**

``` c++
YouMeErrorCode setBackgroundMusicVolume(int vol);
```

* **功能**
设定背景音乐的音量。这个接口用于调整背景音乐和语音之间的相对音量，使得背景音乐和语音混合听起来协调。
这是一个同步调用接口。

* **参数说明**
`vol`:背景音乐的音量，范围 [0-100]。

* **返回值**
如果成功（表明成功设置了背景音乐的音量）返回YOUME_SUCCESS，否则返回错误码，具体请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置监听

* **语法**

``` c++
YouMeErrorCode setHeadsetMonitorOn(bool micEnabled, bool bgmEnabled = true);
```

* **功能**
设置是否用耳机监听自己的声音，当不插耳机或外部输入模式时，这个设置不起作用
这是一个同步调用接口。

* **参数说明**
`micEnabled`:是否监听麦克风 true 监听，false 不监听。
`bgmEnabled`:是否监听背景音乐 true 监听，false 不监听。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置混响音效

* **语法**

``` c++
YouMeErrorCode setReverbEnabled(bool enabled);
```

* **功能**
设置是否开启混响音效，这个主要对主播/指挥有用。

* **参数说明**
`bEnabled`:true——打开，false——关闭。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


### 设置录音时间戳

* **语法**

``` c++
void setRecordingTimeMs(unsigned int timeMs);
```

* **功能**
设置当前录音的时间戳。当通过录游戏脚本进行直播时，要保证观众端音画同步，在主播端需要进行时间对齐。
这个接口设置的就是当前游戏画面录制已经进行到哪个时间点了。

* **参数说明**
`timeMs`:当前游戏画面对应的时间点，单位为毫秒。

* **返回值**
无。

### 设置PCM数据回调对象

* **语法**

``` c++
YouMeErrorCode setPcmCallback(IYouMePcmCallback* pcmCallback);
```

* **功能**
设置PCM数据回调对象

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置成员变化回调对象

* **语法**

``` c++
void setMemberChangeCallback(IYouMeMemberChangeCallback* cb);
```

* **功能**
getChannelUserList的回调消息

* **返回值**
无

### 设置频道内的广播消息回调

* **语法**

``` c++
void setNotifyCallback(IYouMeChannelMsgCallback* cb);
```

* **功能**
设置频道内的广播消息回调

* **返回值**
无

### 获取SDK版本号

* **语法**

``` c++
int getSDKVersion();
```

* **功能**
获取SDK版本号

* **返回值**
整形数字版本号

### 抢麦相关设置

* **语法**

``` c++
YouMeErrorCode setGrabMicOption(const char* pChannelID, int mode, int maxAllowCount, int maxTalkTime, unsigned int voteTime);
```

* **功能**
抢麦相关设置（抢麦活动发起前调用此接口进行设置）

* **参数说明**
`pChannelID`：抢麦活动的频道id
`mode`：抢麦模式（1:先到先得模式；2:按权重分配模式）
`maxAllowCount`：允许能抢到麦的最大人数
`maxTalkTime`：允许抢到麦后使用麦的最大时间（秒）
`voteTime`：抢麦仲裁时间（秒），过了X秒后服务器将进行仲裁谁最终获得麦（仅在按权重分配模式下有效）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 发起抢麦活动

* **语法**

``` c++
YouMeErrorCode startGrabMicAction(const char* pChannelID, const char* pContent);
```

* **功能**
抢麦相关设置（抢麦活动发起前调用此接口进行设置）

* **参数说明**
`pChannelID`：抢麦活动的频道id
`pContent`：游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 停止抢麦活动

* **语法**

``` c++
YouMeErrorCode stopGrabMicAction(const char* pChannelID, const char* pContent);
```

* **功能**
停止抢麦活动

* **参数说明**
`pChannelID`：抢麦活动的频道id
`pContent`：游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 发起抢麦请求

* **语法**

``` c++
YouMeErrorCode requestGrabMic(const char* pChannelID, int score, bool isAutoOpenMic, const char* pContent);
```

* **功能**
停止抢麦活动

* **参数说明**
`pChannelID`：抢麦的频道id
`score`：积分（权重分配模式下有效，游戏根据自己实际情况设置）
`isAutoOpenMic`：抢麦成功后是否自动开启麦克风权限
`pContent`：游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 释放抢到的麦

* **语法**

``` c++
YouMeErrorCode releaseGrabMic(const char* pChannelID);
```

* **功能**
释放抢到的麦

* **参数说明**
`pChannelID`：抢麦的频道id

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 连麦相关设置

* **语法**

``` c++
YouMeErrorCode setInviteMicOption(const char* pChannelID, int waitTimeout, int maxTalkTime);
```

* **功能**
连麦相关设置（角色是频道的管理者或者主播时调用此接口进行频道内的连麦设置）

* **参数说明**
`pChannelID`：连麦的频道id
`waitTimeout`：等待对方响应超时时间（秒）
`maxTalkTime`：最大通话时间（秒）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 发起连麦请求

* **语法**

``` c++
YouMeErrorCode requestInviteMic(const char* pChannelID, const char* pUserID, const char* pContent);
```

* **功能**
发起与某人的连麦请求（主动呼叫）

* **参数说明**
`pUserID`：被叫方的用户id
`pContent`：游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 回应连麦请求

* **语法**

``` c++
YouMeErrorCode responseInviteMic(const char* pUserID, bool isAccept, const char* pContent);
```

* **功能**
对连麦请求做出回应（被动应答）

* **参数说明**
`pUserID`：主叫方的用户id
`isAccept`：是否同意连麦
`pContent`：游戏传入的上下文内容，通知回调会传回此内容（目前只支持纯文本格式）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 停止连麦

* **语法**

``` c++
YouMeErrorCode stopInviteMic();
```

* **功能**
停止连麦

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 向房间广播消息

* **语法**

``` c++
 YouMeErrorCode sendMessage( const char* pChannelID,  const char* pContent, int* requestID );
```

* **功能**
向房间广播消息

* **参数说明**
`pChannelID`:广播房间
`pContent`:广播内容-文本串
`requestID`:返回消息标识，回调的时候会回传该值

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置是否由外部输入音视频

* **语法**

``` c++
 void setExternalInputMode( bool bInputModeEnabled );
```

* **功能**
设置是否由外部输入音视频

* **参数说明**
`bInputModeEnabled`:true:外部输入模式，false:SDK内部采集模式

* **返回值**
无。

### 设置外部输入模式的语音采样率

* **语法**

``` c++
 YouMeErrorCode setExternalInputSampleRate( YOUME_SAMPLE_RATE inputSampleRate, YOUME_SAMPLE_RATE mixedCallbackSampleRate );
```

* **功能**
设置外部输入模式的语音采样率

* **参数说明**
`inputSampleRate`:输入语音采样率, 具体参考 YOUME_SAMPLE_RATE类型定义
`mixedCallbackSampleRate`:mix后输出语音采样率, 具体参考 YOUME_SAMPLE_RATE类型定义

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置视频网络传输分辨率

* **语法**

``` c++
 YouMeErrorCode setVideoNetResolution(  int width, int height  );
```

* **功能**
设置视频网络传输过程的分辨率,高分辨率

* **参数说明**
`width`:宽
`height`:高

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置视频网络传输低分辨率(小流分辨率)

* **语法**

``` c++
 YouMeErrorCode setVideoNetResolutionForSecond(  int width, int height  );
```

* **功能**
设置视频网络传输过程的分辨率，低分辨率

* **参数说明**
`width`:宽
`height`:高

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置视频编码是否采用VBR动态码率方式

* **语法**

``` c++
 YouMeErrorCode setVBR( bool useVBR );
```

* **功能**
设置视频编码是否采用VBR动态码率方式，需要在进房间之前设置

* **参数说明**
`useVBR`: 默认为false，true表示使用VBR模式，允许码率在约1.5倍范围内波动

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置小流视频编码是否采用VBR动态码率方式

* **语法**

``` c++
 YouMeErrorCode setVBRForSecond( bool useVBR );
```

* **功能**
设置视频编码是否采用VBR动态码率方式，需要在进房间之前设置

* **参数说明**
`useVBR`: 默认为false，true表示使用VBR模式，允许码率在约1.5倍范围内波动

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置视频网络传大小流调整方式

* **语法**

``` c++
 YouMeErrorCode setVideoNetAdjustmode( int mode );
```

* **功能**
设置视频网络传大小流自动调整，需要在进房间之前设置

* **参数说明**
`mode`: 0: 自动调整；1: 上层设置大小流接收选择

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置和流画布大小

* **语法**

``` c++
 void setMixVideoSize(  int width, int height  );
```

* **功能**
设置和流画布大小（不设置则默认为采集视频分辨率）

* **参数说明**
`width`:宽
`height`:高

* **返回值**
无。

### 设置具体的user的视频数据在合流画面中展现的位置和尺寸

* **语法**

``` c++
 void addMixOverlayVideo(  std::string userId, int x, int y, int z, int width, int height  );
```

* **功能**
设置具体的user的视频数据在合流画面中展现的位置和尺寸。

* **参数说明**
`x`:x
`y`:y
`z`:z,z值小的在前面
`width`:宽
`height`:高

* **返回值**
无。

### 移除单个合流画面

* **语法**

``` c++
 void removeMixOverlayVideo(  std::string userId  );
```

* **功能**
移除单个合流画面

* **参数说明**
`userId`:用户id

* **返回值**
无。

### 清除所有合流信息

* **语法**

``` c++
 void removeAllOverlayVideo();
```

* **功能**
清除所有合流信息

* **返回值**
无。


### 设置本地视频镜像模式

* **语法**

``` c++
void setLocalVideoMirrorMode( YouMeVideoMirrorMode mode );
```

* **参数**
`mode`:镜像模式，参见YouMeVideoMirrorMode类型

* **返回值**
无。

### 设置音视频统计数据时间间隔

* **语法**

``` c++
 void setAVStatisticInterval(  int interval  );
```

* **功能**
设置音视频统计数据时间间隔，SDK将按该间隔回调 `onAVStatistic` 回调

* **参数说明**
`interval`: 时间间隔，单位毫秒

* **返回值**
无。

### 设置音视频统计数据回调接口

* **语法**

``` c++
 void setAVStatisticCallback(  IYouMeAVStatisticCallback* cb  );
```

* **功能**
设置Audio,Video的统计数据的回调接口

* **参数说明**
`cb`:需要继承IYouMeAVStatisticCallback并实现其中的回调函数

* **返回值**
无。

### 设置Audio传输质量

* **语法**

``` c++
 void setAudioQuality(  YOUME_AUDIO_QUALITY quality  );
```

* **功能**
设置Audio的传输质量

* **参数说明**
`quality`:0: low 1: high

* **返回值**
无。

### 设置是否开启视频编码器

* **语法**

``` c++
 YouMeErrorCode openVideoEncoder( const char* pFilePath );
```

* **功能**
设置是否开启视频编码器

* **参数说明**
`pFilePath`:yuv文件的绝对路径

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

### 设置播放时间戳

* **语法**

``` c++
 void setPlayingTimeMs(unsigned int timeMs);
```

* **功能**
设置当前声音播放的时间戳。当通过录游戏脚本进行直播时，要保证观众端音画同步，游戏画面的播放需要和声音播放进行时间对齐。
这个接口设置的就是当前游戏画面播放已经进行到哪个时间点了。

* **参数说明**
`timeMs`:当前游戏画面播放对应的时间点，单位为毫秒。

* **返回值**
无。


### 设置服务器区域

* **语法**
 
``` c++
void setServerRegion(YOUME_RTC_SERVER_REGION regionId, const char* strExtRegionName);
```

* **功能**
设置首选连接服务器的区域码.

* **参数说明**
`serverRegionId`：如果YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。
`strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。


### 设置服务器区域（全）

* **语法**

``` c++
void setServerRegion(const char*[] regionNames);
```

* **功能**
设置参与通话各方所在的区域,这个接口适合于分布区域比较广的应用。最简单的做法是只设定前用户所在区域。但如果能确定其他参与通话的应用所在的区域，则能使服务器选择更优。

* **参数说明**
`regionNames`：指定参与通话各方区域的数组，数组里每个元素为一个区域代码。用户可以自行定义代表各区域的字符串（如中国用 "cn" 或者 “ch"表示），然后把定义好的区域表同步给游密，游密会把这些定义配置到后台，在实际运营时选择最优服务器。


###  RestApi——支持主播相关信息查询

* **语法**

``` c++
YouMeErrorCode  requestRestApi( const std::string& strCommand , const std::string& strQueryBody , int* requestID = NULL  );
```
* **功能**
Rest API , 向服务器请求额外数据。支持主播信息，主播排班等功能查询。详情参看文档<RequestRestAPI接口说明>


* **参数说明**
`strCommand`：请求的命令字符串，标识命令类型。
`strQueryBody`：请求需要的参数,json格式。
`requestID`：回传id,回调的时候传回，标识消息。不关心可以填NULL。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **设置回调**

``` c++
void setRestApiCallback(IRestApiCallback* cb );
```

* **异步回调**
``` c++
//IRestApiCallback
//requestID:回传ID
//iErrorCode:错误码
//strQuery:回传查询请求，json格式
//strResult:查询结果，json格式
void onRequestRestAPI( int requestID, const YouMeErrorCode &iErrorCode, const std::string& strQuery, const std::string&  strResult )
```


###  安全验证码设置

* **语法**

``` c++
 void setToken( const char* pToken );
```

* **功能**
设置身份验证的token，需要配合后台接口。

* **参数说明**
`pToken`：身份验证用token，设置为NULL或者空字符串，清空token值，不进行身份验证。

###  查询频道用户列表

* **语法**

``` c++
YouMeErrorCode getChannelUserList( const char*  channelID, int maxCount, bool notifyMemChange );
```

* **功能**
查询频道当前的用户列表， 并设置是否获取频道用户进出的通知。（必须自己在频道中）


* **参数说明**
`channelID`：频道ID。
`maxCount`：想要获取的最大人数。-1表示获取全部列表。
`notifyMemChange`：当有人进出频道时，是否获得通知。

* **返回值**
返回YOUME_SUCCESS才会有异步回调通知。其它返回值请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **设置回调**

``` c++
void setMemberChangeCallback( IYouMeMemberChangeCallback* cb );
```

* **异步回调**

``` c++
//IYouMeMemberChangeCallback

// 同时支持std::list 和 const char* json string格式回调
//channel:频道ID
//listMemberChange:查询获得的用户列表，或变更列表。
//isUpdate: 是否是增量通知，刚进入频道会收到一次全量通知，为false，之后成员发生变化属于增量通知，为true
void onMemberChange( const std::string& channel, std::list<MemberChange>& listMemberChange, bool bUpdate)
void onMemberChange( const char* channel, const char* listMemberChangeJson, bool bUpdate )
```


## 视频相关接口
视频的频道属性和语音是绑定的，可以单独控制是否开启/关闭音视频流。**以下接口的调用，必须是在进入频道之后。**

###  创建视频渲染

* **语法**

``` c++
int createRender(const char * userId);
```

* **功能**
根据用户ID创建渲染ID

* **参数说明**
`userId`：用户ID

* **返回值**
大于等于0时，为渲染ID；小于0则为错误码，具体的错误码请参考[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  删除视频渲染

* **语法**

``` c++
int deleteRender(int renderId);
```

* **功能**
删除之前创建的渲染ID

* **参数说明**
`renderId`：渲染ID

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置视频流回调

* **语法**

``` c++
YouMeErrorCode setVideoCallback(IYouMeVideoCallback * cb);
```

* **功能**
设置视频流的异步回调函数

* **返回值**
返回YOUME_SUCCESS

* **异步回调**
```
//IYouMeVideoCallback
```

``` c++
void frameRender(int renderId, int nWidth, int nHeight, int nRotationDegree, int nBufSize, const void * buf)
// 注意事项：
// 返回的视频流是YUV格式，需转换成RGB/RGBA格式，才能使用
// 参数说明：
//renderId:createRender返回的渲染ID;
//nWidth:视频流的宽;
//nHeight:视频流的高;
//nRotationDegree:视频流的旋转角度;
//nBufSize:视频流的数据大小;
//buf:视频流的数据地址
```

###  开始捕获本机摄像头数据

* **语法**

``` c++
YouMeErrorCode startCapture();
```

* **功能**
捕获本机摄像头数据，以便发送给房间内其他人

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  停止捕获本机摄像头数据

* **语法**

``` c++
YouMeErrorCode stopCapture();
```

* **功能**
停止捕获本机摄像头数据（比如退出房间、程序切换到后台时）

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  踢出房间

* **语法**

``` c++
YouMeErrorCode kickOtherFromChannel(const char* pUserID, const char* pChannelID , int lastTime);
```

* **功能**
把某人踢出房间

* **参数说明**
`pUserID`被踢的用户ID
`pChannelID`:从哪个房间踢出
`lastTime`:踢出后，多长时间内不允许再次进入

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置日志等级

* **语法**

``` c++
void setLogLevel(YOUME_LOG_LEVEL consoleLevel, YOUME_LOG_LEVEL fileLevel);
```

* **功能**
设置日志等级

* **参数说明**
`consoleLevel`:控制台日志等级
`fileLevel`:文件日志等级

* **返回值**
无。

###  设置用户自定义Log路径

* **语法**

``` c++
YouMeErrorCode setUserLogPath(const char* pFilePath);
```

* **功能**
设置用户自定义Log路径

* **参数说明**
`pFilePath`:Log文件的路径

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置是否使用TCP

* **语法**

``` c++
YouMeErrorCode setTCPMode(int iUseTCP);
```

* **功能**
设置是否使用TCP传输语音视频数据，必须在进入房间之前调用

* **参数说明**
`iUseTCP`:默认情况下使用UDP，在某些UDP被禁用的网络可以切换成TCP，但是TCP模式下延迟等将不可控，除非必要，不要调用

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  屏蔽/恢复他人视频

* **语法**

``` c++
YouMeErrorCode maskVideoByUserId(const char * userId, bool mask);
```

* **功能**
屏蔽他人视频（屏蔽后恢复他人视频也是调用此函数）

* **参数说明**
`userId`：要屏蔽的用户ID
`mask`:true是要屏蔽，false是要取消屏蔽

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  设置硬件编解码

* **语法**

``` c++
void setVideoHardwareCodeEnable( bool bEnable );
```

* **功能**
设置视频数据是否同意开启硬编硬解
（实际是否开启硬解，还跟服务器配置及硬件是否支持有关，要全部支持开启才会使用硬解。并且如果硬编硬解失败，也会切换回软解。）
（需要在进房间之前设置）

* **参数说明**
`bEnable`: true:开启，false:不开启

    
###  获取硬件编解码开启状态

* **语法**

``` c++
bool getVideoHardwareCodeEnable( );
```

* **功能**
获取视频数据是否开启硬编硬解标识

* **返回值**
true:开启，false:不开启， 默认为true;


###  设置视频超时时间

* **语法**

``` c++
void setVideoNoFrameTimeout(int timeout);
```

* **功能**
设置视频无帧渲染的等待超时时间，超过这个时间会给上层回调

* **参数说明**
`timeout`: 超时时间，单位为毫秒

* **异步回调**

``` c++
//主要回调事件：
//YOUME_EVENT_MEDIA_DATA_ROAD_BLOCK - 音视频数据通路不通
void  onEvent(const char* strParam);
```

###  查询多个用户视频信息

* **语法**

``` c++
YouMeErrorCode queryUsersVideoInfo(std::vector<std::string>& userList);
```

* **功能**
查询多个用户视频信息（支持分辨率）

* **参数说明**
`userList`: 用户ID列表

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  设置多个用户视频信息（支持分辨率）

* **语法**

``` c++
YouMeErrorCode setUsersVideoInfo(std::vector<IYouMeVoiceEngine::userVideoInfo>& videoInfoList);
```

* **功能**
设置多个用户视频信息（支持分辨率）

* **参数说明**
`videoinfoList`: 用户对应分辨率列表
`userVideoInfo`: struct userVideoInfo包含std::string userId（用户id）;int resolutionType（支持分辨率）;

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置帧率

* **语法**

``` c++
YouMeErrorCode setVideoFps(int fps);
```

* **功能**
设置帧率

* **参数说明**
`fps`:帧率（1-30），默认15帧

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  设置本地视频的分辨率

* **语法**

``` c++
YouMeErrorCode setVideoLocalResolution(int width, int height);
```

* **功能**
设置本地视频渲染回调的分辨率

* **参数说明**
`width`:视频宽度
`height`:视频高度

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置是否前置摄像头

* **语法**

``` c++
YouMeErrorCode setCaptureFrontCameraEnable(bool enable);
```

* **功能**
设置是否前置摄像头

* **参数说明**
`enable`:true 前置 false 非前置

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置视频码率的上下限

* **语法**

``` c++
void setVideoCodeBitrate( unsigned int maxBitrate,  unsigned int minBitrate );
```

* **功能**
设置视频数据上行的码率的上下限。

* **参数说明**
`maxBitrate`:最大码率，单位kbps.  0：使用默认值
`minBitrate`:最小码率，单位kbps.  0：使用默认值

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

###  设置视频数据上行的码率的上下限,第二路(默认不传)

* **语法**

``` c++
void setVideoCodeBitrateForSecond( unsigned int maxBitrate,  unsigned int minBitrate );
```

* **功能**
设置视频数据上行的码率的上下限,第二路(默认不传)

* **参数说明**
`maxBitrate`:最大码率，单位kbps.  0：使用默认值
`minBitrate`:最小码率，单位kbps.  0：使用默认值

* **返回值**
无。

###  获取视频当前码率

* **语法**

``` c++
unsigned int getCurrentVideoCodeBitrate( );
```

* **功能**
获取视频数据上行的当前码率。

* **返回值**
码率值，单位kbps


###  美颜开关

* **语法**

``` c++
YouMeErrorCode openBeautify(bool open) ;
```

* **功能**
美颜开关，默认是关闭美颜

* **参数说明**
`open`:true表示开启美颜，false表示关闭美颜

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  设置美颜参数

* **语法**

``` c++
YouMeErrorCode beautifyChanged(float param) ;
```

* **功能**
美颜强度参数设置

* **参数说明**
`param`:美颜参数，0.0 - 1.0 ，默认为0，几乎没有美颜效果，0.5左右效果明显

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。
    

###  瘦脸开关

* **语法**

``` c++
YouMeErrorCode stretchFace(bool stretch) ;
```

* **功能**
瘦脸开关，默认关闭

* **参数说明**
`stretch`:true 开启瘦脸，false关闭，默认 false

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  麦克风释放

* **语法**

``` c++
bool releaseMicSync() ;
```

* **功能**
调用后同步完成麦克风释放

* **参数说明**
无

* **返回值**
如果成功则返回true

###  麦克风恢复

* **语法**

``` c++
bool resumeMicSync() ;
```

* **功能**
调用后恢复麦克风到释放前的状态

* **参数说明**
无

* **返回值**
如果成功则返回true


###  获取摄像头数量个数

* **语法**

``` c++
int getCameraCount();
```

* **功能**
获取windwos平台摄像头个数。

* **参数说明**
无

* **返回值**
返回摄像头个数，摄像头id为0-count。

###   获取摄像名称

* **语法**

``` c++
bool getCameraName(int cameraId, char* name, int nameLen);
```

* **功能**
获取windows平台cameraid 对应名称。

* **参数说明**
`cameraId`:摄像头id
`name`:摄像头名称返回buffer
`nameLen`:buffer长度

* **返回值**
如果返回true表示成功，false失败。

###  设置打开摄像头id

* **语法**

``` c++
void setOpenCameraId(int cameraId);
```

* **功能**
设置windows平台打开摄像头id。

* **参数说明**
`cameraId`:摄像头id

* **返回值**
void

### 设置预览视频镜像开关
* **语法**

``` c++
void setLocalVideoPreviewMirror( bool enable );
```

* **参数说明**
    `enable`: 预览是否开启镜像功能

###  获取windwos/macos平台，audio采集设备数量

* **语法**

``` c++
int getRecordDeviceCount();
```

* **功能**
获取windwos/macos平台，audio采集设备数量

* **返回值**
audio采集设备数量

###  获取windows/macos平台 record设备 对应信息

* **语法**

``` c++
bool getRecordDeviceInfo(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceUId[MAX_DEVICE_ID_LENGTH]);
```

* **功能**
获取windows/macos平台 record设备 对应信息

* **参数说明**
`index`:列表中的位置
`deviceName`:设备名称
`deviceUid`:设备唯一ID，用于设置设备

* **返回值**
true - 成功:非空name; false - 失败:空字符串

###  设置windows/macos平台打开record设备id

* **语法**

``` c++
YouMeErrorCode setRecordDevice( const char* deviceUId);
```

* **功能**
设置windows/macos平台打开record设备id

* **参数说明**
`deviceUId`: record设备的Uid

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

### 自定义数据类型

#### 数据回调

* **设置回调**

``` c++
void setRecvCustomDataCallback(IYouMeCustomDataCallback* pCallback);
```

* **异步回调**
```
//IYouMeCustomDataCallback
```

``` c++
void OnCustomDataNotify(const void* pData, int iDataLen, unsigned long long ulTimeSpan)
```

``` c++
//pData:自定义数据
//iDataLen:数据长度
//ulTimeSpan:时间戳
```

#### 输入用户自定义数据

* **语法**

``` c++
YouMeErrorCode inputCustomData(const void* data, int len, uint64_t timestamp);
```

* **参数说明**
    `data`: 自定义数据，要广播的自定义数据
    `len`: 数据长度，不能大于1024
    `timestamp`: 时间戳

### 其他操作
#### 屏蔽他人视频

* **语法**

``` c++
YouMeErrorCode maskVideoByUserId(const char * userId, bool mask);
```

* **参数说明**
    `userId`: 用户ID
    `mask`: true - 屏蔽, false - 恢复不屏蔽

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 开启服务器推流

* **语法**

``` c++
YouMeErrorCode startPush( std::string pushUrl );
```

* **功能**
开启服务器推流，推送自己的数据

* **参数说明**
	`pushUrl`: 推流地址，可以用restApi获取

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 关闭服务器推流

* **语法**

``` c++
YouMeErrorCode stopPush();
```

* **功能**
关闭服务器推流，对应startPush

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 开启服务器混流推流

* **语法**

``` c++
YouMeErrorCode setPushMix( std::string pushUrl , int width, int height );
```

* **功能**
开启服务器混流推流，将多个人的画面混到一起，对混流画面就行推流。每个房间只允许一个混流推流。开启服务器混流推流后，可以通过addPushMixUser/removePushMixUser改变推流的画面。

* **参数说明**
	`pushUrl`: 推流地址，可以用restApi获取
	`width`: 推流的画面的宽
	`height`: 推流的画面的高

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 关闭服务器混流推流

* **语法**

``` c++
YouMeErrorCode clearPushMix();
```

* **功能**
关闭服务器混流推流，对应setPushMix

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 在服务器混流推流中，加入一个user的数据

* **语法**

``` c++
YouMeErrorCode addPushMixUser( std::string userId, int x, int y, int z, int width, int height );
```

* **功能**
在服务器混流推流中，加入一个user的数据

* **参数说明**
	`userId`: 推流地址，可以用restApi获取
	`x`: 用户画面在混流画面中的位置，x
	`y`: 用户画面在混流画面中的位置，y
	`z`: 用户画面在混流画面中的位置，z
	`width`: 用户画面在混流画面中的宽
	`height`: 用户画面在混流画面中的高

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 

#### 删除混流推流中的一个用户

* **语法**

``` c++
YouMeErrorCode removePushMixUser( std::string userId );
```

* **功能**
删除混流推流中的一个用户

* **参数说明**
	`userId`: 推流地址，可以用restApi获取
	`x`: 用户画面在混流画面中的位置，x
	`y`: 用户画面在混流画面中的位置，y
	`z`: 用户画面在混流画面中的位置，z
	`width`: 用户画面在混流画面中的宽
	`height`: 用户画面在混流画面中的高

* **返回值**

    错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码 
    
    ### 会议纪要功能

* **语法**

```c++
YouMeErrorCode setTranscriberEnabled(bool enable, IYouMeTranscriberCallback* transcriberCallback );
```

* **功能**
设置开启或者关闭会议纪要功能。会议纪要功能，是指在通话过程中，自动将每个人的语音识别为文字。可在进入房间前，或者进入房间后设置。

* **参数说明**
`enable`:true 开启，false关闭，默认 false。
`transcriberCallback`: 识别出的文字的回调接口。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **回调**

```c++
//语句的开始
//userid:说话人
//sentenceIndex:语句的序号
	virtual void onSentenceBegin( std::string userid , int sentenceIndex) = 0 ;
//语句识别结果的改变，用于实时显示当前的识别结果（一句话，随着说的字越来越多，长度会增加，原来识别的结果也可能改变）。
//userid:说话人
//sentenceIndex:语句的序号
//result：语句的当前识别结果
	virtual void onSentenceEnd(std::string userid,  int sentenceIndex, std::string result) = 0;
//语句的最终识别结果，如果不需要实时的变更说话内容，可以只关注这个回调
//userid:说话人
//sentenceIndex:语句的序号
//result:语句的当前识别结果
	virtual void onSentenceChanged(std::string userid,  int sentenceIndex, std::string result) = 0;
```

### 翻译
调用本接口前，需要先设置翻译的回调`setTranslateCallback`。

* **语法**

```c++
YouMeErrorCode translateText(unsigned int* requestID, const char* text, YouMeLanguageCode destLangCode, YouMeLanguageCode srcLangCode);
```

* **功能**
翻译一段文字为指定语言。

* **参数说明**
`requestID`: 翻译请求的ID，传出参数，用于在回调中确定翻译结果是对应哪次请求。
`text`: 要翻译的内容。
`destLangCode`:要翻译成什么语言。
`srcLangCode`:要翻译的是什么语言。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。

* **回调**

```c++
//errorcode：错误码
//requestID：请求ID（与translateText接口输出参数requestID一致）
//text：翻译结果
//srcLangCode：源语言编码
//destLangCode：目标语言编码
virtual void onTranslateTextComplete(YouMeErrorCode errorcode, unsigned int requestID, const std::string& text, YouMeLanguageCode srcLangCode, YouMeLanguageCode destLangCode) = 0 ;
```

### 设置翻译的回调
* **语法**

```c++
void setTranslateCallback( IYouMeTranslateCallback* pCallback );
```

* **功能**
设置翻译的回调实例。

* **参数说明**
`pCallback`: 翻译请求的ID，传出参数，用于在回调中确定翻译结果是对应哪次请求。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


###  反初始化

* **语法**

``` c++
YouMeErrorCode unInit ();
```

* **功能**
反初始化引擎，可在退出游戏时调用，以释放SDK所有资源。

* **返回值**
如果成功则返回YOUME_SUCCESS，其它具体参见[YouMeErrorCode类型定义](/doc/TalkStatusCode.html#youmeerrorcode类型定义)。


## 屏幕共享相关接口
屏幕共享功能必须实在进入房间之后才可以打开，但是屏幕共享的参数设置可以在进入房间之前设置；屏幕共享和摄像头是分离的，可以单独打开视频共享。

### 获取窗口列表
* **语法**

``` c++
void GetWindowInfoList(HWND *pHwnd, char *pWinName, int *winCount);
```

* **功能**
获取当前窗口列表信息(包括窗口名称和窗口句柄)，主要用于在窗口共享模式下给用户选择窗口句柄并在共享视频参数设置接口设置给SDK

* **参数说明**
	`pHwnd`: 窗口句柄列表，和窗口名称列表一一对应
	`pWinName`: 窗口名称列表，和窗口句柄列表一一对应
	`winCount`: 获取到的窗口数量

* **返回值**
	无


### 设置共享视频模式和参数

* **语法**

``` c++
YouMeErrorCode SetShareParameter(int mode, HWND renderHandle, HWND captureHandle);
```

* **功能**
设置共享视频相关参数：包括共享视频采集源，预览窗口句柄，待采集窗口句柄(出口录制模式必选)

* **参数说明**
	`mode`: 共享视频采集模式  2：采集指定窗口; 3：采集桌面; 其他值非法
	`renderHandle`: 共享视频preview窗口句柄，必选
	`captureHandle`: 指定需要采集的窗口句柄，采集桌面则可以设置为NULL

* **返回值**
	错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码


### 开始共享

* **语法**

``` c++
YouMeErrorCode StartShareStream();
```

* **功能**
开始视频共享，并将(屏幕/窗口)共享视频流实时发送到房间内其他人；注意在一个房间内，同时只能有一个人共享视频

* **参数说明**
	无

* **返回值**
	错误码，YOUME_SUCCESS - 表示成功,其他 - 具体错误码

### 结束共享

* **语法**

``` c++
void StopShareStream();
```
* **功能**
结束视频共享，停止发送(屏幕/窗口)共享视频流

* **参数说明**
	无

* **返回值**
	无

