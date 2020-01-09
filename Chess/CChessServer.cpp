// CChessServer.cpp: 구현 파일
//

#include "pch.h"
#include "Chess.h"
#include "CChessServer.h"

#include "MainFrm.h"
#include "ChildView.h"

// CChessServer

CChessServer::CChessServer()
{

}

CChessServer::~CChessServer()
{

}


// CChessServer 멤버 함수


void CChessServer::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();
	
	if (!ptView->Chess->AcceptClient()) {
		ptView->Chess->CloseClient();
		AfxMessageBox(_T("Failed to Connect with Client!"));
	}

	ptView->Chess->SendCommand(_T("RESTART"));
	ptView->Chess->HandleComand(_T("RESTART"));

	ptView->Invalidate();

	AfxMessageBox(_T("New Chellenger!"));
	
	CSocket::OnAccept(nErrorCode);
}
