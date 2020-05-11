// CircleRightLeft.h: interface for the CCircleRightLeft class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLERIGHTLEFT_H__C148B2B5_636E_40BD_81C5_E149DEDDDE87__INCLUDED_)
#define AFX_CIRCLERIGHTLEFT_H__C148B2B5_636E_40BD_81C5_E149DEDDDE87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InputData.h"
#include "Vector.h"
class CCircleRightLeft  
{
public:
	CCircleRightLeft();
	CInputData m_InputData;
	CCircle m_Circle;
	bool Check();//��X���
	void SetData(const CInputData &ID,const CCircle &CC);//��l�ƨ��
	virtual ~CCircleRightLeft();
private:
	long m_CCW;//������V�A0->�k�F1->��
	long m_Direction;//�������f�A0->���F1->�f
	long m_lngLineArc;//�Ψ��x�s���A0->Line�F1->Arc
protected:
	bool m_blnAns;//�����B�⵲�G
	void calculate();

};

#endif // !defined(AFX_CIRCLERIGHTLEFT_H__C148B2B5_636E_40BD_81C5_E149DEDDDE87__INCLUDED_)
