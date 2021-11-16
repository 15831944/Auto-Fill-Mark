// TeacherDayDlg.cpp : implementation file
//

#include "pch.h"
#include "FillMarkNhung.h"
#include "TeacherDayDlg.h"
#include "afxdialogex.h"


// TeacherDayDlg dialog

IMPLEMENT_DYNAMIC(TeacherDayDlg, CDialogEx)

TeacherDayDlg::TeacherDayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEACHERDAY, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

TeacherDayDlg::~TeacherDayDlg()
{
}

void TeacherDayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TeacherDayDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &TeacherDayDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// TeacherDayDlg message handlers


void TeacherDayDlg::OnAcnStartAnimate1()
{
	// TODO: Add your control notification handler code here
}


void TeacherDayDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
