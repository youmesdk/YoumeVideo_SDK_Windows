#include "stdafx.h"
#include "YouMeEventCallback.h"
#include <map>

CYouMeEventCallback::CYouMeEventCallback(HWND mHand)
{
	m_msgHand = mHand;
}


CYouMeEventCallback::~CYouMeEventCallback()
{
}


void CYouMeEventCallback::onEvent(const YouMeEvent_t eventType, const YouMeErrorCode iErrorCode, const char * room, const char * param)
{
	std::map<std::string, int> map1;
	std::map<std::string, std::string> map2;

	map1.insert(std::map<std::string, int>::value_type("event", eventType));
	map1.insert(std::map<std::string, int>::value_type("error", iErrorCode));
	map2.insert(std::map<std::string, std::string>::value_type("room", room));
	map2.insert(std::map<std::string, std::string>::value_type("param", param));

	SendMessage(m_msgHand, UM_CONTROL, (WPARAM)&map1, (LPARAM)&map2);
}
void CYouMeEventCallback::onMemberChange( const char* channel, const char* listMemberChange, bool bUpdate ) {
	//todofish
	// std::list<MemberChange> * p = &listMemberChange;

	// SendMessage(m_msgHand, MEMBER_CHANGE, (WPARAM)channel, (LPARAM)p);
}

void CYouMeEventCallback::onAVStatistic(YouMeAVStatisticType type, const char* userID, int value)
{

	SendMessage(m_msgHand, WM_AVSTATIC_MSG, (WPARAM)userID, (LPARAM)&value);
}

#include "atlbase.h"
#include "atlstr.h"
#include <sstream>
void OutputDebugPrintf(const char* strOutputString, ...)
{
	char strBuffer[4096] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	va_end(vlArgs);
	OutputDebugString(CA2W(strBuffer));
}

void  CYouMeEventCallback::onSentenceBegin(std::string userid, int sentenceIndex)
{
}
void  CYouMeEventCallback::onSentenceEnd(std::string userid, int sentenceIndex, std::string result, std::string transLang, std::string transResult)
{
	std::stringstream ss;
	ss << "Tran:" << userid << ":" << result;

	std::string* msg = new std::string(ss.str());
	SendMessage(m_msgHand, WM_TRANSCRIBER_END_MSG, (WPARAM)msg, (LPARAM)nullptr);
}
void  CYouMeEventCallback::onSentenceChanged(std::string userid, int sentenceIndex, std::string result, std::string transLang, std::string transResult)
{
}

void  CYouMeEventCallback::onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
}

//本地录音pcm数据回调
void  CYouMeEventCallback::onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
}

//远端pcm和本地录音pcm的混合pcm数据回调
void  CYouMeEventCallback::onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte)
{
}