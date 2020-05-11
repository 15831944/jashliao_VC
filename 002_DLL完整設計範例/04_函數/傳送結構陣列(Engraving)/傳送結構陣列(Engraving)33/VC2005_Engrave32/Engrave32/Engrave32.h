// Engrave32.h : Engrave32 DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�
#include "GlobalVar.h"
#include "RotateVector.h"
#include "SmoothSolution.h"
#include "RipAngle2Vector.h"
//////////////////////////////////////
#define EXPORTED_DLL_FUNCTION \
 __declspec(dllexport) __stdcall
long EXPORTED_DLL_FUNCTION EngInitial(long lngBlockAmount,double tolerance,long Direction);//���oBlock�`�ơA�ðʺA�t�m�O����w�ΨӦs��C��Block��Entity�ƶq
long EXPORTED_DLL_FUNCTION EngGetValue(EngarveElement *p,long lngBlock,long lngAmount);//��ư}�C���СF��ư}�C�ݩ�ĴX��lngBlock�F�}�C�j�p
long EXPORTED_DLL_FUNCTION EngLineLineSolve(const CInputData &BaseInputData,const CInputData &RipInputData,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�u�P�u�D����
long EXPORTED_DLL_FUNCTION EngLineArcSolve(const CArc &BaseArc,const CLine &RipLine,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�u�P�꩷�D����
long EXPORTED_DLL_FUNCTION EngArcLineSolve(const CLine &BaseLine,CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�꩷�P�u�D����
long EXPORTED_DLL_FUNCTION EngArcArcSolve(const CArc &BaseArc,const CArc &RipArc,const CPoint3D &RipPoint3D,CCircle *AnsCircle);//�꩷�P�꩷�D����
long EXPORTED_DLL_FUNCTION ArcParagraph(CArc &data,const double tolerance);//�꩷�D���q�I
long EXPORTED_DLL_FUNCTION LineParagraph(CLine &data,const double tolerance);//�u�D���q�I
long EXPORTED_DLL_FUNCTION EngCalculate();//�p��֤�
long EXPORTED_DLL_FUNCTION BubbleSort(double **p,long n);//�G���}�C�Ƨ�
//////////////////////////////////////////////////////////////////////////////////
// CEngrave32App
// �o�����O����@�аѾ\ Engrave32.cpp
//

class CEngrave32App : public CWinApp
{
public:
	CEngrave32App();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
