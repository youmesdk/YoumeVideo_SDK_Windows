// YouMeProductDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YouMeDemo.h"
#include "YouMeProductDlg.h"
#include "afxdialogex.h"
#include <vector>

extern "C" {
	_declspec(dllexport) void youme_setTestConfig(int bTest);
}

const static std::map<std::string, YouMeUserRole_t>  g_sUserRoles =
{
	{ "", YOUME_USER_TALKER_ON_DEMAND },
	{ "��ͨģʽ", YOUME_USER_TALKER_FREE },
	{ "����ģʽ", YOUME_USER_LISTENER},
	{ "ָ��ģʽ", YOUME_USER_COMMANDER},
	{ "����ģʽ", YOUME_USER_HOST },
	{ "�ÿ�ģʽ", YOUME_USER_GUSET }
};


extern void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);

// CYouMeProductDlg �Ի���

IMPLEMENT_DYNAMIC(CYouMeProductDlg, CDialogEx)

CYouMeProductDlg::CYouMeProductDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYouMeProductDlg::IDD, pParent)
{

}

CYouMeProductDlg::~CYouMeProductDlg()
{
}


BOOL CYouMeProductDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// SDK init

	/** ʹ�ò��Է����� */
	youme_setTestConfig((int)TEST_SERVER);

	if (m_cConfig.EngineInstance(this->GetSafeHwnd())) {
		YouMeErrorCode ret = m_cConfig.m_pEngine->init(m_cConfig.m_pEventCallback, m_cConfig.g_strKey.c_str(), m_cConfig.g_strSecret.c_str(), RTC_CN_SERVER, "kuangfeng");

		if (ret != YOUME_SUCCESS) {
			// TODO
		}
	}

	// Dialog init

	userRoleSingle.Clear();
	for (auto it = g_sUserRoles.begin(); it != g_sUserRoles.end(); it++) {
		//userRoleSingle.AddString(it->first.c_str());
		CString str;
		charTowchar(it->first, str);
		userRoleSingle.AddString(str.GetBuffer());
	}
	userRoleSingle.SetCurSel(0);


	userRoleMulti.Clear();
	for (auto it = g_sUserRoles.begin(); it != g_sUserRoles.end(); it++) {
		//userRoleMulti.AddString(it->first.c_str());

		CString str;
		charTowchar(it->first, str);
		userRoleMulti.AddString(str.GetBuffer());
	}
	userRoleMulti.SetCurSel(0);



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CYouMeProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_USERID_MULTI, userIDMulti);
	DDX_Control(pDX, IDC_EDT_ROOMID_MULTI, roomIDMulti);
	DDX_Control(pDX, IDC_CMB_ROOMLIST, roomListMulti);
	DDX_Control(pDX, IDC_CMB_MODEL_MULTI, userRoleMulti);
	DDX_Control(pDX, IDC_EDT_USERID_SINGLE, userIDSingle);
	DDX_Control(pDX, IDC_EDT_ROOMID_SINGLE, roomIDSingle);
	DDX_Control(pDX, IDC_CMB_MODEL_SINGLE, userRoleSingle);
	DDX_Control(pDX, IDC_EDIT1, productLog);
	DDX_Control(pDX, IDC_COMBO1, m_UserListMulti);
}


BEGIN_MESSAGE_MAP(CYouMeProductDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_JOIN, &CYouMeProductDlg::OnBnClickedBtnJoin)
	ON_BN_CLICKED(IDC_BTN_LEAVE, &CYouMeProductDlg::OnBnClickedBtnLeave)
	ON_BN_CLICKED(IDC_BTN_JOIN_MULTI, &CYouMeProductDlg::OnBnClickedBtnJoinMulti)
	ON_BN_CLICKED(IDC_BTN_SPEAKTO, &CYouMeProductDlg::OnBnClickedBtnSpeakto)
	ON_BN_CLICKED(IDC_BTN_LEAVE_MULTI, &CYouMeProductDlg::OnBnClickedBtnLeaveMulti)
	ON_BN_CLICKED(IDC_BTN_PRODUCT_LOG, &CYouMeProductDlg::OnBnClickedBtnProductLog)
	ON_MESSAGE(UM_CONTROL, &CYouMeProductDlg::OnProductEvent)
END_MESSAGE_MAP()


// CYouMeProductDlg ��Ϣ�������

void CYouMeProductDlg::OnBnClickedBtnJoin()
{
	// TODO
	ShowStatus(_T("��ûʵ�֣�"));
}


void CYouMeProductDlg::OnBnClickedBtnLeave()
{
	// TODO
	ShowStatus(_T("��ûʵ�֣�"));
}


