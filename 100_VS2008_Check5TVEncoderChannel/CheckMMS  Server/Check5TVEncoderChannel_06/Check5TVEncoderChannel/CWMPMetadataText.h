// CWMPMetadataText.h  : �H Microsoft Visual C++ �إߤ� ActiveX ����]�˨禡���O���ŧi

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CWMPMetadataText

class CWMPMetadataText : public COleDispatchDriver
{
public:
	CWMPMetadataText() {}		// �I�s COleDispatchDriver �w�]�غc�禡
	CWMPMetadataText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPMetadataText(const CWMPMetadataText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// �ݩ�
public:

// �@�~
public:

	CString get_Description()
	{
		CString result;
		InvokeHelper(0x420, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_text()
	{
		CString result;
		InvokeHelper(0x41f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}


};
