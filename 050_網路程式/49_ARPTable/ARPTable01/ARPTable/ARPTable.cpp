// ARPTable.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "ARPTable.h"
#include <Iprtrmib.h>
#include <Iphlpapi.h>
#include <IOSTREAM>
#include <stdio.h>
using namespace std;
#define ARP_TABLE_SIZE   1
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �Ȧ����@�����ε{������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��l�� MFC �é󥢱ѮɦC�L���~
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: �t�X�z���ݭn�ܧ���~�X
		_tprintf(_T("�Y�����~: MFC ��l�ƥ���\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: �b�����g���ε{���欰���{���X�C
		unsigned long nSize = ARP_TABLE_SIZE;

		PMIB_IPNETTABLE pMib = (PMIB_IPNETTABLE)malloc(sizeof(MIB_IPNETTABLE)+sizeof(MIB_IPNETROW)*nSize);

		DWORD dwRetval = GetIpNetTable(pMib,&nSize,TRUE); 
		while (dwRetval)
		{
		   dwRetval = GetIpNetTable(pMib, &nSize, TRUE);	   
		}

		DWORD dwNumEntries = (unsigned long)pMib->dwNumEntries ;	

		printf("---------------------------\n");

		/* ���ARP Information */
		for (DWORD i=0; i<dwNumEntries; i++) 
		{
			/* �CIP */
			printf("IP : %d.%d.%d.%d\n", pMib->table[i].dwAddr&0xff,
				(pMib->table[i].dwAddr&0xff00) >> 8,
				(pMib->table[i].dwAddr&0xff0000) >> 16,
				(pMib->table[i].dwAddr) >> 24);
		
			/* �CMAC */
			printf("MAC: %x-%x-%x-%x-%x-%x\n", (int)pMib->table[i].bPhysAddr[0],
				(int)pMib->table[i].bPhysAddr[1],
				(int)pMib->table[i].bPhysAddr[2],
				(int)pMib->table[i].bPhysAddr[3],
				(int)pMib->table[i].bPhysAddr[4],
				(int)pMib->table[i].bPhysAddr[5]);
		}

		printf("---------------------------\n");
	}

	return nRetCode;
}
