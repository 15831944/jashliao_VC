// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProGram2.h"
#include "ResultDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultDlg dialog


CResultDlg::CResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDlg)
	DDX_Control(pDX, IDC_LIST1, m_List1);
	//}}AFX_DATA_MAP
}
BOOL CResultDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_List1.AddString(" ");
	m_List1.AddString("==============================================================�������=========================================================");
	m_List1.AddString(" ");
	m_List1.AddString(" ");
	CString black="      ";//���������ߵľ���
	///
	///
	///��ʾ����

/*	// TODO: Add extra initialization here
	m_List1.AddString("--------------------�����ʾ���ڲ���---------------");
	m_List1.AddString("  ");
	m_List1.AddString("_____________________________________________________");
	m_List1.AddString(" . \t 454545 4545");
	m_List1.AddString(" . 11    11");
	m_List1.AddString(" . 22    22");
	m_List1.AddString(" . ");
	m_List1.AddString(" . ");
	m_List1.AddString(" . ");
	m_List1.AddString(" . ");
	m_List1.AddString(" . ");
	m_List1.AddString("____________________________________________________");
	
	MatrixOut(m_Matrix[m_matrixNum-1],black);
	MatrixOut(m_Matrix[m_matrixNum-1],black);*/

	//for(int i=1;i<=m_matrixNum;i++)
	//{
	//	MatrixOut(m_Matrix[i-1],"    ");
	//}
	//////////////////////////////////////
	///
	///������
	if(m_resultkind==1)
	{//���ɷַ���������
		m_List1.AddString("��׼����������:");
		MatrixOut(m_Matrix[0],black);
		m_List1.AddString(" ");
		CString s;
		s.Format("ǰ%d�����ɷֵ��������������ʺ��ۻ�������:",m_J[1]);
		m_List1.AddString(s);
		m_List1.AddString("����һ��Ϊ���������ڶ���Ϊ�����ʣ�������Ϊ�ۻ������ʣ�");
		MatrixOut(m_Matrix[1],black);
		m_List1.AddString(" ");
		s.Format("ǰ%d�����ɷֵ���������(���ж�Ӧһ��ָ��):",m_J[1]);
		m_List1.AddString(s);
		MatrixOut(m_Matrix[2],black);
		m_List1.AddString(" ");
		m_List1.AddString("�����غ���(�ж�Ӧָ��,�ж�Ӧ���ɷ�):");
		MatrixOut(m_Matrix[4],black);
		m_List1.AddString(" ");
		s.Format("������ǰ%d�����ɷֵ÷�ֵ:",m_J[1]);
		m_List1.AddString(s);
		MatrixOut(m_Matrix[3],black);

	}
	else if(m_resultkind==2)
	{//��Ӧ����������
		CMatrix a(m_Matrix[0]);
		CString s;
		s.Format("%d�����������ɷֵ÷�ֵ:",a.GetNumRows());
		m_List1.AddString(s);
		MatrixOut(m_Matrix[0],black);		
		m_List1.AddString(" ");
		a=m_Matrix[1];
		s.Format(" R�������غ���:");
		m_List1.AddString(s);
		MatrixOut(m_Matrix[1],black);
		m_List1.AddString(" ");
		a=m_Matrix[2];
		s.Format("%d����״�����ɷֵ÷�:",a.GetNumRows());
		m_List1.AddString(s);
		MatrixOut(m_Matrix[2],black);
		m_List1.AddString(" ");
		a=m_Matrix[3];
		s.Format(" Q�������غ���:",a.GetNumRows());
		m_List1.AddString(s);
		MatrixOut(m_Matrix[3],black);
		m_List1.AddString(" ");
	}
	else if(m_resultkind==3)
	{//���ӷ���������
		if(m_J[0])
		{
			m_List1.AddString("��׼������");
			MatrixOut(m_Matrix[0],black);
		}
		if(m_J[1])
		{
			m_List1.AddString(" ");
			m_List1.AddString("��ؾ���:");
			MatrixOut(m_Matrix[1],black);
		}
		if(m_J[2])
		{
			m_List1.AddString(" ");
			m_List1.AddString("����ֵ����������(��һ��Ϊ�����������Ϊ��Ӧ��������):");
			MatrixOut(m_Matrix[2],black);			
		}
		if(m_J[3])
		{
			m_List1.AddString(" ");
			m_List1.AddString("�����غ���:");
			MatrixOut(m_Matrix[3],black);			
		}
		m_List1.AddString(" ");
		m_List1.AddString("����ģ��:");
		CMatrix a(m_Matrix[4]);
		if(a.GetNumCols()>8)
			MatrixOut(m_Matrix[4],black,1,false);
		else
			MatrixOut(m_Matrix[4],black,1,true);
		if(m_J[5])
		{
			m_List1.AddString(" ");
			m_List1.AddString("��ת����������غ���:");
			MatrixOut(m_Matrix[5],black);
		}
		m_List1.AddString(" ");
		m_List1.AddString("���ӵ÷�(�ж�Ӧ����):");
		MatrixOut(m_Matrix[6],black);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CResultDlg, CDialog)
	//{{AFX_MSG_MAP(CResultDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultDlg message handlers

