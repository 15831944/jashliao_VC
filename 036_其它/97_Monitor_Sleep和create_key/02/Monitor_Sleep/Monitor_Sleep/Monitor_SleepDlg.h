
// Monitor_SleepDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"


// CMonitor_SleepDlg ��ܤ��
class CMonitor_SleepDlg : public CDialogEx
{
// �غc
public:
	CMonitor_SleepDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MONITOR_SLEEP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_StrSetTime;
	CString m_StrPassword;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT onShowTask(WPARAM wParam,LPARAM lParam); //Step 4
	afx_msg void OnBnClickedButton2();
	CButton m_b1;
	CButton m_b2;
};
