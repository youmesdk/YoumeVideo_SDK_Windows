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
END_MESSAGE_MAP()


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
		charTowchar(strName, wsName);
		m_CameraComboBox.InsertString(i, wsName);
	}
	if (count)
		m_CameraComboBox.SetCurSel(0);
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
		charTowchar(strName, wsName);
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
