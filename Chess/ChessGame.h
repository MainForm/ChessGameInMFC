#pragma once

class ChessGame
{
private:
	CPoint ptStart;
	int iBlockSize;
	static const int BLOCK_COUNT = 8;
public:
	ChessGame(CPoint sp = { 0,0 });
	void PaintChessBoard(CPaintDC & dc);
	void ChessBoardMessage(CPoint ptCursor);
};