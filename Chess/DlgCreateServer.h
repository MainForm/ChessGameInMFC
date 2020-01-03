#pragma once


// DlgCreateServer 대화 상자

class DlgCreateServer : public CDialog
{
	DECLARE_DYNAMIC(DlgCreateServer)

public:
	DlgCreateServer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgCreateServer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgCreateServer };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
