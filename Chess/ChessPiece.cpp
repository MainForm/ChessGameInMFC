#include "pch.h"
#include "ChessPiece.h"

using namespace Chess;

ChessPiece::ChessPiece(int team) : team(team)
{

}

King::King(int team) : ChessPiece(team)
{

}


Pawn::Pawn(int team) : ChessPiece(team)
{

}