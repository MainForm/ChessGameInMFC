#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:
		CPoint ptPosition;
		bool Moveable[2];
		std::unique_ptr<ChessPiece> cp;
	public:
		ChessBlock();

		int GetChessPieceType() const;
		int GetChessPieceTeam() const;

		bool IsHaveChessPiece() const;

		bool AddChessPiece(int type,int team);

		void SetMove(int team);
	};

}