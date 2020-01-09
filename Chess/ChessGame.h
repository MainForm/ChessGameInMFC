#pragma once

#include <array>
#include <memory>

#include "ChessBlock.h"
#include "ChessPiece.h"
#include "Resource.h"

#include "CChessServer.h"
#include "CChessClient.h"

namespace Chess {

	using namespace std;

	class ChessGame
	{
	private:
		static const int BLOCK_COUNT = 8;

		array<array<unique_ptr<ChessBlock>, BLOCK_COUNT>,BLOCK_COUNT> Board;

		CBitmap bmChessPieces[2][PIECE_COUNT];
		CPoint ptStart;
		CPoint ptSelect;
		int iBlockSize;
		bool bMove;
		bool bEnPassant;
		bool bCheckMove;
		int turn;

		unique_ptr<CChessServer> ptServer;
		unique_ptr<CChessClient> ptClinet;
	public:

		ChessGame(CPoint sp = { 0,0 });
		virtual ~ChessGame();

		void PaintChessPiece(CPaintDC& dc, CPoint pt);
		void PaintChessPieces(CPaintDC& dc);
		void PaintChessBoard(CPaintDC& dc);

		void StartGame();
		void EndGame();
		void ChessBoardMessage(CPoint ptCursor);

		bool AddChessPiece(CPoint pt,int type,int team);

		CPoint GetSelectedPoint();

		ChessBlock* GetChessBlock(CPoint pt);
		void ClearAllMove();
		void ClearAllCheck();

		bool IsCheck(int team);

		void IdentifyEnPassant(CPoint cpTo,CPoint cpFrom);
		bool GetEnPassant();

		bool IsRightPoint(CPoint pt) const;

		bool CreateServer(int Port);
		bool IsServerOpen();
		void CloseServer();

		bool ConnectClient(CString& IPAddress,int Port);
		bool AcceptClient();
		bool IsClientOpen();
		void CloseClient();

		bool SendCommand(CString Command);

		bool GetCheckMove();
		void SetCheckMove(bool bValue);
	};
}