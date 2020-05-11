// asdView.h : interface of the CAsdView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASDVIEW_H__56CDAA8C_435B_40DA_9BD0_68589DEBE05D__INCLUDED_)
#define AFX_ASDVIEW_H__56CDAA8C_435B_40DA_9BD0_68589DEBE05D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "asdDoc.h"
class CAsdView : public CView
{
protected: // create from serialization only
	CAsdView();
	DECLARE_DYNCREATE(CAsdView)

// Attributes
public:
	CAsdDoc* GetDocument();
	int value;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAsdView)
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
	virtual ~CAsdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAsdView)
	afx_msg void Ont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in asdView.cpp
inline CAsdDoc* CAsdView::GetDocument()
   { return (CAsdDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASDVIEW_H__56CDAA8C_435B_40DA_9BD0_68589DEBE05D__INCLUDED_)
