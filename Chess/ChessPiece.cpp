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

King::King(int type, int team) : ChessPiece(type,team)
{
}


Queen::Queen(int type, int team) : ChessPiece(type,team)
{
}


Rook::Rook(int type, int team) : ChessPiece(type,team)
{
}

Bishop::Bishop(int type, int team) : ChessPiece(type,team)
{
}


Knight::Knight(int type, int team) : ChessPiece(type,team)
{
}

Pawn::Pawn(int type, int team) : ChessPiece(type,team)
{
}