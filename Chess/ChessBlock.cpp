#include "pch.h"
#include "ChessGame.h"
#include "ChessBlock.h"

using namespace Chess;

ChessBlock::ChessBlock(ChessGame* cg,CPoint pt) : cp(nullptr),ptCG(cg),cpPos(pt)
{
	ZeroMemory(Moveable, sizeof(Moveable));
}

ChessBlock::ChessBlock(ChessBlock& cb) : cp(nullptr),ptCG(cb.ptCG)
{
	if(cb.cp != nullptr)
		cp.reset(cb.cp->CopyChessPiece());
	ZeroMemory(Moveable, sizeof(Moveable));
}

int Chess::ChessBlock::GetChessPieceType() const
{
	if (this->cp == false)
		return -1;

	return this->cp->GetType();
}

int Chess::ChessBlock::GetChessPieceTeam() const
{
	if (cp.get() == nullptr)
		return -1;

	return this->cp->GetTeam();
}

bool Chess::ChessBlock::IsHaveChessPiece() const
{
	if (cp.get() == nullptr)
		return false;
	else
		return true;
}

bool ChessBlock::AddChessPiece(int type, int team)
{
	switch (type) {
	case PIECE_KING:
		this->cp = std::make_unique<King>(this,type,team);
		
		break;
	case PIECE_QUEEN:
		this->cp = std::make_unique<Queen>(this, type, team);
		break;
	case PIECE_ROOK:
		this->cp = std::make_unique<Rook>(this, type, team);
		break;
	case PIECE_BISHOP:
		this->cp = std::make_unique<Bishop>(this, type, team);
		break;
	case PIECE_KNIGHT:
		this->cp = std::make_unique<Knight>(this, type, team);
		break;
	case PIECE_PAWN:
		this->cp = std::make_unique<Pawn>(this, type, team);
		break;
	default:
		return false;
	}

	return true;
}

void Chess::ChessBlock::DeleteChessPiece()
{
	cp.release();
}

bool Chess::ChessBlock::CompareChessPiece(ChessPiece* cp)
{
	return (this->cp.get() == cp);
}

/*
void Chess::ChessBlock::SetMove(int team,int value)
{
	if(team != 0 && team != 1)
		return;

	if (team == cp->GetTeam())
		return;

	ChessBlock cbTmp = *this;

	*this = *ptCG->GetChessBlock(ptCG->GetSelectedPoint());

	ChessBlock& rfCBTmp = *(ptCG->GetChessBlock(ptCG->GetSelectedPoint()));
	*ptCG->GetChessBlock(ptCG->GetSelectedPoint()) = ChessBlock(this->ptCG);

	if (ptCG->IsCheck(team)) {
		*ptCG->GetChessBlock(ptCG->GetSelectedPoint()) = *this;
		*this = cbTmp;
		return;
	}

	*ptCG->GetChessBlock(ptCG->GetSelectedPoint()) = *this;
	*this = cbTmp;

	Moveable[team] = value;
}*/

void Chess::ChessBlock::SetCheck(int team,int value)
{
	bCheck = value;
}

int Chess::ChessBlock::GetMove(int team) const
{
	if (team == 0 || team == 1)
		return Moveable[team];
	else
		return 0;
}

bool Chess::ChessBlock::GetCheck() const
{
	return bCheck;
}

void Chess::ChessBlock::ClearMove()
{
	ZeroMemory(Moveable, sizeof(Moveable));
}

void Chess::ChessBlock::SetChessGame(ChessGame* ptCG)
{
	this->ptCG = ptCG;
}

void Chess::ChessBlock::SetMove(int team, int value) {

}
void Chess::ChessBlock::MovementChessPiece(ChessGame& cg, CPoint ptChessPiece,bool bChecking)
{
	if ((bool)cp == false)
		return;

	if (cg.IsRightPoint(ptChessPiece) == false)
		return;

	if (bChecking == false)
		cp->Movement(cg, ptChessPiece, &ChessBlock::SetMove);
	else
		cp->Movement(cg, ptChessPiece, &ChessBlock::SetCheck);
}

ChessBlock Chess::ChessBlock::operator=(ChessBlock& cb)
{
	this->ptCG = cb.ptCG;

	if (cb.cp == false) {
		cp.release();
		return *this;
	}

	if ((bool)this->cp == true)
		cp.release();

	cp.reset(cb.cp->CopyChessPiece());

	return *this;
}
