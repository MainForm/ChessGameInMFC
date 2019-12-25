// DlgPawnPromotion.cpp: 구현 파일
//

#include "pch.h"
#include "Chess.h"
#include "DlgPawnPromotion.h"
#include "afxdialogex.h"

#include "ChessPiece.h"


// DlgPawnPromotion 대화 상자

IMPLEMENT_DYNAMIC(DlgPawnPromotion, CDialog)

DlgPawnPromotion::DlgPawnPromotion(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PAWN_PROMOTION, pParent)
{

}

DlgPawnPromotion::~DlgPawnPromotion()
{
}

void DlgPawnPromotion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlgPawnPromotion, CDialog)
	ON_BN_CLICKED(IDC_QUEEN, &DlgPawnPromotion::OnBnClickedQueen)
	ON_BN_CLICKED(IDC_ROOK, &DlgPawnPromotion::OnBnClickedRook)
	ON_BN_CLICKED(IDC_BISHOP, &DlgPawnPromotion::OnBnClickedBishop)
	ON_BN_CLICKED(IDC_KNIGHT, &DlgPawnPromotion::OnBnClickedKnight)
END_MESSAGE_MAP()


// DlgPawnPromotion 메시지 처리기


void DlgPawnPromotion::OnBnClickedQueen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(Chess::PIECE_QUEEN);
}


void DlgPawnPromotion::OnBnClickedRook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(Chess::PIECE_ROOK);
}


void DlgPawnPromotion::OnBnClickedBishop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(Chess::PIECE_BISHOP);
}


void DlgPawnPromotion::OnBnClickedKnight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(Chess::PIECE_KNIGHT);
}
