// CWMPErrorItem.h  : �H Microsoft Visual C++ �إߤ� ActiveX ����]�˨禡���O���ŧi

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPErrorItem

class CWMPErrorItem : public COleDispatchDriver
{
public:
	CWMPErrorItem() {}		// �I�s COleDispatchDriver �w�]�غc�禡
	CWMPErrorItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPErrorItem(const CWMPErrorItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// �ݩ�
public:

// �@�~
public:

	long get_errorCode()
	{
		long result;
		InvokeHelper(0x385, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_errorDescription()
	{
		CString result;
		InvokeHelper(0x386, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	VARIANT get_errorContext()
	{
		VARIANT result;
		InvokeHelper(0x387, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	long get_remedy()
	{
		long result;
		InvokeHelper(0x388, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_customUrl()
	{
		CString result;
		InvokeHelper(0x389, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}


};
