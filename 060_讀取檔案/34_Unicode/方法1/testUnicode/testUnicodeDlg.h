// testUnicodeDlg.h : header file
//

#if !defined(AFX_TESTUNICODEDLG_H__E8C6735C_DF44_46DE_AA21_FC6E8F6F3D69__INCLUDED_)
#define AFX_TESTUNICODEDLG_H__E8C6735C_DF44_46DE_AA21_FC6E8F6F3D69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestUnicodeDlg dialog

class CTestUnicodeDlg : public CDialog
{
// Construction
public:
	CTestUnicodeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestUnicodeDlg)
	enum { IDD = IDD_TESTUNICODE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestUnicodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestUnicodeDlg)
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

#endif // !defined(AFX_TESTUNICODEDLG_H__E8C6735C_DF44_46DE_AA21_FC6E8F6F3D69__INCLUDED_)
