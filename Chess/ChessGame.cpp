#include "pch.h"
#include "ChessGame.h"
#include "DlgPawnPromotion.h"

#include "MainFrm.h"
#include "ChildView.h"

using namespace Chess;

ChessBlock* Chess::ChessGame::GetChessBlock(CPoint pt)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (!IsRightPoint(pt))
		return nullptr;
	
	return Board[pt.y][pt.x].get();
}


void Chess::ChessGame::ClearAllMove()
{
	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			Board[iy][ix]->ClearMove();
		}
	}
}

void Chess::ChessGame::ClearAllCheck()
{
	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			Board[iy][ix]->SetCheck(false);
		}
	}
}

bool Chess::ChessGame::IsCheck(int team)
{
	ClearAllCheck();

	CPoint ptIndex(0, 0);
	for (ptIndex.y = 0; ptIndex.y < BLOCK_COUNT; ptIndex.y++) {
		for (ptIndex.x = 0; ptIndex.x < BLOCK_COUNT; ptIndex.x++) {
			ChessBlock* ptCB = GetChessBlock(ptIndex);

			if (ptCB == nullptr)
				continue;

			if (ptCB->GetChessPieceTeam() == team)
				continue;

			ptCB->MovementChessPiece(true);
		}
	}

	for (ptIndex.y = 0; ptIndex.y < BLOCK_COUNT; ptIndex.y++) {
		for (ptIndex.x = 0; ptIndex.x < BLOCK_COUNT; ptIndex.x++) {
			ChessBlock* ptCB = GetChessBlock(ptIndex);
			if (ptCB == nullptr)
				continue;
			
			if (ptCB->GetChessPieceTeam() != team)
				continue;

			if (ptCB->GetChessPieceType() == PIECE_KING && ptCB->GetCheck())
				return true;
			
		}
	}

	return false;
}

bool Chess::ChessGame::IsCheckMate(int team)
{
	CChildView* ptView = ((CMainFrame*)AfxGetMainWnd())->GetView();

	ClearAllMove();
	CPoint ptIndex(0, 0);
	for (ptIndex.y = 0; ptIndex.y < BLOCK_COUNT; ptIndex.y++) {
		for (ptIndex.x = 0; ptIndex.x < BLOCK_COUNT; ptIndex.x++) {
			ChessBlock* ptCB = GetChessBlock(ptIndex);

			if (ptCB == nullptr)
				continue;

			if (ptCB->GetChessPieceTeam() != team)
				continue;

			ptCB->MovementChessPiece(false);
		}
	}

	for (ptIndex.y = 0; ptIndex.y < BLOCK_COUNT; ptIndex.y++) {
		for (ptIndex.x = 0; ptIndex.x < BLOCK_COUNT; ptIndex.x++) {
			ChessBlock* ptCB = GetChessBlock(ptIndex);
			if (ptCB == nullptr)
				continue;

			if (ptCB->GetMove()) 
				return false;
			
		}
	}
	
	return true;
}


bool Chess::ChessGame::IsRightPoint(CPoint pt) const
{
	if ((pt.x >= 0 && pt.x < BLOCK_COUNT) && (pt.y >= 0 && pt.y < BLOCK_COUNT))
		return true;

	return false;
}

bool Chess::ChessGame::CreateServer(int Port)
{
	ptServer = make_unique<CChessServer>();
	if (ptServer->Create(Port, SOCK_STREAM) == false) {
		CloseServer();
		return true;
	}

	if (ptServer->Listen() == false) {
		CloseServer();
		return true;
	}

	return false;
}

bool Chess::ChessGame::IsServerOpen()
{
	return (bool)ptServer;
}

void Chess::ChessGame::CloseServer()
{
	if ((bool)ptServer) {
		CloseClient();
		ptServer->ShutDown();
		ptServer->Close();
		ptServer.release();
	}
}

bool Chess::ChessGame::ConnectClient(CString& IPAddress, int Port)
{
	ptClinet = make_unique<CChessClient>();

	ptClinet->Create(0, SOCK_STREAM);

	if (ptClinet->Connect(IPAddress.GetString(), Port)) {
		return true;
	}
	else {
		CloseClient();
		return false;
	}
}

bool Chess::ChessGame::AcceptClient()
{
	if ((bool)ptServer == false)
		return true;

	ptClinet = make_unique<CChessClient>();
	return ptServer->Accept(*ptClinet);
}

bool Chess::ChessGame::IsClientOpen()
{
	return (bool)this->ptClinet;
}

void Chess::ChessGame::CloseClient()
{
	if ((bool)this->ptClinet) {
		ptClinet->ShutDown();
		ptClinet->Close();
		ptClinet.release();
	}
}

bool Chess::ChessGame::SendCommand(CString Command)
{
	if(IsClientOpen() == false)
		return false;

	ptClinet->Send(Command.GetBuffer(), Command.GetLength() * 2);
	ptClinet->Send("/", 2);
	return true;
}

