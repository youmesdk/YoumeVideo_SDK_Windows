#pragma once


// YouMeMainDlg 对话框

class CYouMeMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYouMeMainDlg)

public:
	CYouMeMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CYouMeMainDlg();

// 对话框数据
	enum { IDD = IDD_YOUME_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnInterface();
	afx_msg void OnBnClickedBtnExternInput();
	afx_msg void OnBnClickedBtnProduct();
};
