﻿
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Chess.h"
#include "ChildView.h"

#include "DlgCreateServer.h"
#include "DlgCreateClient.h"

#include "MainFrm.h"
#include "ChessPiece.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_RESTART, &CChildView::OnRestart)
	ON_COMMAND(ID_SERVER_MAKE, &CChildView::OnServerCreate)
	ON_COMMAND(ID_SERVER_CONNECT, &CChildView::OnCreateClient)
END_MESSAGE_MAP()

// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.

	this->Chess->PaintChessBoard(dc);
	this->Chess->PaintChessPieces(dc);
	
	CString TurnMsg = _T("Turn : ");

	if (Chess->IsClientOpen()) {
		dc.TextOutW(450, 10, _T("Playing with other player."));
	}
	else if (Chess->IsServerOpen()) {
		dc.TextOutW(450, 10, _T("Waiting other player...."));
	}

	if (Chess->GetTurn() == Chess::TEAM_WHITE) {
		TurnMsg += _T("White");
	}
	else {
		TurnMsg += _T("Black");
	}
	dc.TextOutW(450, 30, TurnMsg);
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonDown(nFlags, point);

	this->Chess->ChessBoardMessage(point);

	this->Invalidate();
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	this->Chess = std::make_unique<Chess::ChessGame>(CPoint(10, 10));
	this->Chess->StartGame();
	return 0;
}


void CChildView::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	Chess->CloseServer();
}


void CChildView::OnRestart()
{
	this->Chess->EndGame();
	this->Chess->StartGame();
	Chess->SendCommand(_T("RESTART"));
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CChildView::OnServerCreate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DlgCreateServer dlgServer;
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();

	if (ptView->Chess->IsServerOpen()) {
		AfxMessageBox(_T("Server is already opened!"));
		return;
	}
	
	if (dlgServer.DoModal())
		AfxMessageBox(_T("Failed to create server"));

	Invalidate();
}

void CChildView::OnCreateClient()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	DlgCreateClient dlgClient;

	if (Chess->IsServerOpen()) {
		AfxMessageBox(_T("Server is already opened!"));
		return;
	}

	if (Chess->IsClientOpen()) {
		AfxMessageBox(_T("Client is already connected!"));
		return;
	}

	if (dlgClient.DoModal() == false)
		AfxMessageBox(_T("Failed to connect to server"));

	Invalidate();
}
