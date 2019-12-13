#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:
		bool bMoveable[2];
		std::unique_ptr<ChessPiece> cp;
	public:
		ChessBlock();
		ChessBlock(ChessBlock& cb);
		int GetChessPieceType() const;
		int GetChessPieceTeam() const;

		bool IsHaveChessPiece() const;

		bool AddChessPiece(int type,int team);
		void DeleteChessPiece();

		void SetMove(int team);

		ChessBlock operator=(ChessBlock& cb);
	};

}