void CYouMeProductDlg::OnBnClickedBtnJoinMulti()
{
	CString userid;
	CString roomid;
	CString userrole;
	userIDMulti.GetWindowText(userid);
	roomIDMulti.GetWindowText(roomid);
	userRoleMulti.GetWindowText(userrole);

	if (userid.IsEmpty() || roomid.IsEmpty()) {
		return;
	}
	wcharTochar(userid, m_strUserID);
	wcharTochar(roomid, m_strRoomID);
	//m_strUserID = userid.GetBuffer();
	//m_strRoomID = roomid.GetBuffer();
	std::string str;
	wcharTochar(userrole, str);
	auto it = g_sUserRoles.find(str.c_str());

	if (it != g_sUserRoles.end()) {
		m_userRole = it->second;
	}
	else {
		// Wrong role
		return;
	}

	CString strStatusDis;
	strStatusDis.Format(_T("����Ƶ����===��Roomid: %s, ===��Userid: %s, ===��Mode: %d"), userid.GetBuffer(), roomid.GetBuffer(), m_userRole);
	ShowStatus(strStatusDis);

	if (m_cConfig.EngineInstance(this->GetSafeHwnd())) {
		m_cConfig.m_pEngine->joinChannelMultiMode(m_strUserID.c_str(), m_strRoomID.c_str(), YOUME_USER_HOST);
	}
}


void CYouMeProductDlg::OnBnClickedBtnSpeakto()
{
	if (roomListMulti.GetCount() <= 0) {
		ShowStatus(_T("û�п��л���Ƶ����Ƶ��ID����Ϊ�գ�"));
		return;
	}

	CString cs;
	roomListMulti.GetLBText(roomListMulti.GetCurSel(), cs);
	std::string roomID;// = cs.GetBuffer();
	wcharTochar(cs, roomID);
	if (roomID.empty() || roomID.compare("") == 0) {
		ShowStatus(_T("����ID����Ϊ�գ�"));
		return;
	}
	else {
		CString strStatusDis;
		strStatusDis.Format(_T("�л�Ƶ����roomid:%s"), cs.GetString());
		ShowStatus(strStatusDis);
	}

	if (m_cConfig.EngineInstance(this->GetSafeHwnd())) {
		m_cConfig.m_pEngine->speakToChannel(roomID.c_str());
	}
}


void CYouMeProductDlg::OnBnClickedBtnLeaveMulti()
{
	if (roomListMulti.GetCount() <= 0) {
		ShowStatus(_T("û�п��뿪��Ƶ����Ƶ��ID����Ϊ�գ�"));
		return;
	}

	CString cs;
	roomListMulti.GetLBText(roomListMulti.GetCurSel(), cs);
	std::string roomID;// = cs.GetBuffer();
	wcharTochar(cs, roomID);
	if (roomID.empty() || roomID.compare("") == 0) {
		ShowStatus(_T("Ƶ��ID����Ϊ�գ�"));
		return;
	}
	else {
		CString strStatusDis;
		strStatusDis.Format(_T("�뿪Ƶ����roomid:%s"), cs.GetString());
		ShowStatus(strStatusDis);
	}

	if (m_cConfig.EngineInstance(this->GetSafeHwnd())) {
		m_cConfig.m_pEngine->leaveChannelMultiMode(roomID.c_str());
	}
}


/**
* ��ʾStatus
*/
void CYouMeProductDlg::ShowStatus(CString msg) {
	m_currMessage.Append(_T("[rtc@youme ~]#  "));
	m_currMessage.Append(msg);
	m_currMessage.Append(_T("\r\n"));
	productLog.SetWindowText(m_currMessage);

	/** ������������ */
	int iCount = m_currMessage.GetLength();
	productLog.SetRedraw(FALSE);
	productLog.SetWindowText(m_currMessage);
	int iLine = productLog.GetLineCount();
	productLog.LineScroll(iLine, 0);
	productLog.SetSel(iCount, iCount);
	productLog.SetRedraw(TRUE);
}

void CYouMeProductDlg::OnBnClickedBtnProductLog()
{
	m_currMessage.Empty();
	productLog.SetWindowText(m_currMessage);
}


/** ��Ա�仯 */
void CYouMeProductDlg::OnMemberChange(std::string roomid, std::string userlists)
{
	CString strStatusDis;
	CString cs;
	charTowchar(roomid, cs);
	strStatusDis.Format(_T("�ص���OnMemberChange RoomID:%s"), cs.GetString());
	ShowStatus(strStatusDis);

	UpdateData(TRUE);
	std::vector<std::string> vct;
	SplitString(userlists, vct, ",");
	m_UserListMulti.ResetContent();
	for (std::vector<std::string>::const_iterator iter = vct.cbegin(); iter != vct.cend(); iter++) {
		CString strUser;
		strUser.Format(_T("%s"), ((std::string)*iter).c_str());
		m_UserListMulti.AddString(strUser);
	}
	m_UserListMulti.SetCurSel(0);
	strStatusDis.Empty();
	strStatusDis.Format(_T("�ص���OnMemberChange ��ԱID�б�%s"), userlists.c_str());
	ShowStatus(strStatusDis);
	UpdateData(FALSE);
	UpdateWindow();
}


