#pragma once

#include "YouMeConfig.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <map>


// CYouMeProductDlg �Ի���

class CYouMeProductDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYouMeProductDlg)

public:
	CYouMeProductDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYouMeProductDlg();

// �Ի�������
	enum { IDD = IDD_YOUME_PRODUCT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	void ShowStatus(CString msg);


private:
	CYouMeConfig    m_cConfig;
	std::string		m_strUserID;
	std::string		m_strRoomID;
	YouMeUserRole_t m_userRole;
	CString         m_currMessage;

public:
	afx_msg void OnBnClickedBtnJoin();
	afx_msg void OnBnClickedBtnLeave();
	afx_msg void OnBnClickedBtnJoinMulti();
	afx_msg void OnBnClickedBtnSpeakto();
	afx_msg void OnBnClickedBtnLeaveMulti();
	// �û�ID
	CEdit userIDMulti;
	CEdit roomIDMulti;
	CComboBox roomListMulti;
	CComboBox userRoleMulti;
	CEdit userIDSingle;
	CEdit roomIDSingle;
	CComboBox userRoleSingle;
	afx_msg void OnBnClickedBtnProductLog();
	CEdit productLog;
protected:
	afx_msg LRESULT OnProductEvent(WPARAM wParam, LPARAM lParam);

	void OnMemberChange(std::string roomid, std::string userlists);
public:
	CComboBox m_UserListMulti;
};