void CResultDlg::TranMemberNumber(int resultkind, CMatrix Matrix[], int matrixNum,int J[])
{
	m_resultkind=resultkind;
	m_matrixNum=matrixNum;
	m_Matrix=new CMatrix[m_matrixNum];
	m_Matrix=Matrix;
	m_J=J;
}
///
///
///���������������غ�������һ�����һ����󣬵ڶ������������
void CResultDlg::MatrixOut(CMatrix matrix,CString black)
{
	if(matrix==NULL)
	{
		MessageBox("�վ���");
		return;
	}
	int n=matrix.GetNumRows(),p=matrix.GetNumCols();
	int i,j;
	if(matrix.GetNumCols()>8)
	{
		CMatrix matrix1(n,8);
		CMatrix matrix2(n,p-8);
		for(i=0;i<n;i++)
		{
			for(j=0;j<8;j++)
			{
				matrix1.SetElement(i,j,matrix.GetElement(i,j));
			}
			for(j=0;j<p-8;j++)
			{
				matrix2.SetElement(i,j,matrix.GetElement(i,8+j));
			}
		}
		MatrixOut(matrix1,black);
		MatrixOut(matrix2,black);
	}
	else
	{
		//blackΪ���������ߵľ���
		CString s,member,t="    ";//tΪ����������֮��ľ���
		s=black;
		for(i=0;i<=p+1;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);//�������ǰ��ĺ���
		for(i=0;i<n;i++)
		{
			s=black+black;
			for(j=0;j<p;j++)
			{
				member.Format("%f",(double)matrix.GetElement(i,j));// ȡ����Ԫ��
				s=s+member;
				s=s+t;
			}
			m_List1.AddString(s);
		}
		s=black;
		for(i=0;i<=p+1;i++)
			s=s+"~~~~~~~~~~~";
	
		m_List1.AddString(s);//����������ĺ���
		m_List1.AddString("   ");
		
	}	
}

void CResultDlg::MatrixOut(CMatrix matrix, CString black, int matrixNum, bool isLastMatrix)
{
	int i,j;

	if(matrix.GetNumCols()==9)
	{
		CString s,member,t="    ";
		s=black;
		for(i=0;i<=9;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		s=black+black;
		for(i=1;i<8;i++)
		{
			
			member.Format("����%d",(matrixNum-1)*8+i);
			s=s+member;
			s=s+t+t;
		}
		s=s+"��ͬ��";
		m_List1.AddString(s);
		for(i=0;i<matrix.GetNumRows();i++)
		{
			s=black+black;
			for(j=0;j<8;j++)
			{
				member.Format("%f",(double)matrix.GetElement(i,j));
				s=s+member;
				s=s+t;
			}
			m_List1.AddString(s);
		}
		s=black;
		for(i=0;i<=9;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		s=black;
		for(i=0;i<=2;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		s=black+black;
		s=s+"���ⷽ��";
		m_List1.AddString(s);
		for(i=0;i<matrix.GetNumCols();i++)
		{
			s=black+black;
			member.Format("%f",(double)matrix.GetElement(i,8));
			s=s+member;
			s=s+t;
			m_List1.AddString(s);
		}
		s=black;
		for(i=0;i<=2;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
	}
	else if(matrix.GetNumCols()<=8 && isLastMatrix==true)
	{
		CString s,member,t="   ";
		int i,j;
		int n=matrix.GetNumRows();
		int p=matrix.GetNumCols();
		s=black;
		for(i=0;i<p+1;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		s=black+black;
		for(i=0;i<p-2;i++)
		{
			member.Format("����%d",(matrixNum-1)*8+i+1);
			s=s+member;
			s=s+t+t;
		}
		s=s+"��ͬ��";
		s=s+t+t;
		s=s+"���ⷽ��";
		m_List1.AddString(s);
		for(i=0;i<n;i++)
		{
			s=black+black;
			for(j=0;j<p;j++)
			{
				member.Format("%f",(double)matrix.GetElement(i,j));
				s=s+member;
				s=s+t;
			}
			m_List1.AddString(s);
		}
		s=black;
		for(i=0;i<p+1;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
	}
	else if(matrix.GetNumCols()>8)
	{	
		CString s,member,t="    ";
		int i,j;
		int n=matrix.GetNumRows();
		int p=matrix.GetNumCols();
		CMatrix matrixA(n,p-8);

		for(i=0;i<n;i++)
		{
			for(j=8;j<p;j++)
			{
				matrixA.SetElement(i,j-8,matrix.GetElement(i,j));//����8�к����ֵ������һ��������
			}
		}
		//���ǰ8�У�
		s=black;
		for(i=0;i<=9;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		s=black+black;
		for(i=1;i<=8;i++)
		{
			
			member.Format("����%d",(matrixNum-1)*8+i);
			s=s+member;
			s=s+t+t;
		}
		m_List1.AddString(s);
		for(i=0;i<8;i++)
		{
			s=black+black;
			for(j=0;j<8;j++)
			{
				member.Format("%f",(double)matrix.GetElement(i,j));
				s=s+member;
				s=s+t;
			}
			m_List1.AddString(s);
		}
		s=black;
		for(i=0;i<=9;i++)
			s=s+"~~~~~~~~~~~";
		m_List1.AddString(s);
		if(matrixA.GetNumCols()>8)
			MatrixOut(matrixA,black,matrixNum+1, false);
		else
			MatrixOut(matrixA,black,matrixNum+1, true);

	}
}





