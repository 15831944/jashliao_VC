// GetMACAddress.cpp : �w�q DLL ����l�Ʊ`���C
//

#include "stdafx.h"
#include "GetMACAddress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �p�G�o�� DLL �O�ʺA�a�� MFC DLL �s���A
//		����q�o�� DLL �ץX������|�I�s
//		MFC �������禡�A�������b�禡�@�}�Y�[�W AFX_MANAGE_STATE
//		�����C
//
//		�Ҧp:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// ���B�����`�禡�D��
//		}
//
//		�o�ӥ����@�w�n�X�{�b�C�@��
//		�禡���A�~����I�s MFC �������C�o�N����
//		�������O�禡�����Ĥ@�ӳ��z��
//		�A�Ʀܥ����b���󪫥��ܼƫŧi�e��
//		�A�]�����̪��غc�禡�i��|���͹� MFC
//		DLL �������I�s�C
//
//		�аѾ\ MFC �޳N���� 33 �M 58 ����
//		�ԲӸ�ơC
//

// CGetMACAddressApp

BEGIN_MESSAGE_MAP(CGetMACAddressApp, CWinApp)
END_MESSAGE_MAP()

BSTR EXPORTED_DLL_FUNCTION GetMACAddress ()
{
	//step 03 by jash at 2010/10/20
	bool blnreturn=false;
	CString StrMac;
	char *chrData;
	IP_ADAPTER_INFO AdapterInfo[16];			// Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);		// Save the memory size of buffer
	try
	{
		DWORD dwStatus = GetAdaptersInfo(			// Call GetAdapterInfo
			AdapterInfo,							// [out] buffer to receive data
			&dwBufLen);								// [in] size of receive data buffer
		assert(dwStatus == ERROR_SUCCESS);			// Verify return value is valid, no buffer overflow

		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;// Contains pointer to current adapter info
		do {
			StrMac.Format("%02X-%02X-%02X-%02X-%02X-%02X",pAdapterInfo->Address[0],pAdapterInfo->Address[1],pAdapterInfo->Address[2],pAdapterInfo->Address[3],pAdapterInfo->Address[4],pAdapterInfo->Address[5]);
			pAdapterInfo = pAdapterInfo->Next;		// Progress through linked list
		}
		while(pAdapterInfo);						// Terminate if last adapter
	}
	catch(...)
	{
		StrMac="error";
	}
	chrData=StrMac.GetBuffer(0);
	return  SysAllocString((BSTR)chrData);
}
// CGetMACAddressApp �غc

CGetMACAddressApp::CGetMACAddressApp()
{
	// TODO: �b���[�J�غc�{���X�A
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CGetMACAddressApp ����

CGetMACAddressApp theApp;


// CGetMACAddressApp ��l�]�w

BOOL CGetMACAddressApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}
