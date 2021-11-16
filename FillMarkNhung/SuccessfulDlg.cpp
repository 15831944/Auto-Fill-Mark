// SuccessfulDlg.cpp : implementation file
//

#include "pch.h"
#include "FillMarkNhung.h"
#include "afxdialogex.h"
#include "SuccessfulDlg.h"
#include <string>
#include <random>
#include "Algorithm.h"

int threshold;
CString filepath;
CString fileoutput;
int progressbarPos;
int importScoreResult;

// SuccessfulDlg dialog
IMPLEMENT_DYNAMIC(SuccessfulDlg, CDialogEx)

SuccessfulDlg::SuccessfulDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SUCESSFUL, pParent)
	, textYeuEm(_T(""))
{
	/*std::vector<const wchar_t*> currency = { L" ₫", L" $", L" £", L" ¥", L" €", L" ₩", L" BTC" };

	const int range_from = 0;
	const int range_to = currency.size() - 1;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);*/
	//std:: wstring wtemp = std::wstring(L"Yêu em 3000") + std::wstring(currency[distr(generator)]) + std::wstring(L" ♥");
	//textYeuEm = wtemp.c_str();
	filepath = m_filepath;
	fileoutput = m_fileoutput;
	threshold = m_threshold;
	progressbarPos = 0;
	m_isCompleted = false;
}

SuccessfulDlg::~SuccessfulDlg()
{
}

void SuccessfulDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT_YEUEM, textYeuEm);
	DDX_Control(pDX, IDC_PROGRESS1, m_CtrlProgress);
	DDX_Control(pDX, IDOK, m_BtOKCtrl);
	DDX_Control(pDX, IDC_STATIC_STATUS, m_status);
}


BEGIN_MESSAGE_MAP(SuccessfulDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &SuccessfulDlg::OnNMCustomdrawProgress1)
	ON_STN_CLICKED(IDC_TEXT_YEUEM, &SuccessfulDlg::OnStnClickedTextYeuem)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// SuccessfulDlg message handlers


void SuccessfulDlg::OnStnClickedTextYeuem()
{
	// TODO: Add your control notification handler code here
}


BOOL SuccessfulDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
#ifdef COMMERCIAL
	SetWindowText(L"Thông báo");
	m_BtOKCtrl.SetWindowTextW(L"Mở file đã nhập điểm");
#endif
	m_CtrlProgress.SetRange(0, 115);
	m_CtrlProgress.SetPos(0);
	
	AfxBeginThread(FillMarkThread, 0); // <<== START THE THREAD
	SetTimer(1000, 100, NULL); // 3 times per second
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


UINT FillMarkThread(LPVOID Param)
{
	importScoreResult = importScore(filepath, fileoutput, threshold, progressbarPos);
	return TRUE;
}


void SuccessfulDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1000)
	{
		m_CtrlProgress.SetPos(progressbarPos);
		int min, max;
		m_CtrlProgress.GetRange(min, max);
		if (m_CtrlProgress.GetPos() >= max)
		{
			m_BtOKCtrl.EnableWindow(TRUE);
#ifdef COMMERCIAL
			m_status.SetWindowTextW(L"Đã nhập điểm xong !!!");
#else
			m_status.SetWindowTextW(L"Đã nhập điểm xong rồi nhé Nhung Nhung ♥");
#endif
		}
		else
		{
			m_BtOKCtrl.EnableWindow(FALSE);
			std::wstring temp;
			if (m_CtrlProgress.GetPos() <= 10)
			{
				if (importScoreResult == 1)
				{
#ifdef COMMERCIAL
					temp = std::wstring(L"Đã có lỗi xảy ra, vui lòng kiểm tra lại file nhập điểm !");
					m_status.SetWindowTextW(temp.c_str());
#else
					temp = std::wstring(L"Mình kiểm tra lại file nhập điểm nhé, có lỗi xảy ra rồi ♥");
					m_status.SetWindowTextW(temp.c_str());
#endif
				}
				else
				{
					temp = std::wstring(L"Đang nhập dữ liệu từ các bảng... (") + std::to_wstring(m_CtrlProgress.GetPos() * 100 / max) + std::wstring(L"%)");
					m_status.SetWindowTextW(temp.c_str());
				}
			}
			else if (m_CtrlProgress.GetPos() < max - 5)
			{
#ifdef COMMERCIAL
				temp = std::wstring(L"Đang ghép tên học sinh ... (") + std::to_wstring(m_CtrlProgress.GetPos() * 100 / max) + std::wstring(L"%)");
#else
				temp = std::wstring(L"Đang ghép tên các học trò đáng yêu của cô Nhung Nhung ♥ (") + std::to_wstring(m_CtrlProgress.GetPos() * 100 / max) + std::wstring(L"%)");
#endif
				m_status.SetWindowTextW(temp.c_str());
			}
			else
			{
				temp = std::wstring(L"Đang ghi dữ liệu... (") + std::to_wstring(m_CtrlProgress.GetPos() * 100 / max) + std::wstring(L"%)");
				m_status.SetWindowTextW(temp.c_str());
			}
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

SuccessfulDlg::SuccessfulDlg(int m_threshold, CString m_filepath, CString m_fileoutput) : CDialogEx(IDD_DIALOG_SUCESSFUL, nullptr)
, textYeuEm(_T(""))
{
#ifdef COMMERCIAL
	textYeuEm = L"";
#else
	std::vector<const wchar_t*> currency = { L" ₫", L" $", L" £", L" ¥", L" €", L" ₩", L" BTC" };

	const int range_from = 0;
	const int range_to = currency.size() - 1;
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<int>  distr(range_from, range_to);

	std:: wstring wtemp = std::wstring(L"Yêu em 3000") + std::wstring(currency[distr(generator)]) + std::wstring(L" ♥");
	textYeuEm = wtemp.c_str();
#endif

	this->m_threshold = m_threshold;
	this->m_filepath = m_filepath;
	this->m_fileoutput = m_fileoutput;
	filepath = m_filepath;
	fileoutput = m_fileoutput;
	threshold = m_threshold;
	progressbarPos = 0;
	importScoreResult = 0;
	//m_BtOKCtrl.EnableWindow(FALSE);
}

void SuccessfulDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
