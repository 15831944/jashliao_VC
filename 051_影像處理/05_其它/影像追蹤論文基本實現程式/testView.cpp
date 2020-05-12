// testView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys\timeb.h>
#include "testDoc.h"
#include "testView.h"
#include <string.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CPoint start,end;
FILE *p,*f;
/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_change, Onchange)
	ON_COMMAND(ID_change1, Onchange1)
	ON_COMMAND(ID_copchange, Oncopchange)
	ON_COMMAND(ID_changegray, Onchangegray)
	ON_COMMAND(ID_diff, Ondiff)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers

void CTestView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	int b;
	CFileDialog fdlg(true,NULL,"openfile",NULL,"BMP|*.bmp");
	CString Strfilename;
	f=fopen("time.txt","w");
	if(fdlg.DoModal()==IDOK)
	{
		Strfilename=fdlg.GetPathName();

		//MessageBox(filename);
	}
	testDib.LoadBmp(Strfilename.GetBuffer(0));
	CClientDC dc(this);
    //CDibSection testDib1(testDib);//�����ƻs�v��
	/*//�]�w�j�p�b�ƻs�v��
 	CDibSection testDib1;
	testDib1.Create(640,480,24); 
	testDib1.Copy(testDib);
	*/
	testDib.Draw(dc,0,0,testDib.Width(),testDib.Height());   
	b=testDib.ScanBytes(testDib.Width(),testDib.Depth());
	p=fopen("t.txt","w");
	/*
	fprintf(p,"%d\n",testDib.Width());
    fprintf(p,"%d\n",testDib.Height());
	fprintf(p,"%d\n",testDib.Depth());
	*/
	COLORREF c1=dc.GetPixel(point);
	/*
	fprintf(p,"%d\n",GetRValue(c1));
	fprintf(p,"%d\n",GetGValue(c1));
	fprintf(p,"%d\n",GetBValue(c1));
	*/
	start=point;
	fprintf(p,"%d\t",start.x);
	fprintf(p,"%d\n",start.y);
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	end=point;
	fprintf(p,"%d\t",end.x);
	fprintf(p,"%d\n",end.y);
	CView::OnLButtonUp(nFlags, point);
}

void CTestView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	void CDibSection::Copy(const CDibSection &dib, CPoint to, CSize size, CPoint from)
{
	BitBlt(CDibDC(*this), to.x, to.y, size.cx, size.cy, CDibDC(dib), from.x, from.y, SRCCOPY);
}
*/
	int R,G,B;
	CSize size;
	CClientDC dc(this);
 	CDibSection testDib1;
	size.cx=end.x-start.x;//���I�y��-�_�l�y��
	size.cy=end.y-start.y;//�ܦ�����d��
	//�]�w�s�Ϲ��b�e���_�l��m
	CPoint from;
	from.x =0;
	from.y =0;
	testDib1.Create(640,480,24); 
	//�ƻs(�ӷ�����,�ت��_�l��m,�d��j�p,�ӷ��_�l��m)
	testDib1.Copy(testDib,from,size,start);
	testDib1.Fade(testDib1,256);//���ܩ��G��
	//const BYTE *q=(const BYTE *)testDib1.GetBits(point.x,point.y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(�ѦҥΪk)
	BYTE *q=(BYTE *)testDib1.GetBits(point.x,point.y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
	B=*q++;
	G=*q++;
	R=*q++;
	fprintf(p,"%d\n",R);
	fprintf(p,"%d\n",G);
	fprintf(p,"%d\n",B);
	fclose(p);
	testDib1.Draw(dc,0,0,testDib.Width(),testDib.Height()); //�e��
	CView::OnRButtonDown(nFlags, point);
}

void CTestView::Onchange()//���k½�� 
{		
	int x,y;
	int Width,Height;
	CSize size;
	struct timeb t,t1;
	CClientDC dc(this);
 	CDibSection testDib1(testDib);//�����ƻs�v��
	Width=testDib1.Width();
	Height=testDib.Height();
	f=fopen("time.txt","w");
	ftime(&t);
	for(y=0;y<Height;y++)
		for(x=0;x<Width;x++)
		{
			BYTE *q1=(BYTE *)testDib1.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q=(BYTE *)testDib.GetBits(Width-1-x,y);
			//�n�ഫ�N�nR,G,B�@�_��
			*q1++=*q++;
			*q1++=*q++;
			*q1++=*q++;
		}
	ftime(&t1);
	fprintf(f,"%d\t%d\n%d\t%d\n",t.time,t.millitm,t1.time,t1.millitm);
	fclose(f);
	testDib1.Draw(dc,0,0,testDib.Width(),testDib.Height()); 
}

void CTestView::Onchange1()//�W�U½�� 
{
	// TODO: Add your command handler code here
		int x,y;
	int Width,Height;
	CSize size;
	CClientDC dc(this);
 	CDibSection testDib1(testDib);//�����ƻs�v��
	Width=testDib1.Width();
	Height=testDib.Height();
	for(x=0;x<Width;x++)
		for(y=0;y<Height;y++)
		{
			BYTE *q1=(BYTE *)testDib1.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q=(BYTE *)testDib.GetBits(x,Height-1-y);
			//�n�ഫ�N�nR,G,B�@�_��
			*q1++=*q++;
			*q1++=*q++;
			*q1++=*q++;
		}
	testDib1.Draw(dc,0,0,testDib.Width(),testDib.Height()); 
}

