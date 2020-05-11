// GPSString.h: interface for the CGPSString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSSTRING_H__89A6E39B_9D84_4197_862B_D1A7AC0901FB__INCLUDED_)
#define AFX_GPSSTRING_H__89A6E39B_9D84_4197_862B_D1A7AC0901FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//���ո��
//$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M, , , ,0000*18
//$GPGLL,3723.2475,N,12158.3416,W,161229.487,A*2C
//$GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10
class CGPSString  
{
public:
	CString m_strInData;//��J����ܼ�
	CGPSString();//�غc�l���
	CGPSString(const CString &databuf);//�غc�l���
	CGPSString(const char *databuf);//�غc�l���
	void SetData(const CString &databuf);//��J��ƨ��
	void SetData(const char *databuf);//��J��ƨ��
	void Operation();//���Ѹ�ƹB����
	CString GetHead();//���o���Y���
	CString GetTime();//���o�ɶ����
	CString GetLongitude();//���o�g�ר��
	CString GetLatitude();//���o�n�ר��
	CString GetDirection();//���o��V���
	virtual ~CGPSString();//�Ѻc�l���
private:
	long m_lngType;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
protected:
	CString m_strHead;//���Y�ܼ�
	CString m_strTime;//�ɶ��ܼ�
	CString m_strLongitude;//�g���ܼ�
	CString m_strLatitude;//�n���ܼ�
	CString m_strS_N;//�n�_�b�y�ܼ�
	CString m_strE_W;//�F��b�y�ܼ�
};

#endif // !defined(AFX_GPSSTRING_H__89A6E39B_9D84_4197_862B_D1A7AC0901FB__INCLUDED_)
