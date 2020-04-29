#  Video SDK for win32 开发指引

## 概述
游密视频通话SDK（Video SDK）为开发者提供完整的音视频社交通话服务，开发者无需关注视频通话复杂的内部工作流程，只需调用Video SDK提供的接口，即可快速拥有多人实时视频通话的能力。

## 四步集成Video SDK
### 第一步 注册账号
在[游密官网](https://console.youme.im/user/register)注册游密账号。

### 第二步 添加游戏，获取Appkey
在控制台添加游戏，获得接入需要的Appkey、Appsecret。

### 第三步 下载Video SDK包体
[下载地址](https://www.youme.im/download.php?type=Video)

### 第四步 开发环境配置
[开发环境配置](#快速接入)



## 快速接入

### 工具准备 ###

1. 下载`YouMeVideoSDk for windows`。 也可以请我们这边的同学提供最新的SDK包。     [YouMe下载][YouMeDownload]
2. Microsoft Visual C++ 2013 或以上版本。
3. Microsoft Windows 7 或以上版本。

### SDK介绍 ###
YouMeVideoSDK for windows 包含以下内容：

1. videoDemo 包含简单的demo示例
2. SDK文件夹 包含include头文件夹,win32库文件夹,win64库文件夹


### SDK集成 ###
1. 将SDK文件夹更名为YouMeSDK（其他名称只要不冲突都可以）,拷贝到工程目录下（与.sln同级）
2. 在Visual Studio的项目-属性-配置属性-C/C++-常规中，添加附加包含目录$(ProjectDir)YouMeSDK\include;
3. 在Visual Studio的项目-属性-配置属性-链接器-常规中，添加附加库目录$(ProjectDir)YouMeSDK\win32\$(Configuration)\lib;
4. 在Visual Studio的项目-属性-配置属性-链接器-输入中，添加附加依赖项youme_voice_engine.lib;

## 实现视频通话 ##

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
            //进入语音频道失败
            break;
        default:
            //"事件类型" + eventType + ",错误码" +
            break;
        }  
    }
```

### 初始化 ###
#### 获取引擎实例
代码示例：
``` c++
       IYouMeVoiceEngine * youme = IYouMeVoiceEngine::getInstance();
```

这是一个单例类，可以调用`getInstance()`获取到实例。通过它就可以调用Video SDK的API接口。

#### 调用初始化方法
调用`init`接口，完成YouMeSDK的初始化。代码示例：
``` c++
        YouMeErrorCode init(
        IYouMeEventCallback * pEventCallback,
        const char* strAppKey,
        const char* strAPPSecret,
        YOUME_RTC_SERVER_REGION serverRegionId,
        const char* strExtServerRegionName);
```

* **参数说明**

    `pEventCallback`：通用回调类地址，需要继承IYouMeCommonCallback并实现其中的回调函数。

    `strAPPKey`：从游密申请到的 app key, 这个你们应用程序的唯一标识。

    `strAPPSecret`：对应 strAPPKey 的私钥, 这个需要妥善保存，不要暴露给其他人。

    `serverRegionId`：设置首选连接服务器的区域码，如果在初始化时不能确定区域，可以填RTC_DEFAULT_SERVER，后面确定时通过 SetServerRegion 设置。YOUME_RTC_SERVER_REGION定义的区域码不能满足要求，可以把这个参数设为 RTC_EXT_SERVER，然后通过后面的参数strExtServerRegionName 设置一个自定的区域值（如中国用 "cn" 或者 “ch"表示），然后把这个自定义的区域值同步给游密，我们将通过后台配置映射到最佳区域的服务器。

    `strExtServerRegionName`：自定义的扩展的服务器区域名。不能为null，可为空字符串“”。只有前一个参数serverRegionId设为RTC_EXT_SERVER时，此参数才有效（否则都将当空字符串“”处理）。

    示例：
``` c++
        std::string g_strKey = "XXXXXXXX";
        std::string g_strSecret = "OOOOOOOO";
        YouMeEventCallback * m_pEventCallback = new YouMeEventCallback(mHand);
        youme->setMemberChangeCallback(m_pEventCallback);
        YouMeErrorCode ret = youme->init(m_pEventCallback, g_strKey.c_str(), g_strSecret.c_str(), RTC_CN_SERVER, "cn");
```

    ret为同步返回的调用状态码，0为成功，其余为错误码。当ret为0时才会收到异步回调的通知。

#### 初始化成功回调
之前注册的`onEvent`中收到`YOUME_EVENT_INIT_OK`时就表示异步调用初始化已经成功完成，可以接着调用其他接口了。

#### 部分接口说明
对于部分接口，可在初始化之前调用。例如：

``` c++
        //设置控制台/文件日志等级
        youme->setLogLevel(LOG_VERBOSE, LOG_INFO);
        //设置是否为外部采集模式，默认是内部采集模式
        youme->setExternalInputMode(false);
        //设置音视频统计数据时间间隔
        youme->setAVStatisticInterval(5000);
```

详细接口说明参见 **API参考**


### 加入房间 ###
#### 设置相关参数
调用相关接口，完成加入房间前的准备工作
``` c++
        //设置视频帧率
        youme->setVideoFps(fps);
        //设置本地采集分辨率
        youme->setVideoLocalResolution(width, height);
        //设置网络传输分辨率
        youme->setVideoNetResolution(width, height);
        //设置音频质量
        youme->setAudioQuality(LOW_QUALITY);
        //设置扬声器取消静音
        youme->setSpeakerMute(false);
```

#### 调用加入房间接口
示例如下：
``` c++
    YouMeErrorCode joinChannelSingleMode(const char* pUserID, const char* pChannelID, YouMeUserRole_t eUserRole, bool bVideoAutoRecv = true);
```

* **参数说明**

    `strUserID`：全局唯一的用户标识，全局指在当前应用程序的范围内。

    `strChannelID`：全局唯一的频道标识，全局指在当前应用程序的范围内。

    `userRole`：用户在语音频道里面的角色，见YouMeUserRole定义。
    
    `bVideoAutoRecv`: 是否自动接收频道内其他有人的视频，true表示自动接收，如果为false，需要调用 `setUsersVideoInfo`指定接收流后才会收到对方视频

#### 加入房间成功回调
`onEvent`收到`YOUME_EVENT_JOIN_OK`表示加入房间成功，可以接着调用其他接口了。


### 渲染视频数据 ###

进入房间成功后，如果房间内有其他用户打开了摄像头，就会接收到相关视频数据及回调信息。
接收到其他用户视频流时，会接收到`YOUME_EVENT_OTHERS_VIDEO_ON`
此时调用`addrender`方法即可自动创建相关渲染。可使用map存储userid及render相关信息。代码示例如下：

``` c++
        map_render::iterator iter = m_mapRender.find(userId);
        if (iter != m_mapRender.end())
            return;

        int i = 0;
        int id = 0;
        for (; i < m_vecWinId.size(); i++){
            if (!m_vecWinId[i].use){
                id = m_vecWinId[i].winId;
                break;
            }
        }
        if (!id) return;
        HWND hWnd = GetDlgItem(id)->m_hWnd;
        if (youme->createRender(userId, hWnd))
        {
            m_mapRender.insert(std::make_pair(userId, i));
            m_vecWinId[i].use = true;
        }
```

当用户视频流断开或视频流输入停止时，会分别接收到`YOUME_EVENT_OTHERS_VIDEO_SHUT_DOWN`/`YOUME_EVENT_OTHERS_VIDEO_INPUT_STOP`回调，此时可调用`deleteRender`方法，清除相关内容。
``` c++
        map_render::iterator iter = m_mapRender.find(userId);
        if (iter != m_mapRender.end()){
        
            m_vecWinId[iter->second].use = false;
            youme->deleteRender(userId);
            m_mapRender.erase(iter);
        }
```

### 打开摄像头 ###

#### 选择摄像头

借助`getCameraCount`方法获取PC端摄像头数量，利用`getCameraName(cameraID)`获取对应的摄像头名称。调用`setOpenCameraId(cameraID)`接口设置将要使用的摄像头设备。示例代码使用`selector`存储摄像头信息，以供用户选择。
``` c++
        int count = youme->getCameraCount();
        for (int i = 0; i < count; i++){
            std::string strName = youme->getCameraName(i);
            CString wsName;
            charTowchar(strName, wsName);
            m_CameraComboBox.InsertString(i, wsName);
        }
        if (count)
            m_CameraComboBox.SetCurSel(0);
```

#### 开始摄像头采集

确认所选择的摄像头设备后，调用`startCapture`方法，开始摄像头采集。示例如下：
``` c++
        int index = m_CameraComboBox.GetCurSel();
        youme->setOpenCameraId(index);
        if (youme->startCapture() == 0){
            m_openCamera = true;
            youme->createLocalRender(m_videoView1.m_hWnd);
        }
```

自身打开/关闭摄像头会收到`YOUME_EVENT_LOCAL_VIDEO_INPUT_START`/`YOUME_EVENT_LOCAL_VIDEO_INPUT_STOP`回调，也可直接在`StartCapture`及`StopCapture`时对render进行处理。




















