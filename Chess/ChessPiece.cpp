#include "pch.h"
#include "ChessPiece.h"
#include "ChessGame.h"

using namespace Chess;


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

void Chess::ChessPiece::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
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
	return nullptr;
}


King::King(int type, int team) : ChessPiece(type,team)
{
}

void Chess::King::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();

	CPoint ptMove[8] = {
		{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
	};

	ChessBlock* ptTmp = nullptr;

	for (int i = 0; i < 8; i++) {
		ptTmp = cg.GetChessBlock(ptChessPiece + ptMove[i]);
		if (ptTmp == nullptr)
			continue;

		(ptTmp->*Func)(tteam, 1);
	}
}

ChessPiece* Chess::King::CopyChessPiece()
{
	return new King(ChessPiece::GetType(), ChessPiece::GetTeam());
}


Queen::Queen(int type, int team) : ChessPiece(type,team)
{

}

void Chess::Queen::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();

	CPoint ptMove[8] = {
		{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}
	};

	ChessBlock* ptTmp = nullptr;

	for (int i = 0; i < 8; i++) {
		for (CPoint ptIndex = ptChessPiece + ptMove[i]; cg.IsRightPoint(ptIndex); ptIndex += ptMove[i]) {
			ptTmp = cg.GetChessBlock(ptIndex);
			if (ptTmp == nullptr)
				break;

			(ptTmp->*Func)(tteam, 1);

			if (ptTmp->IsHaveChessPiece() == true)
				break;
		}
	}
}

ChessPiece* Chess::Queen::CopyChessPiece()
{
	return new Queen(ChessPiece::GetType(), ChessPiece::GetTeam());
}

Rook::Rook(int type, int team) : ChessPiece(type,team)
{

}

void Chess::Rook::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();

	CPoint ptMove[4] = {
		{1,0},{-1,0},{0,1},{0,-1}
	};

	ChessBlock* ptTmp = nullptr;

	for (int i = 0; i < 4; i++) {
		for (CPoint ptIndex = ptChessPiece + ptMove[i]; cg.IsRightPoint(ptIndex); ptIndex += ptMove[i]) {
			ptTmp = cg.GetChessBlock(ptIndex);
			if (ptTmp == nullptr)
				break;

			(ptTmp->*Func)(tteam, 1);

			if (ptTmp->IsHaveChessPiece() == true)
				break;
		}
	}
}

ChessPiece* Chess::Rook::CopyChessPiece()
{
	return new Rook(ChessPiece::GetType(), ChessPiece::GetTeam());
}

Bishop::Bishop(int type, int team) : ChessPiece(type,team)
{

}

void Chess::Bishop::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
{
	ChessBlock* cb = cg.GetChessBlock(ptChessPiece);

	if (cb == nullptr)
		return;

	if (cb->CompareChessPiece(this) == false)
		return;

	ChessBlock& rfCB = *cg.GetChessBlock(ptChessPiece);

	int tteam = ChessPiece::GetTeam();
	int tvalue = ChessPiece::GetType();

	CPoint ptMove[4] = { 
		{1,1},{1,-1},{-1,1},{-1,-1}
	};

	ChessBlock* ptTmp = nullptr;

	for (int i = 0; i < 4; i++) {
		for (CPoint ptIndex = ptChessPiece + ptMove[i]; cg.IsRightPoint(ptIndex); ptIndex += ptMove[i]) {
			ptTmp = cg.GetChessBlock(ptIndex);
			if (ptTmp == nullptr)
				break;

			(ptTmp->*Func)(tteam, 1);

			if (ptTmp->IsHaveChessPiece() == true)
				break;
		}
	}
}

ChessPiece* Chess::Bishop::CopyChessPiece()
{
	return new Bishop(ChessPiece::GetType(), ChessPiece::GetTeam());
}


Knight::Knight(int type, int team) : ChessPiece(type,team)
{
}

void Chess::Knight::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
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

		(ptTmp->*Func)(tteam, 1);
	}
}

ChessPiece* Chess::Knight::CopyChessPiece()
{
	return new Knight(ChessPiece::GetType(), ChessPiece::GetTeam());
}

Pawn::Pawn(int type, int team) : ChessPiece(type,team)
{
}

void Chess::Pawn::Movement(ChessGame& cg, CPoint ptChessPiece, SetFunc Func)
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
	
	if(ptTmp != nullptr &&ptTmp->IsHaveChessPiece() == false)
		(ptTmp->*Func)(tteam, 1);
	
	
	ptTmp = cg.GetChessBlock(CPoint(ptChessPiece.x, Foward(ptChessPiece.y, 2, tteam)));

	if (ptTmp != nullptr && (ptChessPiece.y == 1 || ptChessPiece.y == 6) && ptTmp->IsHaveChessPiece() == false)
		(ptTmp->*Func)(tteam, 1);
	

	for (int i = -1; i <= 1; i += 2) {
		ptTmp = cg.GetChessBlock(CPoint(Foward(ptChessPiece.x,i,0), Foward(ptChessPiece.y, 1, tteam)));
		if (ptTmp == nullptr)
			continue;

		if (ptTmp->IsHaveChessPiece() == true)
			(ptTmp->*Func)(tteam, 1);
	}
}

ChessPiece* Chess::Pawn::CopyChessPiece()
{
	return new Pawn(ChessPiece::GetType(),ChessPiece::GetTeam());
}
