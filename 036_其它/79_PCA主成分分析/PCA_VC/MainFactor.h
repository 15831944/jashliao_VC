#include "Matrix.h"
// MainFactor.h: interface for the MainFactor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFACTOR_H__BF4F7477_0675_4DFE_AA61_B58B2730B2E3__INCLUDED_)
#define AFX_MAINFACTOR_H__BF4F7477_0675_4DFE_AA61_B58B2730B2E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MainFactor  
{
public:
	MainFactor();
	virtual ~MainFactor();
	CMatrix m_Matrix1;			//ԭʼ����
	CMatrix m_Matrix2;			//��׼����������
	CMatrix m_Result1;			//������ɷֵ��������������ʺ��ۼƹ�����
	int m_mainNum;//��¼���ɷݸ���
	CMatrix m_Result2;			//������ɷ�ϵ��
	CMatrix m_Result3;			//�����Ʒ�����ɷֵ÷�ֵ
	CMatrix m_Result4;			//���ɷ��غ�����
	double m_p;                 //�û�����������
	int m_t;					//���ɷַ�������ģ�ͣ�0��ʾѡЭ������1��ʾ�������

	CMatrix GetL(CMatrix B);			//���������
	CMatrix GetStX();	       //�������ݱ�׼��
	CMatrix GetR();			//�������������
	CMatrix GetS();         //��������Э������
	void	Analyze1();		//�������ɷַ����Ľ��
	MainFactor(CMatrix A,double p,int Tag);   //���캯��
	void showMatrix(CMatrix a);
};

#endif // !defined(AFX_MAINFACTOR_H__BF4F7477_0675_4DFE_AA61_B58B2730B2E3__INCLUDED_)
