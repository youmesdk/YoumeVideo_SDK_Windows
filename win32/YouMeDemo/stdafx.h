
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展







#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#pragma warning(disable:4996) 
#pragma warning(disable:4819) 


#define UM_CONTROL  (WM_USER + 1)
#define MEMBER_CHANGE  (WM_USER + 2)
#define WM_UNINIT_MSG (WM_USER + 3)
#define WM_AVSTATIC_MSG (WM_USER + 4)
#define WM_TRANSCRIBER_END_MSG (WM_USER+5)

#define TEST_SERVER    0

#include<string>

static bool Utf8ToCString(CString& cstr, const char* utf8Str)
{
	size_t utf8StrLen = strlen(utf8Str);

	if (utf8StrLen == 0)
	{
		cstr.Empty();
		return true;
	}

	LPWSTR ptr = cstr.GetBuffer(utf8StrLen + 1);

#ifdef UNICODE
	int newLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str, utf8StrLen, ptr, utf8StrLen + 1);
	if (!newLen)
	{
		cstr.ReleaseBuffer(0);
		return false;
	}
#else
	WCHAR* buf = (WCHAR*)malloc(utf8StrLen);

	if (buf == NULL)
	{
		cstr.ReleaseBuffer(0);
		return false;
	}

	int newLen = MultiByteToWideChar(CP_UTF8, 0,utf8Str, utf8StrLen, buf, utf8StrLen);
	if (!newLen)
	{
		free(buf);
		cstr.ReleaseBuffer(0);
		return false;
	}

	newLen = WideCharToMultiByte(CP_ACP, 0,buf, newLen, ptr, utf8StrLen);
	if (!newLen)
	{
		free(buf);
		cstr.ReleaseBuffer(0);
		return false;
	}

	free(buf);
#endif
	cstr.ReleaseBuffer(newLen);

	return true;
}




static void charTowchar(const std::string& chr, CString& wchar)
{
	int len = chr.length() * sizeof(wchar_t) + 1;
	LPTSTR pstr = wchar.GetBufferSetLength(chr.length()+1);
	MultiByteToWideChar(CP_ACP, 0, chr.c_str(),
		chr.length() + 1, pstr, chr.length()+1);
}

static void wcharTochar(CString& wchar, std::string& chr)
{
	int len = wchar.GetLength() * sizeof(wchar_t) + 1;
	chr.resize(len);
	WideCharToMultiByte(CP_ACP, 0, wchar.GetBuffer(), -1,
		&chr[0], len, NULL, NULL);
}