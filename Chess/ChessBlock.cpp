#include "pch.h"
#include "ChessGame.h"
#include "ChessBlock.h"

using namespace Chess;

ChessBlock::ChessBlock(ChessGame* cg, CPoint pt) : cp(nullptr), ptCG(cg), cpPos(pt),Moveable(false),bCheck(false)
{
}

ChessBlock::ChessBlock(ChessBlock& cb) : cp(nullptr), ptCG(cb.ptCG), cpPos(cb.cpPos), Moveable(false), bCheck(false)
{
	if(cb.cp != nullptr)
		cp.reset(cb.cp->CopyChessPiece());
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

CPoint Chess::ChessBlock::GetPos() const
{
	return cpPos;
}

ChessGame* Chess::ChessBlock::GetGame() const
{
	return this->ptCG;
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


void Chess::ChessBlock::SetMove(int value)
{
	ChessBlock* ptCB = ptCG->GetChessBlock(ptCG->GetSelectedPoint());
	int ttype = GetChessPieceType();
	int tteam = GetChessPieceTeam();

	
	if (value == 3 || value == 2) {
		Moveable = value;
		return;
	}

	if (ptCB->GetChessPieceTeam() == GetChessPieceTeam())
		return;

	ptCG->MoveChessPiece(cpPos, ptCG->GetSelectedPoint());

	if (ptCG->IsCheck(GetChessPieceTeam())) {
		ptCG->MoveChessPiece(ptCG->GetSelectedPoint(),cpPos);
		ptCG->AddChessPiece(cpPos, ttype, tteam);
		return;
	}
	ptCG->MoveChessPiece(ptCG->GetSelectedPoint(), cpPos);
	ptCG->AddChessPiece(cpPos, ttype, tteam);

	Moveable = value;
}

void Chess::ChessBlock::SetCheck(int value)
{
	bCheck = value;
}

int Chess::ChessBlock::GetMove() const
{
	return Moveable;
}

bool Chess::ChessBlock::GetCheck() const
{
	return bCheck;
}

void Chess::ChessBlock::ClearMove()
{
	Moveable = false;
}

void Chess::ChessBlock::SetChessGame(ChessGame* ptCG)
{
	this->ptCG = ptCG;
}

void Chess::ChessBlock::MovementChessPiece(bool bChecking)
{
	if ((bool)cp == false)
		return;

	if (bChecking == false)
		cp->Movement(&ChessBlock::SetMove);
	else
		cp->Movement(&ChessBlock::SetCheck);
}