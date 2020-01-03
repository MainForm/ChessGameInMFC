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
{

}

DlgCreateServer::~DlgCreateServer()
{
}

void DlgCreateServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgCreateServer, CDialog)
END_MESSAGE_MAP()


// DlgCreateServer 메시지 처리기
