// YouMeVideoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YouMeDemo.h"
#include "YouMeExternVideoDlg.h"
#include "afxdialogex.h"
#include "YouMeEventCallback.h"
#include "YouMeDemoDlg.h"
//#include "screen.h"
#include <stdio.h>
// YouMeExternVideoDlg 对话框



IMPLEMENT_DYNAMIC(YouMeExternVideoDlg, CDialogEx)

YouMeExternVideoDlg::YouMeExternVideoDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(YouMeExternVideoDlg::IDD, pParent)
{
	m_bVideoFullScreen = FALSE;
	m_openCamera = false;
	m_isJoinRoom = true;
	//m_vecWinId.push_back({ IDC_STATIC_VIDEO1, false });	// for capture render
	//m_vecWinId.push_back({ IDC_STATIC_VIDEO2, false });	// for sdk local render
	m_vecWinId.push_back({ IDC_STATIC_VIDEO3, false });
	m_vecWinId.push_back({ IDC_STATIC_VIDEO4, false });
	IYouMeVideoRenderEngine::initRenderEngine();
}

YouMeExternVideoDlg::~YouMeExternVideoDlg()
{
	IYouMeVideoRenderEngine::destroy();
}


void YouMeExternVideoDlg::PictureIncoming(LPVOID param, LPBYTE data, UINT length, ULONGLONG timestamp)
{
	IYouMeVoiceEngine::getInstance()->inputVideoFrameForShare(data, length, 1280, 720, 4, 0, 0, timestamp);
}

void YouMeExternVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIDEO1, m_videoView1);
	DDX_Control(pDX, IDC_STATIC_VIDEO2, m_videoView2);
	DDX_Control(pDX, IDC_STATIC_VIDEO3, m_videoView3);
	DDX_Control(pDX, IDC_STATIC_VIDEO4, m_videoView4);
	DDX_Control(pDX, IDC_STATIC_VIDEO5, m_videoView5);
	DDX_Control(pDX, IDC_COMBO1, m_CameraComboBox);
	DDX_Control(pDX, IDC_CMB_WNDID, m_cmb_wndid);
}


BEGIN_MESSAGE_MAP(YouMeExternVideoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAM_OPEN, &YouMeExternVideoDlg::OnBnClickedButtonCamOpen)
	ON_BN_CLICKED(IDC_BUTTON_CAM_CLOSE, &YouMeExternVideoDlg::OnBnClickedButtonCamClose)
	ON_BN_CLICKED(IDC_BUTTON_CAM_REFRESH, &YouMeExternVideoDlg::OnBnClickedButtonCamRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SHARE_OPEN, &YouMeExternVideoDlg::OnBnClickedButtonShareOpen)
	ON_BN_CLICKED(IDC_BUTTON_SHARE_CLOSE, &YouMeExternVideoDlg::OnBnClickedButtonShareClose)
	ON_BN_CLICKED(IDC_BUTTON_TRANSCRIBER_OPEN, &YouMeExternVideoDlg::OnBnClickedButtonStartTranscriber)
	ON_BN_CLICKED(IDC_BUTTON_TRANSCRIBER_CLOSE, &YouMeExternVideoDlg::OnBnClickedButtonStopTranscriber)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_OPEN, &YouMeExternVideoDlg::OnBnClickedButtonSaveOpen)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_CLOSE, &YouMeExternVideoDlg::OnBnClickedButtonSaveClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHK_AUTO_STATUS, &YouMeExternVideoDlg::OnBnClickedChkAutoStatus)
	ON_STN_DBLCLK(IDC_STATIC_VIDEO1, &YouMeExternVideoDlg::OnStnDblclickStaticVideo1)
	ON_STN_DBLCLK(IDC_STATIC_VIDEO2, &YouMeExternVideoDlg::OnStnDblclickStaticVideo2)
	ON_STN_DBLCLK(IDC_STATIC_VIDEO3, &YouMeExternVideoDlg::OnStnDblclickStaticVideo3)
	ON_STN_DBLCLK(IDC_STATIC_VIDEO4, &YouMeExternVideoDlg::OnStnDblclickStaticVideo4)
	ON_BN_CLICKED(IDC_BUTTON_SHAREWND_OPEN, &YouMeExternVideoDlg::OnBnClickedButtonSharewndOpen)
	ON_BN_CLICKED(IDC_BUTTON_SHAREWND_CLOSE, &YouMeExternVideoDlg::OnBnClickedButtonSharewndClose)
	ON_BN_CLICKED(IDC_BUTTON_WNDID_REFRESH, &YouMeExternVideoDlg::OnBnClickedButtonWndidRefresh)
END_MESSAGE_MAP()


