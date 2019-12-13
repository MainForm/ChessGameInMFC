#include "pch.h"
#include "ChessPiece.h"
#include "ChessGame.h"

using namespace Chess;

ChessPiece::ChessPiece(int type,int team) : type(type),team(team)
{

}

int Chess::ChessPiece::GetType() const
{
	return this->type;
}

int Chess::ChessPiece::GetTeam() const
{
	return this->team;
}

void Chess::ChessPiece::Movement(ChessGame& cg)
{
}

ChessPiece Chess::ChessPiece::ReturnType()
{
	return *this;
}

King::King(int type, int team) : ChessPiece(type,team)
{
}

King Chess::King::ReturnType()
{
	return *this;
}


Queen::Queen(int type, int team) : ChessPiece(type,team)
{
}

Queen Chess::Queen::ReturnType()
{
	return *this;
}


Rook::Rook(int type, int team) : ChessPiece(type,team)
{
}

Rook Chess::Rook::ReturnType()
{
	return *this;
}

Bishop::Bishop(int type, int team) : ChessPiece(type,team)
{
}

Bishop Chess::Bishop::ReturnType()
{
	return *this;
}


Knight::Knight(int type, int team) : ChessPiece(type,team)
{
}

Knight Chess::Knight::ReturnType()
{
	return *this;
}

Pawn::Pawn(int type, int team) : ChessPiece(type,team)
{
}

Pawn Chess::Pawn::ReturnType()
{
	return *this;
}
