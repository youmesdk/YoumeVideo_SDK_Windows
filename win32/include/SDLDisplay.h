//
// header file

//
#ifndef __SDL_DISPLAY__
#define __SDL_DISPLAY__


#include <windows.h>
#include <shlwapi.h>
#include <io.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <WinDef.h>


#define SDLDLL_API __declspec(dllexport)


typedef void*   _HSDL;

/**
 * 功能描述: 初始化渲染
 * @param hWnd 渲染窗口句柄
 * @param width 不需要可以传0
 * @param height 不需要可以传0
 * @param fps 不需要可以传0
 * @return 成功返回_HSDL对象，失败返回NULL
 *         其他 - 具体错误码
 */
SDLDLL_API _HSDL  SDL_Display_Init(HWND hWnd, unsigned int width, unsigned int height, unsigned int fps);

/**
 * 功能描述: 反初始化渲染
 * @param  pHandle 释放渲染对手
 * @return void
 */
SDLDLL_API  void  SDL_Display_Uninit(_HSDL pHandle);

/**
 * 功能描述: 传入渲染视频数据
 * @param pHandle 初始化返回的渲染对象
 * @param data 渲染数据，YUV420p格式
 * @param width 视频宽度
 * @param height 视频高度
  * @param i_stride 视频数据行宽度，可等于width
 * @return void
 */
SDLDLL_API  void  SDL_Display(_HSDL pHandle, const unsigned char * data, int width, int height, int i_stride);

/**
 * 功能描述: 清除视频图像，清除后为黑色背景
 * @param pHandle 初始化返回的渲染对象
 * @return void
 */
void SDL_Display_Clear(_HSDL pHandle);
#endif //__SDL_DISPLAY__

