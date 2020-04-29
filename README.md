# Video SDK for win32 使用指南

## 适用范围

本规范仅适用于使用游密实时音视频引擎win32接口开发多人实时音视频功能的开发者。

## SDK目录概述

Video SDK中有两个子文件夹：lib、include,下面依次介绍下这两个子文件夹。

1. `include`：SDK的头文件。
详细介绍下inlude，所有接口都在这个文件夹中。
    * `IYouMeVoiceEngine.h`封装了Video SDK的全部功能接口，集成方可通过 IYouMeVoiceEngine::getInstance ()->…来调用语音SDK接口。
    * `IYouMeEventCallback.h`包含Video SDK的所有回调事件接口，例如初始化结果，频道加入成功等，都将通过此接口通知集成方
    * `YouMeConstDefine.h`包含Video SDK的所有枚举类型定义，如错误码等。
	* `SDL.h``SDLDisplay.h`包含视频渲染相关方法。
2. `lib`：库文件，分为release版本和debug版本，包含youme_voice_engine.dll,D3DCompiler_43.dll,avcodec-57.dll,avformat-57.dll,d3dx10_43.dll,libscreen.dll,swresample-2.dll,MediaApi.dll,avdevice-57.dll,,avutil-55.dll,libgcc_s_dw2-1.dll,libx264-152.dll,swscale-4.dll,SDL2.dll,avfilter-6.dll,libiconv-2.dll,shaders

## Visual Studio开发环境集成
将SDK拷贝到相关目录
在项目 -> 属性 -> C/C++ -> 常规 -> 附加包含目录 中添加 include文件夹所在目录
在项目->属性->链接器->常规->附加库目录 中添加lib所在目录
在项目->属性->链接器->输入->附加依赖库 中添加lib
将dll添加到工程目录中


## API接口调用流程
API调用的基本流程如下图所示，具体接口说明参见API接口手册。
![](https://www.youme.im/doc/images/talk_shixutu.png)
