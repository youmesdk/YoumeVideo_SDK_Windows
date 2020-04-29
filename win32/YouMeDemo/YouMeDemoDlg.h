
// YouMeDemoDlg.h : 头文件
//

#pragma once
#include "YouMeConfig.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "YouMeVideoDlg.h"
// CYouMeDemoDlg 对话框
class CYouMeDemoDlg : public CDialogEx
{
// 构造
public:
	CYouMeDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YOUME_INTERFACE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	virtual void OnCancel();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLeaveroom();

private:
	CYouMeConfig    m_cConfig;
	std::string		m_strUserID;
	std::string		m_strRoomID;
	CString         m_currMessage;
	
	bool isInit = false; // 是否初始化
	bool isInRoom = false; // 是否进了房间

public:

	afx_msg void OnBnClickedBtnJoinroom();
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnUninit();
	afx_msg void OnNMCustomdrawSliderVol(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnCloseMic();
	afx_msg void OnBnClickedBtnGetMic();
	afx_msg void OnBnClickedBtnOpenMic();
	afx_msg void OnBnClickedBtnGetSpeaker();
	afx_msg void OnBnClickedBtnOpenSpeaker();
	afx_msg void OnBnClickedBtnCloseSpeaker();
	afx_msg void OnBnClickedBtnOpenOtherSpeaker();
	afx_msg void OnBnClickedBtnCloseOtherSpeaker();
	afx_msg void OnBnClickedBtnCloseOtherMic();
	afx_msg void OnBnClickedBtnOpenOtherMic();
	afx_msg void OnBnClickedBtnQuit();
	afx_msg void OnBnClickedBtnAvoidOthers();
	afx_msg void OnCbnSelchangeCmbServer();
	afx_msg void OnBnClickedBtnCancleAvoidOther();
	afx_msg void OnCbnDropdownCmbServer();
	afx_msg void OnBnClickedBtnGetVol();
	CSliderCtrl m_sliderVol;
	CComboBox m_ServerList;
	CComboBox m_UserList;
	CButton m_needUserList;
	CButton m_needMic;
	CButton m_needSpeaker;
	CButton m_needAutoStatus;

	CStatic m_setVol;
	CStatic m_getVol;
	CStatic m_sdkVersion;
	CEdit m_currStatus;

	YouMeVideoDlg * m_YouMeVideoDlg;

	CComboBox m_environmentList;
	bool m_switchEnv;
protected:
	afx_msg LRESULT OnInterfaceEvent(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMemberChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUninitMessage(WPARAM w, LPARAM l);
	afx_msg LRESULT OnAvStaticMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTranscriberMsg(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnBnClickedBtnClear();
	
	void ShowStatus(CString msg);

	YouMeErrorCode initEngine();
	afx_msg void OnClose();

	bool Quit();
	void OnVideoDlgCLose();
	CComboBox m_cbVideoProfile;
	CButton m_needTCP;
	afx_msg void OnCbnSelchangeCmbEnvironment();
};


extern CYouMeDemoDlg* YouMeDemoDlg;