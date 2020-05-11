// PaPaGoString.h: interface for the CPaPaGoString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAPAGOSTRING_H__53E9CABA_2719_41B3_AC75_6CEAC620AB9F__INCLUDED_)
#define AFX_PAPAGOSTRING_H__53E9CABA_2719_41B3_AC75_6CEAC620AB9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GPSString.h"
class CPaPaGoString : public CGPSString   
{
public:
	CPaPaGoString();
	CPaPaGoString(const CString &databuf);//�غc�l���
	CPaPaGoString(const char *databuf);//�غc�l���
	long GetXCoordinate(void);
	long GetYCoordinate(void);
	void CalculateXY();
	virtual ~CPaPaGoString();
private:
protected:
	 long m_XCoordinate;
	 long m_YCoordinate;
};

#endif // !defined(AFX_PAPAGOSTRING_H__53E9CABA_2719_41B3_AC75_6CEAC620AB9F__INCLUDED_)
