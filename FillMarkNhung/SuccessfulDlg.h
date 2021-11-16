#pragma once
#include "afxdialogex.h"


UINT FillMarkThread(LPVOID Param);
// SuccessfulDlg dialog

class SuccessfulDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SuccessfulDlg)

public:
	SuccessfulDlg(CWnd* pParent = nullptr);   // standard constructor
	SuccessfulDlg(int m_threshold, CString m_filepath, CString m_fileoutput);
	virtual ~SuccessfulDlg();
	int m_threshold;
	CString m_filepath;
	CString m_fileoutput;
	int m_progressbarPos = 0;
	bool m_isCompleted = false;

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
	CProgressCtrl m_CtrlProgress;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_BtOKCtrl;
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	CStatic m_status;
};
