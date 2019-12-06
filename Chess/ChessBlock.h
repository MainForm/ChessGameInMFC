#pragma once

#include <memory>

#include "ChessPiece.h"

namespace Chess {

	class ChessBlock
	{
	private:

		std::unique_ptr<ChessPiece> cp;
	public:
		ChessBlock();

		template <class ChessType>
		bool GetChessPiece(int team);
	};
}
