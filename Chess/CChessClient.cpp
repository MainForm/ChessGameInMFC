// CChessClient.cpp: 구현 파일
//

#include "pch.h"
#include "Chess.h"
#include "CChessClient.h"

#include "MainFrm.h"
#include "ChildView.h"

// CChessClient

CChessClient::CChessClient()
{

}

CChessClient::~CChessClient()
{

}


// CChessClient 멤버 함수


void CChessClient::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();

	ptView->Chess->CloseClient();

	ptView->Invalidate();

	CSocket::OnClose(nErrorCode);
}


void CChessClient::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	TCHAR szReceived[1024] = _T("");
	CString Commands;
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();

	if (Receive(szReceived, sizeof(szReceived)) > 0) {
		Commands = szReceived;
		int curPos = 0;
		CString cmd;

		cmd = Commands.Tokenize(_T("/"), curPos);
		while (cmd != _T("")) {
			ptView->Chess->HandleComand(cmd);
			cmd = Commands.Tokenize(_T("/"), curPos);
		}
	}

	ptView->Invalidate();

	CSocket::OnReceive(nErrorCode);
}
