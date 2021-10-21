
// FillMarkNhungDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FillMarkNhung.h"
#include "FillMarkNhungDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Algorithm.h"
#include <string>


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFillMarkNhungDlg dialog



CFillMarkNhungDlg::CFillMarkNhungDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILLMARKNHUNG_DIALOG, pParent)
	, numScore(0)
	, className(_T(""))
	, fileSavePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFillMarkNhungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM_SCORE, numScore);
	DDV_MinMaxInt(pDX, numScore, 0, 10);
	DDX_Text(pDX, IDC_EDIT_NUM_CLASS, className);
	DDX_Text(pDX, IDC_MFCEDITBROWSE, fileSavePath);
}

BEGIN_MESSAGE_MAP(CFillMarkNhungDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GEN_SAMPLE, &CFillMarkNhungDlg::OnBnClickedButtonGenSample)
	ON_BN_CLICKED(ID_BUTTON_NHAPDIEM, &CFillMarkNhungDlg::OnBnClickedButtonNhapdiem)
END_MESSAGE_MAP()


// CFillMarkNhungDlg message handlers

BOOL CFillMarkNhungDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFillMarkNhungDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFillMarkNhungDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFillMarkNhungDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFillMarkNhungDlg::OnBnClickedButtonGenSample()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	std::wstring temp(className);
	temp += L".xlsx";
	createStudentListSample(temp.c_str(), numScore);
}


void CFillMarkNhungDlg::OnBnClickedButtonNhapdiem()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString filePath = L"2021-10-21_22-36-24_6A3.xlsx";
	std::wstring temp(filePath);
	importScore(temp.c_str(), numScore);
}
