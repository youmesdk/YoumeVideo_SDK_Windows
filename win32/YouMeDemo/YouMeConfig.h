//
//
//
//
//
//

#pragma once
#include "YouMeEventCallback.h"
#include "afxcmn.h"
#include "afxwin.h"

class CYouMeConfig
{
public:
	CYouMeConfig();
	~CYouMeConfig();

public:
	BOOL EngineInstance(HWND mHand);

public:
	IYouMeVoiceEngine *  m_pEngine;
	CYouMeEventCallback * m_pEventCallback;

	static std::string g_strKey;
	static std::string g_strSecret;
	static std::string strJoinAppKey;
};