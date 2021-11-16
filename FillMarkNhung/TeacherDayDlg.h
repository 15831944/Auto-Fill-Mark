#pragma once


// TeacherDayDlg dialog

class TeacherDayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TeacherDayDlg)

public:
	TeacherDayDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TeacherDayDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEACHERDAY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAcnStartAnimate1();
	afx_msg void OnBnClickedOk();
};