void YouMeExternVideoDlg::RefreshWindowList(HWND hwndCombobox)
{
	::SendMessage(hwndCombobox, CB_RESETCONTENT, 0, 0);
	int index = 0;

	ZeroMemory(winfoList, sizeof(winfoList));

	HWND hwndCurrent = ::GetWindow(GetDesktopWindow()->GetSafeHwnd(), GW_CHILD);
	do
	{
		//if (IsWindowVisible(hwndCurrent) && !IsIconic(hwndCurrent))
		if (::IsWindowVisible(hwndCurrent))
		{
			RECT clientRect;
			::GetClientRect(hwndCurrent, &clientRect);

			winfoList[index].index = index;

			//String strWindowName;
			//strWindowName.SetLength(GetWindowTextLength(hwndCurrent));
			//GetWindowText(hwndCurrent, strWindowName, strWindowName.Length() + 1);
			::GetWindowText(hwndCurrent, winfoList[index].szWindowName, MAX_LOADSTRING - 1);

			DWORD exStyles = (DWORD)GetWindowLongPtr(hwndCurrent, GWL_EXSTYLE);
			DWORD styles = (DWORD)GetWindowLongPtr(hwndCurrent, GWL_STYLE);

			if (winfoList[index].szWindowName[0] != 0 /*&& sstri(strWindowName, L"battlefield") != nullptr*/)
				exStyles &= ~WS_EX_TOOLWINDOW;

			if ((exStyles & WS_EX_TOOLWINDOW) == 0 && (styles & WS_CHILD) == 0 &&
				clientRect.bottom != 0 && clientRect.right != 0)
			{
				//-------

				DWORD processID;
				GetWindowThreadProcessId(hwndCurrent, &processID);
				if (processID == GetCurrentProcessId())
					continue;

				TCHAR fileName[MAX_PATH + 1];
				lstrcpy(fileName, TEXT("unknown"));

				HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);
				if (hProcess)
				{
					DWORD dwSize = MAX_PATH;
					QueryFullProcessImageName(hProcess, 0, fileName, &dwSize);
					CloseHandle(hProcess);
				}

				//-------
				TCHAR* p = &fileName[lstrlen(fileName)];
				while (p != &fileName[0])
				{
					if (*p == TEXT('\\') || *p == TEXT('/'))
					{
						p++;
						break;
					}
					p--;
				}

				TCHAR szWndHandle[16];
				wsprintf(szWndHandle, TEXT("0x%x"), hwndCurrent);
				TCHAR showName[MAX_PATH + 1];
				lstrcpy(showName, TEXT("["));
				lstrcat(showName, p);
				lstrcat(showName, TEXT("-"));
				lstrcat(showName, szWndHandle);
				lstrcat(showName, TEXT("]:"));
				lstrcat(showName, winfoList[index].szWindowName);

				if (winfoList[index].szWindowName[0] == 0)
					lstrcpy(winfoList[index].szWindowName, p);

				int id = (int)::SendMessage(hwndCombobox, CB_ADDSTRING, 0, (LPARAM)showName);
				::SendMessage(hwndCombobox, CB_SETITEMDATA, id, (LPARAM)hwndCurrent);

				winfoList[index].hWnd = hwndCurrent;
				GetClassName(hwndCurrent, winfoList[index].szWindowClass, MAX_LOADSTRING - 1);

				index++;
			}
		}
	} while (hwndCurrent = ::GetNextWindow(hwndCurrent, GW_HWNDNEXT));
	
	::SendMessage(hwndCombobox, CB_SETCURSEL, 0, 0);
}

// YouMeVideoDlg 消息处理程序
BOOL YouMeExternVideoDlg::OnInitDialog()
{
	__super::OnInitDialog();

	m_config = nullptr;

	// TODO:  在此添加额外的初始化
	int count = IYouMeVoiceEngine::getInstance()->getCameraCount();
	for (int i = 0; i < count; i++){
		std::string strName = IYouMeVoiceEngine::getInstance()->getCameraName(i);
		CString wsName;
		Utf8ToCString(wsName, strName.c_str());
		m_CameraComboBox.InsertString(i, wsName);
	}
	if (count)
		m_CameraComboBox.SetCurSel(0);

	RefreshWindowList(m_cmb_wndid.GetSafeHwnd());

#if 0
	// uxsvreen init ang config
	HINSTANCE hInstance = AfxGetInstanceHandle();
	if (FAILED(InitMedia(hInstance)))
	{
		//MessageBox(NULL, TEXT("InitMedia Failed"), TEXT("title"), MB_OK);
		printf("initmedia failed");
	}
	//m_videoView5.ShowWindow(SW_HIDE);
	SetRenderWnd(m_videoView5.m_hWnd);
	SetCaptureFPS(15);
	SetPictureCallback(PictureIncoming, NULL);

	SetCaptureMode(CAPTURE_MODE_SCREEN);
	SetCaptureWindow(NULL, 0, 0, 0, 0);
	SetOutputSize(1280, 720);
#endif
	//HINSTANCE hInstance = AfxGetInstanceHandle();
	//IYouMeVoiceEngine::getInstance()->StartShareStream(hInstance, 3, m_videoView1.m_hWnd, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void YouMeExternVideoDlg::setConfig(CYouMeConfig* config)
{
	m_config = config;
}


void YouMeExternVideoDlg::OnBnClickedButtonCamOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_openCamera)
		return;



	int index = m_CameraComboBox.GetCurSel();
	IYouMeVoiceEngine::getInstance()->setOpenCameraId(index);

	if (IYouMeVoiceEngine::getInstance()->startCapture() == 0){
		m_openCamera = true;
		IYouMeVideoRenderEngine::getInstance()->createLocalRender(m_videoView2.m_hWnd);
	}
}

