# Video SDK for win32 典型场景实现方法

## 实现视频通话(内部采集、内部渲染) ##

### 相关接口及调用顺序

#### 初始化流程
`setLogLevel` 设置日志级别
`init` 引擎初始化

#### 加入房间流程
`setVideoPreviewFps` 设置本地预览帧率，设置本地预览帧率，建议设置为 20
`setVideoLocalResolution` 设置本地采集分辨率，建议设置为 960 * 720
`setVideoFps` 设置视频编码帧率（大流），建议设置为 10 - 15
`setVideoNetResolution` 设置网络传输分辨率（大流），建议设置，建议设置 640 * 480
`setVBR` 设置视频编码是否采用VBR动态码率（大流），建议设置为 true
`setVideoCodeBitrate` 设置视频编码码率，若不调用则采用默认设置（大流），建议设置为 600 - 160
`setVideoFpsForSecond` 设置视频帧率（小流）），建议设置为 7
`setVideoNetResolutionForSecond` 设置编码分辨率（小流），建议设置为 336 * 256 （16的整数被）
`setVBRForSecond` 设置视频编码是否采用VBR动态码率（小流），建议设置为true
`setVideoCodeBitrateForSecond` 设置视频编码码率，若不调用则采用默认设置（小流），200 - 100
`setVideoFpsForShare` 设置共享流帧率，一般共享建议设置为 10帧
`setVideoNetResolutionForShare` 设置共享流编码分辨率，建议为 720p - 1080p
`setMicLevelCallback` 设置是否开启讲话音量回调
`setFarendVoiceLevelCallback` 设置是否开启远端说话人音量回调
`setAVStatisticInterval` 设置音视频统计上报间隔
`setAutoSendStatus` 设置状态同步(mic,speaker的状态会通知给接收端)
`joinChannelSingleMode` 加入房间
`createRender` 创建渲染
`getCameraCount` 获取摄像头个数
`getCameraName` 获取摄像头名称
`setOpenCameraId` 设置打开摄像头

#### 本地设备控制接口
`startCapture` 打开摄像头采集
`stopCapture` 关闭摄像头采集
`setMicrophoneMute`	设置麦克风状态
`setSpeakerMute`	设置扬声器状态
`switchCamera` 切换摄像头

#### 接收远端音视频
`createRender` 创建渲染
`deleteRender` 删除渲染
`setUsersVideoInfo` 设置观看用户的哪一路流(大小流)，autoRecv设置为false时，需要调用该接口后才会接收对方的视频流
`maskVideoByUserId` 设置是否屏蔽他人视频，屏蔽对方的所有视频流，包括共享流，音频流保留
`setListenOtherVoice` 设置是否听其他人语音
`onMemberChange` 房间内其它用户加入/离开回调通知
`YOUME_EVENT_OTHERS_VIDEO_INPUT_START` onEvent 事件，远端开启摄像头，可用于显示摄像头状态
`YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP` onEvent 事件，远端关闭摄像头，可用于显示摄像头状态
`YOUME_EVENT_OTHERS_SHARE_INPUT_START` onEvent 事件，远端开启共享流，可用于显示共享画面
`YOUME_EVENT_OTHERS_SHARE_INPUT_STOP` onEvent 事件，远端关闭共享流，可用于移除共享画面


#### 离开房间
`leaveChannelAll` 退出所有房间

#### 反初始化
`unInit` 反初始化引擎

### 关键调用顺序
1. 初始化（init）, 等待初始化成功的通知事件`YOUME_EVENT_INIT_OK` 

2. 房间参数设置(视频参数、共享参数、QOS统计间隔等)，也可采用默认设置

3. 加入房间（joinChannelSingleMode），等待加入成功的通知事件 `YOUME_EVENT_JOIN_OK`

4. 选择并打开摄像头（startCapture），设置麦克风扬声器等设备（setMicrophoneMute，setSpeakerMute）

5. 创建本端预览，同时接收到视频数据回调事件`YOUME_EVENT_OTHERS_VIDEO_ON`，创建渲染（createRender）

6. 其它接口(开关摄像头、开关mic/speaker，屏蔽他人语音/视频)

7. 退出房间

8. 反初始化

### 设置回调 ###
Video引擎底层对于耗时操作都采用异步回调的方式，函数调用会立即返回，操作结果会同步回调。因此，用户必须实现相关接口并在初始化完成以后进行注册。

#### 新建回调类

新建一个类继承`IYouMeEventCallback`并实现其纯虚函数（回调函数）名称自定，例如YouMeEventCallback

#### 实现回调接口
实现`virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * channel, const char * param) override;` 处理各类回调事件。

``` c++
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
            //进入频道失败
            break;
        default:
            //"事件类型" + eventType + ",错误码" +
            break;
        }  
    }
```

## 实现视频直播 ##

### 相关接口

`init` 引擎初始化
`setVideoLocalResolution` 设置本地采集分辨率
`setVideoNetResolution` 设置网络传输分辨率
`joinChannelSingleMode` 加入房间
`createRender` 创建渲染
`getCameraCount` 获取摄像头个数
`getCameraName` 获取摄像头名称
`setOpenCameraId` 设置打开摄像头
`startCapture` 开始摄像头采集
`setMicrophoneMute` 设置麦克风状态
`setSpeakerMute`    设置扬声器状态
`setHeadsetMonitorOn` 设置监听
`setBackgroundMusicVolume`  设置背景音乐播放音量
`playBackgroundMusic`   播放背景音乐

### 关键调用顺序
1. 以主播身份进入频道 初始化（init）->joinChannelSingleMode(参数三传主播身份YOUME_USER_HOST), 观众传的身份可以是听众 也可以是自由人（住进自由人进入频道 需要关闭麦克风）

2. 主播打开摄像头，麦克风等设备

3. 设置监听 setHeadsetMonitorOn（true,true）参数1表示是否监听麦克风 true表示监听,false表示不监听 ,参数2表示是否监听背景音乐,true表示监听,false表示不监听

4. setBackgroundMusicVolume（70）调节背景音量大小

5. playBackgroundMusic(string pFilePath, bool bRepeat) 播放本地的mp3音乐。 参数一 本地音乐路径， 参数二 是否重复播放 true重复，false不重复

6. 远端有视频流过来，会通知 `YOUME_EVENT_OTHERS_VIDEO_ON` 事件,此时调用createRender创建相关渲染。