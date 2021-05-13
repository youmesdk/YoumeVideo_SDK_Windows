
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ







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