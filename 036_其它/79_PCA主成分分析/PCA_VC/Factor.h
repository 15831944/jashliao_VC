#include "Matrix.h"
// Factor.h: interface for the Factor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTOR_H__C5426C88_4CD6_46BF_B320_0CE445B18713__INCLUDED_)
#define AFX_FACTOR_H__C5426C88_4CD6_46BF_B320_0CE445B18713__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Factor  
{
public:
	Factor();
	Factor(CMatrix mx, double dep_m);
	////////////////////////////
	CMatrix X;//ԭ���ݣ����Ϊ��׼���������
	double dep_m;//������
	int n;//��¼Ԫ��������
	int p;//��¼Ԫ��������
	double *h2,*a2;///ȷ������h2��¼�����A�����һ��
	double m_ColsOfA;//��¼�������A��ǰ������
    CMatrix R;//��ؾ���P*P
	CMatrix te_R;//����ֵ����������
	CMatrix A;//�����غ���p*p
	CMatrix B;//������ת����������غ���p*m
	CMatrix F;//���ӵ÷�m_ColsOfA*p
	///////////////////////////
	
	void Run(void);
	virtual ~Factor();

};

#endif // !defined(AFX_FACTOR_H__C5426C88_4CD6_46BF_B320_0CE445B18713__INCLUDED_)
