#pragma once

// CChessServer 명령 대상

class CChessServer : public CSocket
{
public:
	CChessServer();
	virtual ~CChessServer();
	virtual void OnAccept(int nErrorCode);
};