void Chess::ChessGame::HandleComand(CString Command)
{
	int curPos = 0;
	CString resToken;
	vector<CString> arguments;

	resToken = Command.Tokenize(_T(" "), curPos);
	while (resToken != _T("")) {
		arguments.emplace_back(resToken);
		resToken = Command.Tokenize(_T(" "), curPos);
	}

	SetCheckMove(true);

	if (arguments[0] == _T("DELETE")) {
		DeleteChessPiece(CPoint(_wtoi(arguments[1]), _wtoi(arguments[2])));
	}
	else if (arguments[0] == _T("ADD")) {
		AddChessPiece(CPoint(_wtoi(arguments[1]), _wtoi(arguments[2])), _wtoi(arguments[3]), _wtoi(arguments[4]));
	}
	else if (arguments[0] == _T("RESTART")) {
		EndGame();
		StartGame();
	}
	else if (arguments[0] == _T("ENDTURN")) {
		turn = !turn;
	}

	SetCheckMove(false);
}

bool Chess::ChessGame::GetCheckMove()
{
	return bCheckMove;
}

void Chess::ChessGame::SetCheckMove(bool bValue)
{
	bCheckMove = bValue;
}

int Chess::ChessGame::GetTurn()
{
	return turn;
}

int Chess::ChessGame::GetPlayerTurn()
{
	return PlayerTurn;
}

ChessGame::ChessGame(CPoint sp) : ptStart(sp), iBlockSize(50), bMove(false), turn(0), bEnPassant(false), bCheckMove(false)
								, PlayerTurn(0)
{
	for (int i = 0; i < 2; i++) 
		for(int i1 = 0;i1 < PIECE_COUNT;i1++)
			this->bmChessPieces[i][i1].LoadBitmapW(IDB_KING_WHITE + (i * 10) + i1);

	CPoint ptIndex(0, 0);
	for (ptIndex.y = 0; ptIndex.y < BLOCK_COUNT; ptIndex.y++) {
		for (ptIndex.x = 0; ptIndex.x < BLOCK_COUNT; ptIndex.x++) {
			Board[ptIndex.y][ptIndex.x] = make_unique<ChessBlock>(this, ptIndex);
		}
	}
}

ChessGame::~ChessGame() {

}

void ChessGame::PaintChessBoard(CPaintDC& dc)
{
	CBrush bsBlockColor[5];
	CBrush* bsOld;
	CPoint ptSize = { iBlockSize,iBlockSize };
	bool bBoard = false;

	bsBlockColor[0].CreateSolidBrush(RGB(200, 200, 200));
	bsBlockColor[1].CreateSolidBrush(RGB(255, 255, 255));
	bsBlockColor[2].CreateSolidBrush(RGB(0, 255, 0));
	bsBlockColor[3].CreateSolidBrush(RGB(100, 190, 240));
	bsBlockColor[4].CreateSolidBrush(RGB(150, 100, 255));

	bsOld = (CBrush*)dc.SelectObject(&bsBlockColor[0]);

	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			ChessBlock& rfCB = *GetChessBlock(CPoint(ix, iy));
			if (rfCB.GetMove() == 1 && bMove == true)
				dc.SelectObject(&bsBlockColor[2]);
			else if (rfCB.GetMove() == 2 && bMove == true)
				dc.SelectObject(&bsBlockColor[4]);
			else if(rfCB.GetMove() == 3 && bMove == true)
				dc.SelectObject(&bsBlockColor[3]);
			else if (bBoard)
				dc.SelectObject(&bsBlockColor[0]);
			else
				dc.SelectObject(&bsBlockColor[1]);


			CPoint ptTemp = CPoint(ix * iBlockSize, iy * iBlockSize) + ptStart;

			dc.Rectangle(CRect(ptTemp, ptTemp + ptSize));

			bBoard = !bBoard;
		}
		bBoard = !bBoard;
	}

	dc.SelectObject(*bsOld);
}

void Chess::ChessGame::PaintChessPiece(CPaintDC& dc, CPoint pt) 
{
	CBitmap* btOld;
	CDC memDC;
	ChessBlock& rfCB = *Board[pt.y][pt.x];

	if (rfCB.IsHaveChessPiece() == false)
		return;

	memDC.CreateCompatibleDC(&dc);
	btOld = (CBitmap*)memDC.SelectObject(&bmChessPieces[rfCB.GetChessPieceTeam()][rfCB.GetChessPieceType()]);

	dc.TransparentBlt(ptStart.x + (pt.x * 50), ptStart.y + ( pt.y * 50), 50, 50,&memDC, 0, 0, 100, 100, RGB(255, 255, 255));

	memDC.SelectObject(btOld);
}

void Chess::ChessGame::PaintChessPieces(CPaintDC& dc)
{
	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			PaintChessPiece(dc, CPoint(ix, iy));
		}
	}
}


void ChessGame::StartGame()
{
	int CPprocedure[BLOCK_COUNT] = { 2,4,3,1,0,3,4,2 };
	for (int i = 0; i < BLOCK_COUNT; i++) {
		AddChessPiece(CPoint(i, 0), CPprocedure[i], 1);
		AddChessPiece(CPoint(i, 7), CPprocedure[i], 0);
		AddChessPiece(CPoint(i, 1), PIECE_PAWN, 1);
		AddChessPiece(CPoint(i, 6), PIECE_PAWN, 0);
	}

	turn = TEAM_WHITE;
}

