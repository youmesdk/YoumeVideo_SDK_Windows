
// YouMeDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYouMeDemoApp: 
// �йش����ʵ�֣������ YouMeDemo.cpp
//

class CYouMeDemoApp : public CWinApp
{
public:
	CYouMeDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYouMeDemoApp theApp;