#pragma once

namespace Chess {
	const int TEAM_BLACK = 0;
	const int TEAM_WHITE = 1;
	
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

	class ChessPiece
	{
	private:
		const int type;
		int team;
	protected:
		int Foward(int Num,int add, int team);
	public:

		ChessPiece(int type,int team);
		int GetType() const;
		int GetTeam() const;

		virtual void Movement(ChessGame& cg,CPoint ptChessPiece);
		ChessPiece ReturnType();
	};

	class King : public ChessPiece
	{
	private:

	public:
		King(int type, int team);
		King ReturnType();
	};

	class Queen : public ChessPiece
	{
	private:

	public:
		Queen(int type, int team);
		Queen ReturnType();
	};

	class Rook : public ChessPiece
	{
	private:

	public:
		Rook(int type, int team);
		Rook ReturnType();
	};

	class Bishop : public ChessPiece
	{
	private:

	public:
		Bishop(int type, int team);
		Bishop ReturnType();
	};

	class Knight : public ChessPiece
	{
	private:

	public:
		Knight(int type, int team);
		Knight ReturnType();
	};

	class Pawn : public ChessPiece
	{
	private:

	public:
		Pawn(int type, int team);
		Pawn ReturnType();

		virtual void Movement(ChessGame& cg, CPoint ptChessPiece) override;
	};
}