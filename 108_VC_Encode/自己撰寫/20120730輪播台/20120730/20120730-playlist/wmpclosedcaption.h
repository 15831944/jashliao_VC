#if !defined(AFX_WMPCLOSEDCAPTION_H__B7BA6EDA_3BA3_42D3_864A_74401AAA49F5__INCLUDED_)
#define AFX_WMPCLOSEDCAPTION_H__B7BA6EDA_3BA3_42D3_864A_74401AAA49F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CWMPClosedCaption wrapper class

class CWMPClosedCaption : public COleDispatchDriver
{
public:
	CWMPClosedCaption() {}		// Calls COleDispatchDriver default constructor
	CWMPClosedCaption(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPClosedCaption(const CWMPClosedCaption& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetSAMIStyle();
	void SetSAMIStyle(LPCTSTR lpszNewValue);
	CString GetSAMILang();
	void SetSAMILang(LPCTSTR lpszNewValue);
	CString GetSAMIFileName();
	void SetSAMIFileName(LPCTSTR lpszNewValue);
	CString GetCaptioningId();
	void SetCaptioningId(LPCTSTR lpszNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPCLOSEDCAPTION_H__B7BA6EDA_3BA3_42D3_864A_74401AAA49F5__INCLUDED_)
