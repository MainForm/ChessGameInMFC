#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:
		ChessGame* ptCG;
		const CPoint cpPos;
		int Moveable;
		std::unique_ptr<ChessPiece> cp;
		bool bCheck;
	public:
		ChessBlock(ChessGame* cg, CPoint pt);
		ChessBlock(ChessBlock& cb);
		int GetChessPieceType() const;
		int GetChessPieceTeam() const;
		ChessGame* GetGame() const;
		CPoint GetPos() const;

		bool IsHaveChessPiece() const;

		bool AddChessPiece(int type,int team);
		void DeleteChessPiece();
		bool MoveChessPiece(CPoint cpTo);

		bool CompareChessPiece(ChessPiece* cp);

		void SetMove(int value);
		void SetCheck(int value);
		int GetMove() const;
		bool GetCheck() const;

		void ClearMove();

		void SetChessGame(ChessGame* ptCG);

		void MovementChessPiece(bool bChecking);
	};

}