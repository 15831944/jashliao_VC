#if !defined(AFX_WMPSETTINGS_H__516ABD5B_3226_4599_B0B4_465CA7D9753E__INCLUDED_)
#define AFX_WMPSETTINGS_H__516ABD5B_3226_4599_B0B4_465CA7D9753E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CWMPSettings wrapper class

class CWMPSettings : public COleDispatchDriver
{
public:
	CWMPSettings() {}		// Calls COleDispatchDriver default constructor
	CWMPSettings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPSettings(const CWMPSettings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsAvailable(LPCTSTR bstrItem);
	BOOL GetAutoStart();
	void SetAutoStart(BOOL bNewValue);
	CString GetBaseURL();
	void SetBaseURL(LPCTSTR lpszNewValue);
	CString GetDefaultFrame();
	void SetDefaultFrame(LPCTSTR lpszNewValue);
	BOOL GetInvokeURLs();
	void SetInvokeURLs(BOOL bNewValue);
	BOOL GetMute();
	void SetMute(BOOL bNewValue);
	long GetPlayCount();
	void SetPlayCount(long nNewValue);
	double GetRate();
	void SetRate(double newValue);
	long GetBalance();
	void SetBalance(long nNewValue);
	long GetVolume();
	void SetVolume(long nNewValue);
	BOOL getMode(LPCTSTR bstrMode);
	void setMode(LPCTSTR bstrMode, BOOL varfMode);
	BOOL GetEnableErrorDialogs();
	void SetEnableErrorDialogs(BOOL bNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPSETTINGS_H__516ABD5B_3226_4599_B0B4_465CA7D9753E__INCLUDED_)
