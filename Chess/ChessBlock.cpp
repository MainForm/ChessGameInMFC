#include "pch.h"
#include "ChessBlock.h"

using namespace Chess;

ChessBlock::ChessBlock() : cp(nullptr)
{

}

template <class ChessType>
bool ChessBlock::GetChessPiece(int team)
{
	cp = std::make_unique<ChessType>(team);
	return false;
}
