#pragma once
#include "afxwin.h"
#include <map>
#include <vector>
#include "IYouMeVideoRenderEngine.h"

// YouMeVideoDlg 对话框
class YouMeVideoDlg;
class CYouMeConfig;


class YouMeVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YouMeVideoDlg)

public:
	YouMeVideoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~YouMeVideoDlg();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_YOUME_VIDEO };

	void setConfig(CYouMeConfig* config);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void addRender(std::string userId);
	void removeRender(std::string userid);
	void clearRender();
	void joinRoomSuc(bool state);

public:
	CStatic m_videoView1;
	CStatic m_videoView2;
	CStatic m_videoView3;
	CStatic m_videoView4;
	afx_msg void OnBnClickedButtonCamOpen();
	afx_msg void OnBnClickedButtonCamClose();
	afx_msg void OnBnClickedButtonCamRefresh();
	afx_msg void OnBnClickedButtonShareOpen();
	afx_msg void OnBnClickedButtonShareClose();
	afx_msg void OnBnClickedButtonStartTranscriber();
	afx_msg void OnBnClickedButtonStopTranscriber();

	//
	static void PictureIncoming(LPVOID param, LPBYTE data, UINT length, ULONGLONG timestamp);
private:

	struct winInfo{
		int winId;
		bool use;
	};
	std::vector<winInfo> m_vecWinId;

	typedef std::map<std::string, int> map_render;
	map_render m_mapRender;
	
	bool m_openCamera;
	bool m_openShare;
	bool m_isJoinRoom;
public:
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual void OnCancel();
	CComboBox m_CameraComboBox;

	CYouMeConfig* m_config;
};
