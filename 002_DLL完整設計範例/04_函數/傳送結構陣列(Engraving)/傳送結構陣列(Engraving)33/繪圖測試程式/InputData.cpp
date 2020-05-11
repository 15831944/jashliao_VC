#include "stdafx.h"
#include "SDIShow.h"
#include "InputData.h"

CInputData::CInputData(void)
{
	m_lngBlock=-1;//�Ψ��x�s�ݩ����Block
	m_lngEntity=-1;//�Ψ��x�s�ݩ����Entity
	m_lngLineArc=-1;//�Ψ��x�s���A0->Line�F1->Arc
	CCW=-1;//������V�A0->�k�F1->��
	Direction=-1;//�������f�A0->���F1->�f
	CPoint3D Point3D(0.0f,0.0f,0.0f); 
	m_Line.SetData(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f) ;
	m_Arc.SetData(Point3D,0.0f,0.0f,0.0f);
}

CInputData::~CInputData(void)
{
}
void CInputData::Reset(void)
{
	m_lngBlock=-1;//�Ψ��x�s�ݩ����Block
	m_lngEntity=-1;//�Ψ��x�s�ݩ����Entity
	m_lngLineArc=-1;//�Ψ��x�s���A0->Line�F1->Arc
	CCW=-1;//������V�A0->�k�F1->��
	Direction=-1;//�������f�A0->���F1->�f
	CPoint3D Point3D(0.0f,0.0f,0.0f); 
	m_Line.SetData(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f) ;
	m_Arc.SetData(Point3D,0.0f,0.0f,0.0f);
}
