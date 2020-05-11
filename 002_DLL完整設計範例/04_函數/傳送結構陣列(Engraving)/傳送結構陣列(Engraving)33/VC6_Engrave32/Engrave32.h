// Engrave32.h : main header file for the ENGRAVE32 DLL
//

#if !defined(AFX_ENGRAVE32_H__25E608BA_BD32_4ABB_BD1C_D2DE469C37CF__INCLUDED_)
#define AFX_ENGRAVE32_H__25E608BA_BD32_4ABB_BD1C_D2DE469C37CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
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
/////////////////////////////////////////////////////////////////////////////
// CEngrave32App
// See Engrave32.cpp for the implementation of this class
//

class CEngrave32App : public CWinApp
{
public:
	CEngrave32App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEngrave32App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEngrave32App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENGRAVE32_H__25E608BA_BD32_4ABB_BD1C_D2DE469C37CF__INCLUDED_)
