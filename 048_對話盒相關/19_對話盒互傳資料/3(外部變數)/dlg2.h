#if !defined(AFX_DLG2_H__997988EA_7284_4A3B_B03D_FB805D1CA6CB__INCLUDED_)
#define AFX_DLG2_H__997988EA_7284_4A3B_B03D_FB805D1CA6CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg2.h : header file
//
#include "dlgDlg.h"
/////////////////////////////////////////////////////////////////////////////
// dlg2 dialog

class dlg2 : public CDialog
{
// Construction
public:
	dlg2(CWnd* pParent = NULL);   // standard constructor
	void getval(CDlgDlg *a);
// Dialog Data
	//{{AFX_DATA(dlg2)
	enum { IDD = IDD_DIALOG1 };
	int		m_v1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dlg2)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2_H__997988EA_7284_4A3B_B03D_FB805D1CA6CB__INCLUDED_)
