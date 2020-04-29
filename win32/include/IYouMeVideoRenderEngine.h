#pragma once
#include <string>
#include <wtypes.h>


#ifdef WIN32
#ifdef YOUMEVIDEO_EXPORTS
#define YOUMEVIDEO_API __declspec(dllexport)
#else
#define YOUMEVIDEO_API __declspec(dllimport)
#endif
#else
#define YOUMEVIDEO_API __attribute ((visibility("default")))
#endif

class YOUMEVIDEO_API IYouMeVideoRenderEngine
{

public:
	static IYouMeVideoRenderEngine* getInstance();

	/**
	*  功能描述:初始化引擎(主线程调用)
	*
	*  @return 无
	*/
	static bool initRenderEngine();

	/**
	*  功能描述:销毁引擎实例，释放内存
	*
	*  @return 无
	*/
	static void destroy();


	/**
	*  功能描述: 创建本地预览渲染, 未进房间之前预览使用
	*  @param  hWnd:渲染窗口句柄
	*  @return true - 成功， false - 失败
	*/
	bool createLocalRender(HWND  hWnd);

	/**
	*  功能描述: 删除本地预览渲染
	*  @return void
	*/
	void deleteLocalRender();

	/**
	*  功能描述: 创建视频渲染，将用户ID和渲染窗口绑定
	*  @param  userId:指定渲染用户ID
	*  @param  hWnd:渲染窗口句柄
	*  @return true - 成功， false - 失败
	*/
	bool createRender(const char* userId, HWND  hWnd);

	/**
	*  功能描述: 删除视频渲染
	*  @param  userId:指定渲染用户ID
	*  @return void
	*/
	void deleteRender(const char* userId);

	/**
	*  功能描述: 清除所有渲染绑定，不包括本地预览渲染
	*  @return void
	*/
	void deleteAllRender();

public:
	IYouMeVideoRenderEngine();
	~IYouMeVideoRenderEngine();

};

