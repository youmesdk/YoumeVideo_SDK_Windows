#include <stdio.h>
#include <windows.h>
#include "../../../youme_voice_engine/bindings/cocos2d-x/interface/IYouMeVoiceEngine.h"
#include "../../../youme_voice_engine/bindings/cocos2d-x/interface/IMyYouMeInterface.h"
#include <time.h>

extern "C" {
	_declspec(dllexport) void youme_setTestConfig(int bTest);
}

class CMyCommonCallback :public IYouMeCommonCallback
{
public:

	virtual void onEvent(const YouMeEvent_t &eventType, const YouMeErrorCode &iErrorCode) override
	{
		printf("onEvent:type:%d errorcode:%d\r\n", eventType, iErrorCode);
		if (iErrorCode ==  0)
		{
			srand(time(0));
			int iID =  rand();
			char szUserid[20] = { 0 };
			sprintf(szUserid, "testxp_%d", iID);
			IYouMeVoiceEngine::getInstance()->joinConference(szUserid, "YouMe_1");
		}
	}

};

class CMyConferenceCallback :public IYouMeConferenceCallback
{
public:

private:


	virtual void onCallEvent(const YouMeCallEvent_t &event, const YouMeErrorCode_t &errCode, const std::string & strRoomID) override
	{
		printf("onCallEvent:type:%d errorcode:%d\r\n", event, errCode);
	}

	virtual void onCommonStatusEvent(STATUS_EVENT_TYPE_t eventType, const std::string &strUserID, int iStatus) override
	{
	}

	virtual void onMemberChangeEvent(const std::string &strUserIDs, const std::string & strRoomID) override
	{
		printf("onMemberChangeEvent:userid:%s\r\n", strUserIDs.c_str());
	}

};




int main()
{
	
#if WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
#endif

	youme_setTestConfig(1);
	IYouMeVoiceEngine::getInstance()->init(new CMyCommonCallback, new CMyConferenceCallback, "YOUME5BE427937AF216E88E0F84C0EF148BD29B691556", "y1sepDnrmgatu/G8rx1nIKglCclvuA5tAvC0vXwlfZKOvPZfaUYOTkfAdUUtbziW8Z4HrsgpJtmV/RqhacllbXD3abvuXIBlrknqP+Bith9OHazsC1X96b3Inii6J7Und0/KaGf3xEzWx/t1E1SbdrbmBJ01D1mwn50O/9V0820BAAE=");
	
	Sleep(10000000);
    return 0;
}