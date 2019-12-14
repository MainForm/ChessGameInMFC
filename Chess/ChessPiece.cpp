#include "pch.h"
#include "ChessPiece.h"
#include "ChessGame.h"

using namespace Chess;

int Chess::ChessPiece::Foward(int Num,int add, int team)
{
	if (team == 0)
		Num -= add;
	else
		Num += add;

	return Num;
}

ChessPiece::ChessPiece(int type,int team) : type(type),team(team)
{

}

int Chess::ChessPiece::GetType() const
{
	if (this == nullptr)
		return -1;

	return this->type;
}

int Chess::ChessPiece::GetTeam() const
{
	if (this == nullptr)
		return -1;

	return this->team;
}

void Chess::ChessPiece::Movement(ChessGame& cg, CPoint ptChessPiece)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	cb->SetMove(this->team,1);
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

void Chess::Pawn::Movement(ChessGame& cg, CPoint ptChessPiece)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();
	
	ChessBlock* ptTmp = cg.GetChessBlock(CPoint(ptChessPiece.x, Foward(ptChessPiece.y, 1, tteam)));
	
	if(ptTmp->IsHaveChessPiece() == false)
		ptTmp->SetMove(tteam, 1);

	ptTmp = cg.GetChessBlock(CPoint(ptChessPiece.x, Foward(ptChessPiece.y, 2, tteam)));

	if ((ptChessPiece.y == 1 || ptChessPiece.y == 6) && ptTmp->IsHaveChessPiece() == false)
		ptTmp->SetMove(tteam, 1);

}
