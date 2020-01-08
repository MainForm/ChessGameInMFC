// DlgCreateServer.cpp: 구현 파일
//

#include "pch.h"
#include "Chess.h"
#include "DlgCreateServer.h"
#include "afxdialogex.h"

// DlgCreateServer 대화 상자

IMPLEMENT_DYNAMIC(DlgCreateServer, CDialog)

DlgCreateServer::DlgCreateServer(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CREATESERVER, pParent)
	, ctrl_Port(_T(""))
{

}

DlgCreateServer::~DlgCreateServer()
{
}

void DlgCreateServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ctrl_Port);
}


BEGIN_MESSAGE_MAP(DlgCreateServer, CDialog)
//	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &DlgCreateServer::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgCreateServer 메시지 처리기

/*

*/
//int DlgCreateServer::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
//	
//	
//	//ctrlIPAddress.SetAddress(0, 0, 0, 0);
//	ctrl_Port = "Test";
//
//
//	return 0;
//}


void DlgCreateServer::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();

	
}


BOOL DlgCreateServer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
