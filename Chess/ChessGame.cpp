#include "pch.h"
#include "ChessGame.h"

using namespace Chess;

ChessGame::ChessGame(CPoint sp) : ptStart(sp), iBlockSize(50)
{

}

void ChessGame::PaintChessBoard(CPaintDC& dc)
{
	CBrush bsBlockColor[2];
	CBrush* bsOld;
	CPoint ptSize = { iBlockSize,iBlockSize };
	bool bBoard = false;

	bsBlockColor[0].CreateSolidBrush(RGB(200, 200, 200));
	bsBlockColor[1].CreateSolidBrush(RGB(255, 255, 255));

	bsOld = (CBrush*)dc.SelectObject(&bsBlockColor[0]);

	for (int iy = 0; iy < BLOCK_COUNT; iy++) {
		for (int ix = 0; ix < BLOCK_COUNT; ix++) {
			if (bBoard)
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

void ChessGame::ChessBoardMessage(CPoint ptCursor)
{
	ptCursor -= ptStart;

	ptCursor.x /= iBlockSize;
	ptCursor.y /= iBlockSize;

	if (ptCursor.x < 0 || ptCursor.x >= BLOCK_COUNT
		|| ptCursor.y < 0 || ptCursor.y >= BLOCK_COUNT)
		return;

	CString Msg;

	Msg.Format(_T("%d , %d"), ptCursor.x, ptCursor.y);

	MessageBox(NULL, Msg, _T("Test"), MB_OK);

}

bool ChessGame::AddChessPiece(CPoint pt, int type, int team)
{
	
	return false;
}
