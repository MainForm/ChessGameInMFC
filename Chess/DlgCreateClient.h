#pragma once


// DlgCreateClient 대화 상자

class DlgCreateClient : public CDialog
{
	DECLARE_DYNAMIC(DlgCreateClient)

public:
	DlgCreateClient(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgCreateClient();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATECLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString ctrl_Port;
	CIPAddressCtrl ctrl_IPAddress;
};
