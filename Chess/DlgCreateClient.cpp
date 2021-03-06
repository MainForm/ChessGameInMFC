﻿// DlgCreateClient.cpp: 구현 파일
//

#include "pch.h"
#include "Chess.h"
#include "DlgCreateClient.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildView.h"

// DlgCreateClient 대화 상자

IMPLEMENT_DYNAMIC(DlgCreateClient, CDialog)

DlgCreateClient::DlgCreateClient(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CREATECLIENT, pParent)
	, ctrl_Port(_T(""))
{

}

DlgCreateClient::~DlgCreateClient()
{
}

void DlgCreateClient::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ctrl_Port);
	DDX_Control(pDX, IDC_IPADDRESS1, ctrl_IPAddress);
}


BEGIN_MESSAGE_MAP(DlgCreateClient, CDialog)
	ON_BN_CLICKED(IDOK, &DlgCreateClient::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgCreateClient 메시지 처리기


BOOL DlgCreateClient::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	ctrl_IPAddress.SetAddress(127, 0, 0, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void DlgCreateClient::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialog::OnOK();
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();

	BYTE fields[4];
	CString IPAddress;

	UpdateData();

	ctrl_IPAddress.GetAddress(fields[0], fields[1], fields[2], fields[3]);

	IPAddress.Format(_T("%d.%d.%d.%d"), fields[0], fields[1], fields[2], fields[3]);

	EndDialog(ptView->Chess->ConnectClient(IPAddress, _wtoi(ctrl_Port)));
}
