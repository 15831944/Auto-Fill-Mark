
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
#include "SuccessfulDlg.h"
#include "TeacherDayDlg.h"


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
	, numScore(1)
	, className(_T("6A3"))
	, fileSavePath(_T(""))
	, m_threshold(90)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFillMarkNhungDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM_SCORE, numScore);
	DDV_MinMaxInt(pDX, numScore, 1, 20);
	DDX_Text(pDX, IDC_EDIT_NUM_CLASS, className);
	DDX_Text(pDX, IDC_MFCEDITBROWSE, fileSavePath);
	DDX_Control(pDX, IDC_MFCEDITBROWSE, editBrowserCtrl);
	editBrowserCtrl.EnableFileBrowseButton(_T("XLSX"), _T("Excel Workbooks|*.xlsx||"));
	DDX_Text(pDX, IDC_EDIT3, m_threshold);
	DDV_MinMaxInt(pDX, m_threshold, 0, 100);
	DDX_Control(pDX, ID_BUTTON_NHAPDIEM, m_NhapDiemCtrl);
	DDX_Control(pDX, IDC_BUTTON_GEN_SAMPLE, m_genSampleCtrl);
}

BEGIN_MESSAGE_MAP(CFillMarkNhungDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GEN_SAMPLE, &CFillMarkNhungDlg::OnBnClickedButtonGenSample)
	ON_BN_CLICKED(ID_BUTTON_NHAPDIEM, &CFillMarkNhungDlg::OnBnClickedButtonNhapdiem)
	ON_EN_CHANGE(IDC_EDIT_NUM_SCORE, &CFillMarkNhungDlg::OnEnChangeEditNumScore)
	ON_EN_CHANGE(IDC_EDIT3, &CFillMarkNhungDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE, &CFillMarkNhungDlg::OnEnChangeMfceditbrowse)
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
#ifdef COMMERCIAL
	std::wstring temp = std::wstring(L"Phần mềm nhập điểm cho Excel ") + std::wstring(VERSION);
	SetWindowText(temp.c_str());
#else
	std::wstring temp = std::wstring(L"Phần mềm nhập điểm cho Nhung Nhung ♥ ") + std::wstring(VERSION);
	SetWindowText(temp.c_str());
	std::wstring datecheck = getDateToWString();
	if (datecheck.compare(L"2021-11-20") == 0)
	{
		TeacherDayDlg teacherDayDlg;
		teacherDayDlg.DoModal();
	}
#endif
	m_NhapDiemCtrl.EnableWindow(FALSE);
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
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	std::wstring temp2(currentDir);
	std::wstring timeTemp = getTimeToWString();
	std::wstring temp(className);
	temp = temp2 + L"\\" + timeTemp + temp + L".xlsx";
	createStudentListSample(temp.c_str(), numScore);
	editBrowserCtrl.SetWindowTextW(temp.c_str());
}


void CFillMarkNhungDlg::OnBnClickedButtonNhapdiem()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString filePath;
	editBrowserCtrl.GetWindowTextW(filePath);
	CString fileOutput;
	int check = saveFileDialog(fileOutput);
	if (!check)
	{
		
		//if (!(importScore(filePath, fileOutput, m_threshold)))
		{
			SuccessfulDlg dlg (m_threshold, filePath, fileOutput);
			if (dlg.DoModal() == IDOK)
			{
				::ShellExecute(NULL, L"open", fileOutput, NULL, NULL, SW_SHOW);
			}
		}
			
	}
	else
	{
		//Error
	}
}

std::wstring CFillMarkNhungDlg::getTimeToWString()
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S_", &timeinfo);
	std::string str(buffer);
	std::wstring wsTmp(str.begin(), str.end());
	return wsTmp;
}

std::wstring CFillMarkNhungDlg::getDateToWString()
{
	time_t rawtime;
	struct tm timeinfo;
	char buffer[80];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%Y-%m-%d", &timeinfo);
	std::string str(buffer);
	std::wstring wsTmp(str.begin(), str.end());
	return wsTmp;
}

int CFillMarkNhungDlg::saveFileDialog(CString& filePath)
{
	TCHAR currentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currentDir);
	LPCTSTR pszFilter = _T("Excel Workbooks |*.xlsx||");
	CFileDialog dlgFile(FALSE, _T("xlsx"), className, OFN_OVERWRITEPROMPT, pszFilter, AfxGetMainWnd());
	//dlgFile.m_ofn.lpstrInitialDir = currentDir;
	if (dlgFile.DoModal() == IDOK)
	{
		filePath = dlgFile.GetPathName();
		return 0;
	}
	else
	{
		return 1;
	}
}

void CFillMarkNhungDlg::OnEnChangeEditNumScore()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFillMarkNhungDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CFillMarkNhungDlg::OnEnChangeMfceditbrowse()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
	CString filePath;
	editBrowserCtrl.GetWindowTextW(filePath);
	if (!filePath.IsEmpty())
	{
		m_NhapDiemCtrl.EnableWindow(TRUE);
	}
	else
	{
		m_NhapDiemCtrl.EnableWindow(FALSE);
	}
}
