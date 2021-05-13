#pragma once
#include "afxwin.h"
#include <map>
#include <vector>
#include "IYouMeVideoRenderEngine.h"

// YouMeVideoDlg 对话框
class YouMeVideoDlg;
class CYouMeConfig;

#define MAX_LOADSTRING 100

typedef struct UxWindowInfo
{
	int				index;
	HWND			hWnd;
	TCHAR			szWindowClass[MAX_LOADSTRING];
	TCHAR			szWindowName[MAX_LOADSTRING];
}UXWINDOWINFO;


class YouMeExternVideoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(YouMeExternVideoDlg)

public:
	YouMeExternVideoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~YouMeExternVideoDlg();
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
	CStatic m_videoView5;
	afx_msg void OnBnClickedButtonCamOpen();
	afx_msg void OnBnClickedButtonCamClose();
	afx_msg void OnBnClickedButtonCamRefresh();
	afx_msg void OnBnClickedButtonShareOpen();
	afx_msg void OnBnClickedButtonShareClose();
	afx_msg void OnBnClickedButtonStartTranscriber();
	afx_msg void OnBnClickedButtonStopTranscriber();
	afx_msg void OnBnClickedButtonSaveOpen();
	afx_msg void OnBnClickedButtonSaveClose();

	//! 图像回调函数
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

	CYouMeConfig* m_config;
	BOOL m_bVideoFullScreen;
	WINDOWPLACEMENT m_VideoOldWndPlace;
	WINDOWPLACEMENT m_WindowOldWndPlace;

	HWND					hwndComboSelected;
	UXWINDOWINFO			winfoList[100];
	void					RefreshWindowList(HWND hwndCombobox);

private:
	void FullScreen(int nID);
public:
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual void OnCancel();
	CComboBox m_CameraComboBox;
	afx_msg void OnBnClickedChkAutoStatus();
	afx_msg void OnStnDblclickStaticVideo1();
	afx_msg void OnStnDblclickStaticVideo2();
	afx_msg void OnStnDblclickStaticVideo3();
	afx_msg void OnStnDblclickStaticVideo4();
	afx_msg void OnBnClickedButtonSharewndOpen();
	afx_msg void OnBnClickedButtonSharewndClose();
	CComboBox m_cmb_wndid;
	afx_msg void OnBnClickedButtonWndidRefresh();
};
