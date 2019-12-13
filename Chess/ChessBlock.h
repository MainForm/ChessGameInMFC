#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:
		int Moveable[2];
		std::unique_ptr<ChessPiece> cp;
		bool bCheck;
	public:
		ChessBlock();
		ChessBlock(ChessBlock& cb);
		int GetChessPieceType() const;
		int GetChessPieceTeam() const;

		bool IsHaveChessPiece() const;

		bool AddChessPiece(int type,int team);
		void DeleteChessPiece();

		bool CompareChessPiece(ChessPiece* cp);

		void SetMove(int team,int value);
		int GetMove(int team) const;
		void ClearMove();

		void MovementChessPiece(ChessGame& cg, CPoint ptChessPiece);

		ChessBlock operator=(ChessBlock& cb);
	};

}