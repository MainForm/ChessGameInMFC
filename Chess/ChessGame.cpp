#include "pch.h"
#include "ChessGame.h"

using namespace Chess;

ChessBlock* Chess::ChessGame::GetChessBlock(CPoint pt)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	if (!IsRightPoint(pt))
		return nullptr;
	
	return &Board[pt.y][pt.x];
}

void Chess::ChessGame::ClearAllMove()
{
	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			Board[iy][ix].ClearMove();
		}
	}
}

bool Chess::ChessGame::IsRightPoint(CPoint pt) const
{
	if ((pt.x >= 0 && pt.x < BLOCK_COUNT) && (pt.y >= 0 && pt.y < BLOCK_COUNT))
		return true;

	return false;
}

ChessGame::ChessGame(CPoint sp) : ptStart(sp), iBlockSize(50), bMove(false), turn(0)
{
	for (int i = 0; i < 2; i++) 
		for(int i1 = 0;i1 < PIECE_COUNT;i1++)
			this->bmChessPieces[i][i1].LoadBitmapW(IDB_KING_WHITE + (i * 10) + i1);

	
}

ChessGame::~ChessGame() {

}

void ChessGame::PaintChessBoard(CPaintDC& dc)
{
	CBrush bsBlockColor[3];
	CBrush* bsOld;
	CPoint ptSize = { iBlockSize,iBlockSize };
	bool bBoard = false;

	bsBlockColor[0].CreateSolidBrush(RGB(200, 200, 200));
	bsBlockColor[1].CreateSolidBrush(RGB(255, 255, 255));
	bsBlockColor[2].CreateSolidBrush(RGB(0, 255, 0));

	bsOld = (CBrush*)dc.SelectObject(&bsBlockColor[0]);

	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			ChessBlock& rfCB = *GetChessBlock(CPoint(ix, iy));
			if (rfCB.GetMove(GetChessBlock(ptSelect)->GetChessPieceTeam()) == 1 && bMove == true)
				dc.SelectObject(&bsBlockColor[2]);
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
	ChessBlock& rfCB = this->Board[pt.y][pt.x];

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

		rfCB.MovementChessPiece(*this, ptCursor);

		this->ptSelect = ptCursor;
		bMove = true;
	}
	else {
		if (rfCB.GetMove(GetChessBlock(ptSelect)->GetChessPieceTeam()) == 0)
			return;

		this->MoveChessPiece(ptCursor, ptSelect);

		ClearAllMove();
		bMove = false;
	}

}

void Chess::ChessGame::MoveChessPiece(CPoint ptTo, CPoint ptFrom)
{
	if (ptTo == ptFrom)
		return;

	Board[ptTo.y][ptTo.x] = Board[ptFrom.y][ptFrom.x];
	Board[ptFrom.y][ptFrom.x].DeleteChessPiece();
}

bool ChessGame::AddChessPiece(CPoint pt, int type, int team)
{
	Board[pt.y][pt.x].AddChessPiece(type, team);
	return false;
}

CPoint Chess::ChessGame::GetSelectedPoint()
{
	return ptSelect;
}
