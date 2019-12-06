#pragma once

#include "ChessBlock.h"

namespace Chess {
	class ChessGame
	{
	private:
		static const int BLOCK_COUNT = 8;

		ChessBlock Board[BLOCK_COUNT][BLOCK_COUNT];
		CPoint ptStart;
		int iBlockSize;
	public:
		ChessGame(CPoint sp = { 0,0 });
		void PaintChessBoard(CPaintDC& dc);
		void ChessBoardMessage(CPoint ptCursor);
		bool AddChessPiece(CPoint pt, int type, int team);
		virtual ~ChessGame();
	};
}