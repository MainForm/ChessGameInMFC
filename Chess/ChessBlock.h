#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:
		ChessGame* ptCG;
		int Moveable[2];
		std::unique_ptr<ChessPiece> cp;
		bool bCheck;

		friend ChessGame;
	public:
		ChessBlock(ChessGame* cg = nullptr);
		ChessBlock(ChessBlock& cb);
		int GetChessPieceType() const;
		int GetChessPieceTeam() const;

		bool IsHaveChessPiece() const;

		bool AddChessPiece(int type,int team);
		void DeleteChessPiece();

		bool CompareChessPiece(ChessPiece* cp);

		void SetMove(int team,int value);
		void SetCheck(int team,int value);
		int GetMove(int team) const;
		bool GetCheck() const;

		void ClearMove();

		void SetChessGame(ChessGame* ptCG);

		void MovementChessPiece(ChessGame& cg, CPoint ptChessPiece,bool bChecking);

		ChessBlock operator=(ChessBlock& cb);
	};

}