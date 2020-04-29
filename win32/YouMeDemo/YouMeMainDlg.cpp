// YouMeMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YouMeDemo.h"
#include "YouMeMainDlg.h"
#include "YouMeDemoDlg.h"
#include "YouMeExternDemoDlg.h"
#include "YouMeProductDlg.h"
#include "afxdialogex.h"
#include "YouMeVideoDlg.h"

// YouMeMainDlg 对话框

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


// YouMeMainDlg 消息处理程序


void CYouMeMainDlg::OnBnClickedBtnInterface()
{
	// TODO:  在此添加控件通知处理程序代码
	CYouMeDemoDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	
}

void CYouMeMainDlg::OnBnClickedBtnExternInput()
{
	// TODO:  在此添加控件通知处理程序代码
	CYouMeExternDemoDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

}

void CYouMeMainDlg::OnBnClickedBtnProduct()
{
	// TODO:  在此添加控件通知处理程序代码
	CYouMeProductDlg dlg;
	INT_PTR nResponse = dlg.DoModal();

}