void YouMeExternVideoDlg::OnBnClickedButtonCamClose()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_openCamera){
		IYouMeVoiceEngine::getInstance()->stopCapture();
		m_openCamera = false;
		IYouMeVideoRenderEngine::getInstance()->deleteLocalRender();
	}
}

void YouMeExternVideoDlg::OnBnClickedButtonCamRefresh()
{
	m_CameraComboBox.Clear();
	m_CameraComboBox.ResetContent();
	// TODO:  在此添加控件通知处理程序代码
	int count = IYouMeVoiceEngine::getInstance()->getCameraCount();
	for (int i = 0; i < count; i++) {
		std::string strName = IYouMeVoiceEngine::getInstance()->getCameraName(i);
		CString wsName;
		Utf8ToCString(wsName, strName.c_str());
		m_CameraComboBox.InsertString(i, wsName);
	}
	if (count)
		m_CameraComboBox.SetCurSel(0);
}

void YouMeExternVideoDlg::OnBnClickedButtonStartTranscriber()
{
	if (m_config)
	{
		IYouMeVoiceEngine::getInstance()->setTranscriberEnabled(true, m_config->m_pEventCallback);
	}
}
void YouMeExternVideoDlg::OnBnClickedButtonStopTranscriber()
{
	IYouMeVoiceEngine::getInstance()->setTranscriberEnabled(false, nullptr);
}


void YouMeExternVideoDlg::OnBnClickedButtonShareOpen()
{
	IYouMeVoiceEngine::getInstance()->StartShareStream(3, m_videoView1.m_hWnd, NULL);
}


void YouMeExternVideoDlg::OnBnClickedButtonShareClose()
{
	IYouMeVoiceEngine::getInstance()->StopShareStream();
}


void YouMeExternVideoDlg::OnBnClickedButtonSaveOpen()
{
	IYouMeVoiceEngine::getInstance()->startSaveScreen("E:\\workspace\\screen.mp4", m_videoView1.m_hWnd, NULL);
}


void YouMeExternVideoDlg::OnBnClickedButtonSaveClose()
{
	IYouMeVoiceEngine::getInstance()->stopSaveScreen();
}

void YouMeExternVideoDlg::addRender(std::string userId)
{
	//IYouMeVideoRenderEngine::getInstance()->createRender("youme_share", m_videoView3.m_hWnd);
	map_render::iterator iter = m_mapRender.find(userId);
	if (iter != m_mapRender.end())
		return;

	int i = 0;
	int id = 0;
	for (; i < m_vecWinId.size(); i++){
		if (!m_vecWinId[i].use){
			id = m_vecWinId[i].winId;
			break;
		}
	}
	if (!id) return;
	HWND hWnd = GetDlgItem(id)->m_hWnd;
	if (IYouMeVideoRenderEngine::getInstance()->createRender(userId.c_str(), hWnd))
	{
		m_mapRender.insert(std::make_pair(userId, i));
		m_vecWinId[i].use = true;
	}
	else{

	}
}

void YouMeExternVideoDlg::removeRender(std::string userId)
{
	map_render::iterator iter = m_mapRender.find(userId);
	if (iter != m_mapRender.end()){
	
		m_vecWinId[iter->second].use = false;
		IYouMeVideoRenderEngine::getInstance()->deleteRender(userId.c_str());
		m_mapRender.erase(iter);
	}
	
}


void YouMeExternVideoDlg::clearRender()
{
	for (int i = 0; i < m_vecWinId.size(); i++){
		if (m_vecWinId[i].use){
			m_vecWinId[i].use = false;
		}
	}
	m_mapRender.clear();
	IYouMeVideoRenderEngine::getInstance()->deleteAllRender();
}

