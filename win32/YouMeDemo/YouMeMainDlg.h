#pragma once


// YouMeMainDlg �Ի���

class CYouMeMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CYouMeMainDlg)

public:
	CYouMeMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYouMeMainDlg();

// �Ի�������
	enum { IDD = IDD_YOUME_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnInterface();
	afx_msg void OnBnClickedBtnExternInput();
	afx_msg void OnBnClickedBtnProduct();
};
