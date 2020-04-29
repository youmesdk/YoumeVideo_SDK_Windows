// YouMeMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YouMeDemo.h"
#include "YouMeMainDlg.h"
#include "YouMeDemoDlg.h"
#include "YouMeExternDemoDlg.h"
#include "YouMeProductDlg.h"
#include "afxdialogex.h"
#include "YouMeVideoDlg.h"

// YouMeMainDlg �Ի���

IMPLEMENT_DYNAMIC(CYouMeMainDlg, CDialogEx)

CYouMeMainDlg::CYouMeMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYouMeMainDlg::IDD, pParent)
{

}

CYouMeMainDlg::~CYouMeMainDlg()
{
}

void CYouMeMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYouMeMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_INTERFACE, &CYouMeMainDlg::OnBnClickedBtnInterface)
	ON_BN_CLICKED(IDC_CMB_EXTERNINPUT, &CYouMeMainDlg::OnBnClickedBtnExternInput)
	//ON_BN_CLICKED(IDC_BTN_PRODUCT, &CYouMeMainDlg::OnBnClickedBtnProduct)

END_MESSAGE_MAP()


// YouMeMainDlg ��Ϣ�������


void CYouMeMainDlg::OnBnClickedBtnInterface()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CYouMeDemoDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	
}

void CYouMeMainDlg::OnBnClickedBtnExternInput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CYouMeExternDemoDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

}

void CYouMeMainDlg::OnBnClickedBtnProduct()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CYouMeProductDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

}
