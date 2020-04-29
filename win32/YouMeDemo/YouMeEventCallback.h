#pragma once
#include <windows.h>
#include <string>
#include "IYouMeVoiceEngine.h"

class CYouMeEventCallback : public IYouMeEventCallback, public IYouMeMemberChangeCallback, 
	public IYouMeAVStatisticCallback, public IYouMeTranscriberCallback, public IYouMePcmCallback
{
public:
	CYouMeEventCallback(HWND mHand = NULL);
	~CYouMeEventCallback();
private:
	HWND m_msgHand;
public:
	virtual void onEvent(const YouMeEvent event, const YouMeErrorCode error, const char * room, const char * param) override;

	virtual void onMemberChange( const char* channel, const char* listMemberChange, bool bUpdate ) override;

	virtual void onAVStatistic(YouMeAVStatisticType type, const char* userID, int value);

	virtual void onSentenceBegin(std::string userid, int sentenceIndexe) override;
	virtual void onSentenceEnd(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "") override;
	virtual void onSentenceChanged(std::string userid, int sentenceIndex, std::string result, std::string transLang = "", std::string transResult = "")override;

	virtual void onPcmDataRemote(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
	//本地录音pcm数据回调
	virtual void onPcmDataRecord(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
	//远端pcm和本地录音pcm的混合pcm数据回调
	virtual void onPcmDataMix(int channelNum, int samplingRateHz, int bytesPerSample, void* data, int dataSizeInByte) override;
};