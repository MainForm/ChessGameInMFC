#pragma once

namespace Chess {
	const int TEAM_BLACK = 1;
	const int TEAM_WHITE = 0;
	
	const int PIECE_KING = 0;
	const int PIECE_QUEEN = 1;
	const int PIECE_ROOK = 2;
	const int PIECE_BISHOP = 3;
	const int PIECE_KNIGHT = 4;
	const int PIECE_PAWN = 5;

	const int PIECE_COUNT = 6;

	//ChessPiece class can't be transfrom to abstract class.
	//because unique_ptr occur the error when using the abstract class.
	//so I just use this class without making to abstract.
	class ChessGame;
	class ChessBlock;

	using SetFunc = void (ChessBlock::*)(int);

	class ChessPiece
	{
	private:
		ChessBlock* ptCB;

		const int type;
		int team;
	public:
		CPoint Foward(CPoint pt, int team);

		ChessPiece(ChessBlock* ptCB,int type,int team);
		int GetType() const;
		int GetTeam() const;
		ChessBlock* GetBlock();

		virtual void Movement(SetFunc Func);
		virtual ChessPiece* CopyChessPiece();
	};

	class King : public ChessPiece
	{
	private:

	public:
		King(ChessBlock* ptCB, int type, int team);
		virtual void Movement(SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};

	class Queen : public ChessPiece
	{
	private:

	public:
		Queen(ChessBlock* ptCB, int type, int team);
		virtual void Movement( SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};

	class Rook : public ChessPiece
	{
	private:

	public:
		Rook(ChessBlock* ptCB, int type, int team);
		virtual void Movement( SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};

	class Bishop : public ChessPiece
	{
	private:

	public:
		Bishop(ChessBlock* ptCB, int type, int team);
		virtual void Movement( SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};

	class Knight : public ChessPiece
	{
	private:

	public:
		Knight(ChessBlock* ptCB, int type, int team);

		virtual void Movement( SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};

	class Pawn : public ChessPiece
	{
	private:
		bool bEnPassant;
	public:
		Pawn(ChessBlock* ptCB, int type, int team);

		virtual void Movement(SetFunc Func) override;
		virtual ChessPiece* CopyChessPiece() override;
	};
}