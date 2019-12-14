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

ChessPiece* Chess::ChessPiece::CopyChessPiece()
{
	return new ChessPiece(type,team);
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

void Chess::Knight::Movement(ChessGame& cg, CPoint ptChessPiece)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();

	CPoint ptMove[8]= {
		{2,1},{-2,1},{2,-1},{-2,-1},
		{1,2},{-1,2},{1,-2},{-1,-2}
	};

	ChessBlock* ptTmp = nullptr;

	for (int i = 0; i < 8; i++) {
		ptTmp = cg.GetChessBlock(ptChessPiece + ptMove[i]);
		if (ptTmp == nullptr)
			continue;

		ptTmp->SetMove(tteam, 1);
	}
}

ChessPiece* Chess::Knight::CopyChessPiece()
{
	return new Knight(ChessPiece::GetType(), ChessPiece::GetTeam());
}

Pawn::Pawn(int type, int team) : ChessPiece(type,team)
{
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

	for (int i = -1; i <= 1; i += 2) {
		ptTmp = cg.GetChessBlock(CPoint(Foward(ptChessPiece.x,i,0), Foward(ptChessPiece.y, 1, tteam)));
		if (ptTmp == nullptr)
			continue;

		if (ptTmp->IsHaveChessPiece() == true)
			ptTmp->SetMove(tteam, 1);
	}
}

ChessPiece* Chess::Pawn::CopyChessPiece()
{
	return new Pawn(ChessPiece::GetType(),ChessPiece::GetTeam());
}
