// SuccessfulDlg.cpp : implementation file
//

#include "pch.h"
#include "FillMarkNhung.h"
#include "afxdialogex.h"
#include "SuccessfulDlg.h"
#include <string>
#include <random>

// SuccessfulDlg dialog

IMPLEMENT_DYNAMIC(SuccessfulDlg, CDialogEx)

SuccessfulDlg::SuccessfulDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SUCESSFUL, pParent)
	, textYeuEm(_T(""))
{
	std::vector<const wchar_t*> currency = { L" ₫", L" $", L" £", L" ¥", L" €", L" ₩", L" BTC" };

	const int range_from = 0;
	const int range_to = currency.size();
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	std:: wstring wtemp = std::wstring(L"Yêu em 3000") + std::wstring(currency[distr(generator)]) + std::wstring(L" ♥");
	textYeuEm = wtemp.c_str();
}

SuccessfulDlg::~SuccessfulDlg()
{
}

void SuccessfulDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_YEUEM, textYeuEm);
}


BEGIN_MESSAGE_MAP(SuccessfulDlg, CDialogEx)
	ON_STN_CLICKED(IDC_TEXT_YEUEM, &SuccessfulDlg::OnStnClickedTextYeuem)
END_MESSAGE_MAP()


// SuccessfulDlg message handlers


void SuccessfulDlg::OnStnClickedTextYeuem()
{
	// TODO: Add your control notification handler code here
}
