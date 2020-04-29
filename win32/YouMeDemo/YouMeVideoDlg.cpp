// YouMeVideoDlg.cpp :
//

#include "stdafx.h"
#include "YouMeDemo.h"
#include "YouMeVideoDlg.h"
#include "afxdialogex.h"
#include "YouMeEventCallback.h"
#include "YouMeDemoDlg.h"
#include <stdio.h>
// YouMeVideoDlg



IMPLEMENT_DYNAMIC(YouMeVideoDlg, CDialogEx)

YouMeVideoDlg::YouMeVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(YouMeVideoDlg::IDD, pParent)
{
	m_openCamera = false;
	m_isJoinRoom = true;
	//m_vecWinId.push_back({ IDC_STATIC_VIDEO1, false });
	//m_vecWinId.push_back({ IDC_STATIC_VIDEO2, false });
	m_vecWinId.push_back({ IDC_STATIC_VIDEO3, false });
	m_vecWinId.push_back({ IDC_STATIC_VIDEO4, false });
	IYouMeVideoRenderEngine::initRenderEngine();
}

YouMeVideoDlg::~YouMeVideoDlg()
{
	IYouMeVideoRenderEngine::destroy();
}

void YouMeVideoDlg::PictureIncoming(LPVOID param, LPBYTE data, UINT length, ULONGLONG timestamp)
{
	IYouMeVoiceEngine::getInstance()->inputVideoFrameForShare(data, length, 1280, 720, 4, 0, 0, timestamp);
}
void YouMeVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VIDEO1, m_videoView1);
	DDX_Control(pDX, IDC_STATIC_VIDEO2, m_videoView2);
	DDX_Control(pDX, IDC_STATIC_VIDEO3, m_videoView3);
	DDX_Control(pDX, IDC_STATIC_VIDEO4, m_videoView4);
	DDX_Control(pDX, IDC_COMBO1, m_CameraComboBox);
}


BEGIN_MESSAGE_MAP(YouMeVideoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAM_OPEN, &YouMeVideoDlg::OnBnClickedButtonCamOpen)
	ON_BN_CLICKED(IDC_BUTTON_CAM_CLOSE, &YouMeVideoDlg::OnBnClickedButtonCamClose)
	ON_BN_CLICKED(IDC_BUTTON_CAM_REFRESH, &YouMeVideoDlg::OnBnClickedButtonCamRefresh)
	ON_BN_CLICKED(IDC_BUTTON_SHARE_OPEN, &YouMeVideoDlg::OnBnClickedButtonShareOpen)
	ON_BN_CLICKED(IDC_BUTTON_SHARE_CLOSE, &YouMeVideoDlg::OnBnClickedButtonShareClose)
	ON_BN_CLICKED(IDC_BUTTON_TRANSCRIBER_OPEN, &YouMeVideoDlg::OnBnClickedButtonStartTranscriber)
	ON_BN_CLICKED(IDC_BUTTON_TRANSCRIBER_CLOSE, &YouMeVideoDlg::OnBnClickedButtonStopTranscriber)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// YouMeVideoDlg
BOOL YouMeVideoDlg::OnInitDialog()
{
	m_config = nullptr;
	__super::OnInitDialog();

	m_CameraComboBox.Clear();

	// TODO:
	int count = IYouMeVoiceEngine::getInstance()->getCameraCount();
	for (int i = 0; i < count; i++){
		std::string strName = IYouMeVoiceEngine::getInstance()->getCameraName(i);
		CString wsName;
		charTowchar(strName, wsName);
		m_CameraComboBox.InsertString(i, wsName);
	}
	if (count)
		m_CameraComboBox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	//FALSE
}

void YouMeVideoDlg::setConfig(CYouMeConfig* config )
{
	m_config = config;
}


void YouMeVideoDlg::OnBnClickedButtonCamOpen()
{
	// TODO: 
	if (m_openCamera)
		return;


	
	int index = m_CameraComboBox.GetCurSel();
	IYouMeVoiceEngine::getInstance()->setOpenCameraId(index);
	
	if (IYouMeVoiceEngine::getInstance()->startCapture() == 0){
		m_openCamera = true;
		IYouMeVideoRenderEngine::getInstance()->createLocalRender(m_videoView2.m_hWnd);
	}
	
}


void YouMeVideoDlg::OnBnClickedButtonCamClose()
{
	//TODO:
	if (m_openCamera){
		IYouMeVoiceEngine::getInstance()->stopCapture();
		m_openCamera = false;
		IYouMeVideoRenderEngine::getInstance()->deleteLocalRender();
	}
}

void YouMeVideoDlg::OnBnClickedButtonStartTranscriber()
{
	if (m_config)
	{
		IYouMeVoiceEngine::getInstance()->setTranscriberEnabled(true, m_config->m_pEventCallback);
	}
}
void YouMeVideoDlg::OnBnClickedButtonStopTranscriber()
{
	IYouMeVoiceEngine::getInstance()->setTranscriberEnabled(false, nullptr);
}


void YouMeVideoDlg::OnBnClickedButtonShareOpen()
{
	IYouMeVoiceEngine::getInstance()->StartShareStream(3, m_videoView1.m_hWnd, NULL);

	//IYouMeVoiceEngine::getInstance()->startSaveScreen("E:\\workspace\\screen.mp4");
}


void YouMeVideoDlg::OnBnClickedButtonShareClose()
{

	IYouMeVoiceEngine::getInstance()->StopShareStream();
	//IYouMeVoiceEngine::getInstance()->stopSaveScreen();
}

void YouMeVideoDlg::OnBnClickedButtonCamRefresh()
{
	m_CameraComboBox.Clear();
	m_CameraComboBox.ResetContent();
	// TODO
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





void YouMeVideoDlg::addRender(std::string userId)
{
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

void YouMeVideoDlg::removeRender(std::string userId)
{
	map_render::iterator iter = m_mapRender.find(userId);
	if (iter != m_mapRender.end()){
	
		m_vecWinId[iter->second].use = false;
		IYouMeVideoRenderEngine::getInstance()->deleteRender(userId.c_str());
		m_mapRender.erase(iter);
	}
	
}


void YouMeVideoDlg::clearRender()
{
	for (int i = 0; i < m_vecWinId.size(); i++){
		if (m_vecWinId[i].use){
			m_vecWinId[i].use = false;
		}
	}
	m_mapRender.clear();
	IYouMeVideoRenderEngine::getInstance()->deleteAllRender();
}

void YouMeVideoDlg::joinRoomSuc(bool state)
{
	if (!state)
	{
		if (m_openCamera){
			IYouMeVoiceEngine::getInstance()->StopShareStream();
			IYouMeVoiceEngine::getInstance()->stopCapture();
			IYouMeVideoRenderEngine::getInstance()->deleteLocalRender();
			m_openCamera = false;
		}
		clearRender();
	}
	m_isJoinRoom = state;
	

}

void YouMeVideoDlg::OnClose()
{
	// TODO
	if (YouMeDemoDlg){
		YouMeDemoDlg->OnVideoDlgCLose();
	}
	__super::OnClose();
}


void YouMeVideoDlg::PostNcDestroy()
{
	// TODO

	__super::PostNcDestroy();
	delete this;
}


void YouMeVideoDlg::OnCancel()
{
	// TODO
	DestroyWindow();
	//__super::OnCancel();
}
