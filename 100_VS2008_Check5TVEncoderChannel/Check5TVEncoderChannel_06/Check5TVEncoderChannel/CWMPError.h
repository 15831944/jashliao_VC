// CWMPError.h  : �H Microsoft Visual C++ �إߤ� ActiveX ����]�˨禡���O���ŧi

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPError

class CWMPError : public COleDispatchDriver
{
public:
	CWMPError() {}		// �I�s COleDispatchDriver �w�]�غc�禡
	CWMPError(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPError(const CWMPError& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// �ݩ�
public:

// �@�~
public:

	void clearErrorQueue()
	{
		InvokeHelper(0x353, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_errorCount()
	{
		long result;
		InvokeHelper(0x354, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(long dwIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x355, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, dwIndex);
		return result;
	}
	void webHelp()
	{
		InvokeHelper(0x356, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}


};