void CTestView::Oncopchange()//�q�e���^����ưe�ܪ��� 
{
	// TODO: Add your command handler code here
	int x,y;
	int Width,Height;
	CDibSection testDib1;
	testDib.LoadBmp("C:\\Documents and Settings\\jash\\�ୱ\\�q�ϩM�칳���ȩM²���ƻs\\SAMPLE.BMP");
	CClientDC dc(this);
	testDib.Draw(dc,0,0,testDib.Width(),testDib.Height());
	testDib1.Create(640,480,24);
	Width=testDib1.Width();
	Height=testDib.Height();
	for(x=0;x<Width;x++)
		for(y=0;y<Height;y++)
		{
			BYTE *q1=(BYTE *)testDib1.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			//BYTE *q=(BYTE *)testDib.GetBits(x,Height-1-y);
			//�n�ഫ�N�nR,G,B�@�_��
			COLORREF c1=dc.GetPixel(x,Height-1-y);
			*q1++=GetBValue(c1);
			*q1++=GetGValue(c1);
			*q1++=GetRValue(c1);
		} 
	testDib1.Draw(dc,0,0,testDib.Width(),testDib.Height());
	testDib1.SaveBmp("C:\\t.bmp");
	MessageBox("saved");
}

void CTestView::Onchangegray() 
{
	int x,y;
	int Width,Height;
	int R,G,B;
	struct timeb t,t1;
	CFileDialog fdlg(true,NULL,"openfile",NULL,"BMP|*.bmp");
	CString Strfilename;
	f=fopen("time.txt","w");
	if(fdlg.DoModal()==IDOK)
	{
		Strfilename=fdlg.GetPathName();

		//MessageBox(filename);
	}
	CDibSection testDib1;
	ftime(&t);
	testDib.LoadBmp(Strfilename.GetBuffer(0));
	Width=testDib.Width();
	Height=testDib.Height();
	testDib1.Create(Width,Height,24);
	

	CClientDC dc(this);
	for(x=0;x<Width;x++)
	{
		for(y=0;y<Height;y++)
		{
			BYTE *q1=(BYTE *)testDib.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q=(BYTE *)testDib1.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			B=*q1++;
			G=*q1++;
			R=*q1++;
			*q++=(0.299*R+0.587*G+0.114*B);
			*q++=(0.299*R+0.587*G+0.114*B);
			*q++=(0.299*R+0.587*G+0.114*B);
		}
	}

	testDib1.Draw(dc,0,0,testDib.Width(),testDib.Height());	
	ftime(&t1);
	fprintf(f,"�_�l�ɶ�%d(s)\t%d(ms)\n�����ɶ�%d(s)\t%d(ms)\n",t.time,t.millitm,t1.time,t1.millitm);
	fclose(f);
}

void CTestView::Ondiff()//�۴�_�ۦ�
{
	// TODO: Add your command handler code here
	CFileDialog fdlg(true,NULL,"openfile",NULL,"BMP|*.bmp");
	int x,y;
	int R1,G1,B1;
	int R2,G2,B2;
	int R3,G3,B3;
	int R4,G4,B4;
	int R5,G5,B5;
	int Width,Height;
	CDibSection Dib1,Dib2,Dib3,Dib4;
	CString StrFileName1,StrFileName2,StrFileName3;
	if(fdlg.DoModal()==IDOK)
	{
		StrFileName1=fdlg.GetPathName();
		Dib1.LoadBmp(StrFileName1.GetBuffer(0));
	}
	else
	{
		return;
	}
	////////////////////////
	if(fdlg.DoModal()==IDOK)
	{
		StrFileName2=fdlg.GetPathName();
		Dib2.LoadBmp(StrFileName2.GetBuffer(0));
	}
	else
	{
		return;
	}
	////////////////////////
	if(fdlg.DoModal()==IDOK)
	{
		StrFileName3=fdlg.GetPathName();
		Dib3.LoadBmp(StrFileName3.GetBuffer(0));
	}
	else
	{
		return;
	}
	///////////////////
	Width=Dib1.Width();
	Height=Dib1.Height();
	Dib4.Create(Width,Height,24);
	CClientDC dc(this);
	for(x=0;x<Width;x++)
	{
		for(y=0;y<Height;y++)
		{
			BYTE *q1=(BYTE *)Dib1.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q2=(BYTE *)Dib2.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q3=(BYTE *)Dib3.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			BYTE *q4=(BYTE *)Dib4.GetBits(x,y);//�Q�Ϊ��󥻨��Ҵ��Ѥ�������ƨ��o�@�ӹ����� R,G,B(���ХΪk)
			B1=*q1++;
			G1=*q1++;
			R1=*q1++;
			/////////
			B2=*q2++;
			G2=*q2++;
			R2=*q2++;
			/////////
			B3=*q3++;
			G3=*q3++;
			R3=*q3++;
			/////////
			B4=abs(B1-B2);
			G4=abs(G1-G2);
			R4=abs(R1-R2);
			/////////////////
			B5=abs(B2-B3);
			G5=abs(G2-B3);
			R5=abs(R2-R3);
			/////////////////
			*q4++=B4*B5/255;
			*q4++=G4*G5/255;
			*q4++=R4*R5/255;
		}
	}
	Dib4.Draw(dc,0,0,Dib4.Width(),Dib4.Height());	
}
