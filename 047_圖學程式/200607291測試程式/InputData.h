#pragma once
#include "Arc.h"
#include "Line.h"
class CInputData//�Ψӱ���vb���c���ഫ������
{
public:
	long m_lngBlock;//�Ψ��x�s�ݩ����Block
	long m_lngEntity;//�Ψ��x�s�ݩ����Entity
	long m_lngLineArc;//�Ψ��x�s���A0->Line�F1->Arc
	long CCW;//������V�A0->�k�F1->��
	long Direction;//�������f�A0->���F1->�f
	CLine m_Line;
	CArc m_Arc;
	CInputData(void);
	void Reset(void);
public:
	~CInputData(void);
};
