
// FillMarkNhungDlg.h : header file
//

#pragma once


// CFillMarkNhungDlg dialog
class CFillMarkNhungDlg : public CDialogEx
{
// Construction
public:
	CFillMarkNhungDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILLMARKNHUNG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int numScore;
	afx_msg void OnBnClickedButtonGenSample();
	CString className;
	CString fileSavePath;
	afx_msg void OnBnClickedButtonNhapdiem();
};
