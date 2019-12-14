#pragma once

#include "ChessBlock.h"
#include "ChessPiece.h"
#include "Resource.h"

namespace Chess {

	class ChessGame
	{
	private:
		static const int BLOCK_COUNT = 8;
		ChessBlock Board[BLOCK_COUNT][BLOCK_COUNT];

		CBitmap bmChessPieces[2][PIECE_COUNT];
		CPoint ptStart;
		CPoint ptSelect;
		int iBlockSize;
		bool bMove;
		int turn;
	public:
		ChessGame(CPoint sp = { 0,0 });
		void PaintChessPiece(CPaintDC& dc, CPoint pt);
		void PaintChessPieces(CPaintDC& dc);
		void PaintChessBoard(CPaintDC& dc);

		void StartGame();
		void ChessBoardMessage(CPoint ptCursor);
		void MoveChessPiece(CPoint ptTo, CPoint ptFrom);

		bool AddChessPiece(CPoint pt,int type,int team);

		CPoint GetSelectedPoint();

		ChessBlock* GetChessBlock(CPoint pt);
		void ClearAllMove();
		void ClearAllCheck();

		bool IsCheck(int team);

		bool IsRightPoint(CPoint pt) const;
		virtual ~ChessGame();
	};
}