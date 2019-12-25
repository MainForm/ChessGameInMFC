#pragma once


// DlgPawnPromotion 대화 상자

class DlgPawnPromotion : public CDialog
{
	DECLARE_DYNAMIC(DlgPawnPromotion)

public:
	DlgPawnPromotion(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DlgPawnPromotion();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAWN_PROMOTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQueen();
	afx_msg void OnBnClickedRook();
	afx_msg void OnBnClickedBishop();
	afx_msg void OnBnClickedKnight();
};
