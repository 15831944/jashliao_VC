// MultiThreadFTPDlg.h : header file
//

#if !defined(AFX_MULTITHREADFTPDLG_H__D93CA6B7_699B_423B_8521_B954CC21E7A5__INCLUDED_)
#define AFX_MULTITHREADFTPDLG_H__D93CA6B7_699B_423B_8521_B954CC21E7A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMultiThreadFTPDlg dialog

class CMultiThreadFTPDlg : public CDialog
{
// Construction
public:
	CMultiThreadFTPDlg(CWnd* pParent = NULL);	// standard constructor
	int m_intStep;
	int m_intSum;
	int m_intCount;
	int m_intThreadCount;
	int m_intCheckThread;
	int m_intThreadSum;
	CString StrShowData[5];
	CArray <CString,CString&> m_ArrayListIP;//CArray Step_02
	void ReadListFile();//(Data to CArray)
	int GetIPData();//�@���T�q���X5�����
	void ShowIPData();//�N�����ܦb�����W
	void WaitThread();//���ݰ����
	static UINT Thread00(LPVOID lpram);//�����
	static UINT Thread01(LPVOID lpram);//�����
	static UINT Thread02(LPVOID lpram);//�����
	static UINT Thread03(LPVOID lpram);//�����
	static UINT Thread04(LPVOID lpram);//�����
	void Thread00Fun();//������D��AFTP�M��B�U���A�إ߸�Ƨ�
	void Thread01Fun();//������D��AFTP�M��B�U���A�إ߸�Ƨ�
	void Thread02Fun();//������D��AFTP�M��B�U���A�إ߸�Ƨ�
	void Thread03Fun();//������D��AFTP�M��B�U���A�إ߸�Ƨ�
	void Thread04Fun();//������D��AFTP�M��B�U���A�إ߸�Ƨ�
// Dialog Data
	//{{AFX_DATA(CMultiThreadFTPDlg)
	enum { IDD = IDD_MULTITHREADFTP_DIALOG };
	CString	m_StrIP00;
	CString	m_StrIP01;
	CString	m_StrIP02;
	CString	m_StrIP03;
	CString	m_StrIP04;
	CString	m_StrIPCount;
	CString	m_StrIPSum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiThreadFTPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMultiThreadFTPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITHREADFTPDLG_H__D93CA6B7_699B_423B_8521_B954CC21E7A5__INCLUDED_)
