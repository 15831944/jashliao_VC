
// USB_FramDoc.cpp : CUSB_FramDoc ���O����@
//

#include "stdafx.h"
#include "USB_Fram.h"

#include "USB_FramDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUSB_FramDoc

IMPLEMENT_DYNCREATE(CUSB_FramDoc, CDocument)

BEGIN_MESSAGE_MAP(CUSB_FramDoc, CDocument)
END_MESSAGE_MAP()


// CUSB_FramDoc �غc/�Ѻc

CUSB_FramDoc::CUSB_FramDoc()
{
	// TODO: �b���[�J�@���غc�{���X

}

CUSB_FramDoc::~CUSB_FramDoc()
{
}

BOOL CUSB_FramDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �b���[�J���s��l�Ƶ{���X
	// (SDI ���|���Φ����)

	return TRUE;
}




// CUSB_FramDoc �ǦC��

void CUSB_FramDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �b���[�J�x�s�{���X
	}
	else
	{
		// TODO: �b���[�J���J�{���X
	}
}


// CUSB_FramDoc �E�_

#ifdef _DEBUG
void CUSB_FramDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUSB_FramDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUSB_FramDoc �R�O