void Chess::ChessGame::EndGame()
{
	CPoint cpTmp(0, 0);

	for (cpTmp.y = 0; cpTmp.y < BLOCK_COUNT; cpTmp.y++) {
		for (cpTmp.x = 0; cpTmp.x < BLOCK_COUNT; cpTmp.x++) {
			GetChessBlock(cpTmp)->DeleteChessPiece();
		}
	}
}

void ChessGame::ChessBoardMessage(CPoint ptCursor)
{
	ptCursor -= ptStart;

	ptCursor.x /= iBlockSize;
	ptCursor.y /= iBlockSize;

	if (ptCursor.x < 0 || ptCursor.x >= BLOCK_COUNT
		|| ptCursor.y < 0 || ptCursor.y >= BLOCK_COUNT)
		return;

	ChessBlock& rfCB = *GetChessBlock(ptCursor);

	if (bMove == false) {
		if (rfCB.IsHaveChessPiece() == false)
			return;

		this->ptSelect = ptCursor;

		if (turn != GetChessBlock(ptSelect)->GetChessPieceTeam())
			return;

		IsCheck(GetChessBlock(ptSelect)->GetChessPieceTeam());

		rfCB.MovementChessPiece(false);

		CPoint cpTmp(0, 0);

		for (cpTmp.y = 0; cpTmp.y < BLOCK_COUNT;cpTmp.y++) {
			for (cpTmp.x = 0; cpTmp.x < BLOCK_COUNT;cpTmp.x++) {
				if (GetChessBlock(cpTmp)->GetMove() == 1) {
					rfCB.SetMove(3);
					bMove = true;
					return;
				}
			}
		}
	}

	else {
		if (ptCursor == ptSelect) {
			ClearAllMove();
			bMove = false;
		}

		if (rfCB.GetMove() == 0)
			return;

		GetChessBlock(ptSelect)->MoveChessPiece(ptCursor);

		ChessBlock* cbTmp = GetChessBlock(ptCursor);

		//pawn promotion
		if (cbTmp->GetChessPieceType() == PIECE_PAWN && (ptCursor.y == 0 || ptCursor.y == 7)) {
			DlgPawnPromotion DlgPromotion;
			int iDlgResult = DlgPromotion.DoModal();
			int tteam = cbTmp->GetChessPieceTeam();

			cbTmp->DeleteChessPiece();
			cbTmp->AddChessPiece(iDlgResult, tteam);
		}

		//king castling
		if (cbTmp->GetChessPieceType() == PIECE_KING && cbTmp->GetMove() == 2) {
			CPoint ptCastling(ptCursor.x == 6? 7 : 0, ptCursor.y);

			GetChessBlock(ptCastling)->MoveChessPiece(ptCastling + CPoint(ptCastling.x == 7 ? -2 : 3, 0));
		}

		IdentifyEnPassant(ptCursor, this->ptSelect);

		if (IsCheckMate(!GetChessBlock(ptCursor)->GetChessPieceTeam()))
			AfxMessageBox(_T("CheckMate!!"));
		else if (IsCheck(!GetChessBlock(ptCursor)->GetChessPieceTeam()))
			AfxMessageBox(_T("Check!!"));

		ClearAllMove();
		SendCommand(_T("ENDTURN"));
		bMove = false;
		turn = !turn;
	}

}

void Chess::ChessGame::IdentifyEnPassant(CPoint cpTo, CPoint cpFrom)
{
	if (bEnPassant == true && GetChessBlock(cpTo)->GetMove() == 2) {
		ChessBlock* ptCB = GetChessBlock(CPoint(cpTo.x,cpFrom.y));
		ptCB->DeleteChessPiece();
	}

	bEnPassant = false;

	if (GetChessBlock(cpTo)->GetChessPieceType() != PIECE_PAWN)
		return;

	if (abs(cpTo.y - cpFrom.y) != 2)
		return;

	for (int i = -1; i <= 1; i += 2) {
		ChessBlock* ptCB = GetChessBlock(cpTo + CPoint(i, 0));
		if (ptCB == nullptr)
			continue;
		
		if(ptCB->GetChessPieceTeam() != GetChessBlock(cpTo)->GetChessPieceTeam() &&
			ptCB->GetChessPieceType() == PIECE_PAWN)
			bEnPassant = true;
	}
}

bool Chess::ChessGame::GetEnPassant()
{
	return bEnPassant;
}

bool ChessGame::AddChessPiece(CPoint pt, int type, int team)
{
	Board[pt.y][pt.x]->AddChessPiece(type, team);
	return false;
}

void Chess::ChessGame::DeleteChessPiece(CPoint pt)
{
	Board[pt.y][pt.x]->DeleteChessPiece();
}

CPoint Chess::ChessGame::GetSelectedPoint()
{
	return ptSelect;
}
