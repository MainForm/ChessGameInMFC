#include "pch.h"
#include "ChessBlock.h"

using namespace Chess;

ChessBlock::ChessBlock() : cp(nullptr)
{


}

int Chess::ChessBlock::GetChessPieceType() const
{
	if (this->cp == false)
		return -1;

	return this->cp->GetType();
}

int Chess::ChessBlock::GetChessPieceTeam() const
{
	if (this->cp == false)
		return -1;

	return this->cp->GetTeam();
}

bool Chess::ChessBlock::IsHaveChessPiece() const
{
	return (bool)this->cp;
}

bool ChessBlock::AddChessPiece(int type, int team)
{
	switch (type) {
	case PIECE_KING:
		this->cp = std::make_unique<King>(type,team);
		
		break;
	case PIECE_QUEEN:
		this->cp = std::make_unique<Queen>(type, team);
		break;
	case PIECE_ROOK:
		this->cp = std::make_unique<Rook>(type, team);
		break;
	case PIECE_BISHOP:
		this->cp = std::make_unique<Bishop>(type, team);
		break;
	case PIECE_KNIGHT:
		this->cp = std::make_unique<Knight>(type, team);
		break;
	case PIECE_PAWN:
		this->cp = std::make_unique<Pawn>(type, team);
		break;
	default:
		return false;
	}

	return true;
}


void Chess::ChessBlock::SetMove(int team)
{
	if(team != 0 && team != 1)
		return;
	Moveable[team] = true;
}