void YouMeExternVideoDlg::joinRoomSuc(bool state)
{
	if (!state)
	{
		if (m_openCamera){
			//StopStream();
			IYouMeVoiceEngine::getInstance()->StopShareStream();
			IYouMeVoiceEngine::getInstance()->stopInputVideoFrame();
			IYouMeVideoRenderEngine::getInstance()->deleteLocalRender();
			m_openCamera = false;
		}
		clearRender();
	}
	m_isJoinRoom = state;
	

}

void YouMeExternVideoDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值 
	if (YouMeDemoDlg){
		YouMeDemoDlg->OnVideoDlgCLose();
	}
	__super::OnClose();
}


void YouMeExternVideoDlg::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	__super::PostNcDestroy();
	delete this;
}


void YouMeExternVideoDlg::OnCancel()
{
	//DestroyMedia();
	// TODO:  在此添加专用代码和/或调用基类

	DestroyWindow();
	//__super::OnCancel();
}


void YouMeExternVideoDlg::OnBnClickedChkAutoStatus()
{
	// TODO:  在此添加控件通知处理程序代码
}


void YouMeExternVideoDlg::OnStnDblclickStaticVideo1()
{
	FullScreen(IDC_STATIC_VIDEO1);
}


void YouMeExternVideoDlg::OnStnDblclickStaticVideo2()
{
	FullScreen(IDC_STATIC_VIDEO2);
}


void YouMeExternVideoDlg::OnStnDblclickStaticVideo3()
{
	FullScreen(IDC_STATIC_VIDEO3);
}


void YouMeExternVideoDlg::OnStnDblclickStaticVideo4()
{
	FullScreen(IDC_STATIC_VIDEO4);
}


void YouMeExternVideoDlg::FullScreen(int nID)
{
	if (m_bVideoFullScreen)
	{
		GetDlgItem(nID)->SetWindowPlacement(&m_VideoOldWndPlace);
		SetWindowPlacement(&m_WindowOldWndPlace);
		m_bVideoFullScreen = FALSE;
	}
	else
	{
		//保留原来的位置
		GetDlgItem(nID)->GetWindowPlacement(&m_VideoOldWndPlace);
		GetWindowPlacement(&m_WindowOldWndPlace);

		//获取系统屏幕宽高
		int iCurScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		//计算出窗口全屏显示客户端所应该设置的窗口大小，主要为了将不需要显示的窗体边框等部分排除在屏幕外
		CRect rectWholeDlg;
		CRect rectClient;
		GetWindowRect(&rectWholeDlg);//得到当前窗体的总的相对于屏幕的坐标
		RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rectClient);//得到客户区窗口坐标
		ClientToScreen(&rectClient);//将客户区相对窗体的坐标转为相对屏幕坐标
		//GetDlgItem(IDC_STATIC_PICSHOW)->GetWindowRect(rectClient);//得到PICTURE控件坐标

		CRect rectFullScreen;
		rectFullScreen.left = rectWholeDlg.left - rectClient.left;
		rectFullScreen.top = rectWholeDlg.top - rectClient.top;
		rectFullScreen.right = rectWholeDlg.right + iCurScreenWidth - rectClient.right;
		rectFullScreen.bottom = rectWholeDlg.bottom + iCurScreenHeight - rectClient.bottom;

		WINDOWPLACEMENT struWndpl;
		struWndpl.length = sizeof(WINDOWPLACEMENT);
		struWndpl.flags = 0;
		struWndpl.showCmd = SW_SHOWNORMAL;
		struWndpl.rcNormalPosition = rectFullScreen;
		SetWindowPlacement(&struWndpl);
		GetDlgItem(nID)->MoveWindow(CRect(0, 0, iCurScreenWidth, iCurScreenHeight));
		m_bVideoFullScreen = TRUE;
	}
}

//窗口共享
void YouMeExternVideoDlg::OnBnClickedButtonSharewndOpen()
{
	int nCurIdx = m_cmb_wndid.GetCurSel();

	HWND hSelWnd = (HWND)m_cmb_wndid.GetItemData(nCurIdx);

	printf("%x\n", hSelWnd);

	IYouMeVoiceEngine::getInstance()->StartShareStream(2, m_videoView1.m_hWnd, hSelWnd);
}


void YouMeExternVideoDlg::OnBnClickedButtonSharewndClose()
{
	IYouMeVoiceEngine::getInstance()->StopShareStream();
}


void YouMeExternVideoDlg::OnBnClickedButtonWndidRefresh()
{
	RefreshWindowList(m_cmb_wndid.GetSafeHwnd());
}
