// DialogBarView.h : interface of the CDialogBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGBARVIEW_H__10D799AC_2E74_11DA_B776_0040F43A9B72__INCLUDED_)
#define AFX_DIALOGBARVIEW_H__10D799AC_2E74_11DA_B776_0040F43A9B72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDialogBarView : public CView
{
protected: // create from serialization only
	CDialogBarView();
	DECLARE_DYNCREATE(CDialogBarView)

// Attributes
public:
	CDialogBarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDialogBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDialogBarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DialogBarView.cpp
inline CDialogBarDoc* CDialogBarView::GetDocument()
   { return (CDialogBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBARVIEW_H__10D799AC_2E74_11DA_B776_0040F43A9B72__INCLUDED_)