afx_msg LRESULT CYouMeProductDlg::OnProductEvent(WPARAM wParam, LPARAM lParam)
{
	std::map<std::string, int> * map1 = (std::map<std::string, int> *)wParam;
	std::map<std::string, std::string> * map2 = (std::map<std::string, std::string> *)lParam;

	auto it1 = map1->find("event");
	auto it2 = map1->find("error");
	auto it3 = map2->find("room");
	auto it4 = map2->find("param");
	YouMeEvent event = (YouMeEvent)it1->second;
	YouMeErrorCode error = (YouMeErrorCode)it2->second;
	std::string room = it3->second;
	std::string param = it4->second;
	CString strRoom, strParam;
	charTowchar(room, strRoom);
	charTowchar(param, strParam);
	CString strStatusDis;
	strStatusDis.Format(_T("�ص���OnEvent event: %d, error: %d, room: %s, param: %s"), event, error, strRoom.GetBuffer(), strParam.GetBuffer());
	ShowStatus(strStatusDis);

	switch (event) {
	case YOUME_EVENT_INIT_OK:			 ///< SDK��֤�ɹ�
		break;
	case YOUME_EVENT_INIT_FAILED:           ///< SDK��֤ʧ��
		break;
	case YOUME_EVENT_JOIN_OK:  {
		roomListMulti.AddString(strRoom.GetBuffer());
		roomListMulti.SetCurSel(0);
	}
		break;
	case YOUME_EVENT_JOIN_FAILED: 
		break;
	case YOUME_EVENT_LEAVED_ONE: {
		roomListMulti.DeleteString(roomListMulti.FindStringExact(0, strRoom.GetBuffer()));
		roomListMulti.SetCurSel(0);
	}
		break;
	//case YOUME_EVENT_INCOMING:           ///< �յ�����
	//	break; 
	//case YOUME_EVENT_INPROGRESS:         ///< ���ں���
	//	break; 
	//case YOUME_EVENT_RINGING:            ///< Զ��������
	//	break; 
	//case YOUME_EVENT_CONNECTED:          ///< ���гɹ�
	//	roomListMulti.AddString(room.c_str());
	//	roomListMulti.SetCurSel(0);
	//	break; 
	//case YOUME_EVENT_TERMWAITING:        ///< �Ҷ��У����������������߶Է��Ҷ�ʱ���ܵ����¼�
	//	break; 
	//case YOUME_EVENT_TERMINATED:         ///< �ѹҶϣ����������������߶Է��Ҷ�ʱ���ܵ����¼�
	//	roomListMulti.DeleteString(roomListMulti.FindStringExact(0, room.c_str()));
	//	roomListMulti.SetCurSel(0);
	//	break; 
	//case YOUME_EVENT_FAILED:             ///< ����ʧ��
	//	break; 
	case YOUME_EVENT_REC_PERMISSION_STATUS:///< ֪ͨ¼��Ȩ��״̬���ɹ���ȡȨ��ʱ������ΪYOUME_SUCCESS����ȡʧ��ΪYOUME_ERROR_REC_NO_PERMISSION����ʱ������˷�mute״̬��Σ���û�����������
		break; 
	case YOUME_EVENT_BGM_STOPPED:        ///< ֪ͨ�������ֲ��Ž���
		break; 
	case YOUME_EVENT_BGM_FAILED:         ///< ֪ͨ�������ֲ���ʧ��
		break; 
	//case YOUME_EVENT_PAUSE:              ///< ֪ͨ��ͣͨ���Ƿ�ɹ�
	//	break; 
	//case YOUME_EVENT_RESUME:             ///< ֪ͨ�ָ�ͨ���Ƿ�ɹ�
	//	break; 
	case YOUME_EVENT_SPEAK_SUCCESS:      ///< �л�����ͨ���ɹ�
		break; 
	case YOUME_EVENT_SPEAK_FAILED:       ///< �л�����ͨ��ʧ��
		break; 
	/*case YOUME_EVENT_MEMBER_CHANGE:      ///< �����Ա�仯
		break; 
	case YOUME_EVENT_MIC_NORMAL:         ///< ��˷��������򿪣�
		break; 
	case YOUME_EVENT_MIC_MUTE:           ///< ��˷羲�����رգ�
		break; 
	case YOUME_EVENT_SPEAKER_NORMAL:     ///< �������������򿪣�
		break; 
	case YOUME_EVENT_SPEAKER_MUTE:       ///< �������������رգ�
		break; 
	case YOUME_EVENT_MIC_CTR_NORMAL:     ///< ��˷�����������򿪣�
		break; 
	case YOUME_EVENT_MIC_CTR_MUTE:       ///< ��˷���ƾ������رգ�
		break; 
	case YOUME_EVENT_SPEAKER_CTR_NORMAL: ///< �����������������򿪣�
		break; 
	case YOUME_EVENT_SPEAKER_CTR_MUTE:   ///< ���������ƾ������رգ�
		break; 
	case YOUME_EVENT_AVOID_OTHER_NORMAL: ///< �������������������Σ�
		break; 
	case YOUME_EVENT_AVOID_OTHER_MUTE:   ///< �������˾��������Σ�
		break; 
	case YOUME_EVENT_FAILED_LEAVE:        ///< �˳�����ʧ��
		break;
		*/
	default:
		break;
	}

	UpdateData(FALSE);
	UpdateWindow();
	return 0;
}