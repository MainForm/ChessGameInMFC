#pragma once

namespace Chess {
	class ChessPiece
	{
	private:
		static const int TEAM_BLACK = 0;
		static const int TEAM_WHITE = 1;

		int team;
	public:
		ChessPiece(int team);
	};

	class King : public ChessPiece
	{
	private:

	public:
		King(int team);
	};

	class Pawn : public ChessPiece
	{
	private:

	public:
		Pawn(int team);
	};
}