#pragma once
#include "afxdialogex.h"


// SuccessfulDlg dialog

class SuccessfulDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SuccessfulDlg)

public:
	SuccessfulDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SuccessfulDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUCESSFUL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString textYeuEm;
	afx_msg void OnStnClickedTextYeuem();
};
