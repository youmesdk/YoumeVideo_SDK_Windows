#include "stdafx.h"
#include "YouMeConfig.h"



std::string CYouMeConfig::strJoinAppKey = "YOUME5BE427937AF216E88E0F84C0EF148BD29B691556";

std::string CYouMeConfig::g_strKey = "YOUME5BE427937AF216E88E0F84C0EF148BD29B691556";
std::string CYouMeConfig::g_strSecret = "y1sepDnrmgatu/G8rx1nIKglCclvuA5tAvC0vXwlfZKOvPZfaUYOTkfAdUUtbziW8Z4HrsgpJtmV/RqhacllbXD3abvuXIBlrknqP+Bith9OHazsC1X96b3Inii6J7Und0/KaGf3xEzWx/t1E1SbdrbmBJ01D1mwn50O/9V0820BAAE=";

CYouMeConfig::CYouMeConfig()
{
	m_pEngine = NULL;
	m_pEventCallback = NULL;
}
CYouMeConfig::~CYouMeConfig()
{
}
/**
 *
 */
BOOL CYouMeConfig::EngineInstance(HWND mHand)
{
	if (!m_pEngine)
	{
		m_pEngine = IYouMeVoiceEngine::getInstance();
	}

	if (!m_pEventCallback) {
		m_pEventCallback = new CYouMeEventCallback(mHand);
	}

	return (m_pEngine && m_pEventCallback);
}