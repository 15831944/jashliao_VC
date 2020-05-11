// testURLDlg.h : header file
//

#if !defined(AFX_TESTURLDLG_H__11ADE6C9_F6A0_4D57_B57F_3EC59B0A259B__INCLUDED_)
#define AFX_TESTURLDLG_H__11ADE6C9_F6A0_4D57_B57F_3EC59B0A259B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestURLDlg dialog

class CTestURLDlg : public CDialog
{
// Construction
public:
	CTestURLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestURLDlg)
	enum { IDD = IDD_TESTURL_DIALOG };
	CString	m_URL;
	long	m_v1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestURLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestURLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTURLDLG_H__11ADE6C9_F6A0_4D57_B57F_3EC59B0A259B__INCLUDED_)
