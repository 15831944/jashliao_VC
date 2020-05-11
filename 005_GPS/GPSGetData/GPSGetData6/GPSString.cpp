// GPSString.cpp: implementation of the CGPSString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GPSGetData.h"
#include "GPSString.h"
#include <string.h>
#include <stdlib.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGPSString::CGPSString()//�غc�l���
{
	m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	m_strInData="";
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	m_DataOK=-1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
	m_fltRate=0.0f;//�ثe�t��
}
CGPSString::CGPSString(const CString &databuf)//�غc�l���
{
	m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	m_strInData=databuf;
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	m_DataOK=-1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
	m_fltRate=0.0f;//�ثe�t��
}
CGPSString::CGPSString(const char *databuf)//�غc�l���
{
	m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	m_strInData=databuf;
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	m_DataOK=-1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
	m_fltRate=0.0f;//�ثe�t��
}
void CGPSString::SetData(const CString &databuf)//��J��ƨ��
{
	m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	m_strInData=databuf;
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	m_DataOK=-1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
	m_fltRate=0.0f;//�ثe�t��
}
void CGPSString::SetData(const char *databuf)//��J��ƨ��
{
	m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	m_strInData=databuf;
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	m_DataOK=-1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
	m_fltRate=0.0f;//�ثe�t��
}
void CGPSString::Operation()//���Ѹ�ƹB����
{
	char *chrInBuf;//�إ߼Ȧs��J��ƫ���
	char *chrOutBuf;//�إ߼Ȧs��X���θ�ƫ���
	long lngLen=0;//�إߪ��׼Ȧs�ܼ�
	long lngGetLen1=0;//������ƪ���
	long lngGetLen2=0;//�Ѿl��ƪ���
	CString strInData="";//m_strInData����
	CString strRemain="";//�Ѿl���
	long lngIndex=0;//����ƺX��
	CString strbuf="";//�إߤ�����Y��ƼȦs��
	char chrSeps[]=",";//�إߤ��βŸ�
	m_strHead="";//���Y�ܼ�
	m_strTime="";//�ɶ��ܼ�
	m_strLongitude="";//�g���ܼ�
	m_strLatitude="";//�n���ܼ�
	m_strS_N="";//�n�_�b�y�ܼ�
	m_strE_W="";//�F��b�y�ܼ�
	/////////////////////////////////////
	chrInBuf=new char('\0');//���Ъ�l��
	chrOutBuf=new char('\0');//���Ъ�l��
	strInData=m_strInData;
	chrInBuf=strInData.GetBuffer(0);//�ᤩ���
	////////////////////////////////////
	chrOutBuf=strtok(chrInBuf,chrSeps);//�^�����Y
	m_strHead=chrOutBuf;//��X�ܦ����ܼ�
	strbuf="$GPGGA";
	if(m_strHead==strbuf)
	{
		m_lngType=0;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
	}
	else
	{
		strbuf="$GPGLL";
		if(m_strHead==strbuf)
		{
			m_lngType=1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
		}
		else
		{
			strbuf="$GPRMC";
			if(m_strHead==strbuf)
			{
				m_lngType=2;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
			}
			else
			{
				m_lngType=-1;//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
			}
		}
	}
	if(m_lngType>=0)
	{
		strInData=m_strInData;//���X��Ӹ��
		chrInBuf=strInData.GetBuffer(0);//�ᤩ���
		lngLen=strlen(chrInBuf);
		chrOutBuf=strtok(chrInBuf,chrSeps);//�^�����Y
		lngGetLen1=strlen(chrOutBuf);//������ƪ���
		lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
		strRemain=m_strInData.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
		lngIndex++;
		while(chrOutBuf!=NULL)
		{
			lngIndex++;
			strInData=strRemain;//���X��Ӹ��
			chrInBuf=strInData.GetBuffer(0);//�ᤩ���
			lngLen=strlen(chrInBuf);
			chrOutBuf=strtok(chrInBuf,chrSeps);//�^��
			lngGetLen1=strlen(chrOutBuf);//������ƪ���
			lngGetLen2=lngLen-lngGetLen1;//�Ѿl��ƪ���
			if(lngGetLen2!=0)
			{
				strRemain=strRemain.Mid(lngGetLen1+1,lngGetLen2);//�Ѿl���
			}
			switch(m_lngType)//�q�T�榡�����ܼ�GPGAA=0,GPGLL=1,GPRMC=2,�Ұʮɬ�-1
			{
				case 0://GPGAA=0
					switch(lngIndex)
					{
						case 2:
							m_strTime=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 3:
							m_strLatitude=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 4:
							m_strS_N=chrOutBuf;
							break;
						case 5:
							m_strLongitude=chrOutBuf;
							break;
						case 6:
							m_strE_W=chrOutBuf;
							break;
						case 7:
							int buf;
							buf=atoi(chrOutBuf);
							if(buf!=0)
								m_DataOK=1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							else
								m_DataOK=0;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							break;
					}
					break;
				case 1://GPGLL=1
					switch(lngIndex)
					{
						case 2:
							m_strLatitude=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 3:
							m_strS_N=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 4:
							m_strLongitude=chrOutBuf;
							break;
						case 5:
							m_strE_W=chrOutBuf;
							break;
						case 6:
							m_strTime=chrOutBuf;
							break;
						case 7:
							int buf;
							buf=*(chrOutBuf+0);
							if(buf==65)
								m_DataOK=1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							else
								m_DataOK=0;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							break;
					}				
					break;
				case 2://GPRMC=2
					switch(lngIndex)
					{
						case 2:
							m_strTime=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 3:
							int buf;
							buf=*(chrOutBuf+0);
							if(buf==65)
								m_DataOK=1;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							else
								m_DataOK=0;//��ƥ��T�ʪ�l���A-1�A0�����~�A1�����T
							break;
						case 4:
							m_strLatitude=chrOutBuf;//��X�ܦ����ܼ�
							break;
						case 5:
							m_strS_N=chrOutBuf;
							break;
						case 6:
							m_strLongitude=chrOutBuf;
							break;
						case 7:
							m_strE_W=chrOutBuf;
							break;
						case 8:
							m_fltRate=(float)atof(chrOutBuf);
					}			
					break;
			}
			if(lngGetLen2==0)
			{
				break;
			}
		}
	}
	////////////////////////////////////
//	delete []chrInBuf;
//	delete []chrOutBuf;
	////////////////////////////////////
	if(m_DataOK!=1)
	{
		m_strLongitude="";
		m_strLatitude="";
	}
}
CString CGPSString::GetHead()//���o���Y���
{
	return m_strHead;
}
CString CGPSString::GetTime()//���o�ɶ����
{
	return m_strTime;
}
CString CGPSString::GetLongitude()//���o�g�ר��
{
	return m_strLongitude;
}
CString CGPSString::GetLatitude()//���o�n�ר��
{
	return m_strLatitude;
}
CString CGPSString::GetDirection()//���o��V���
{
	CString buf;
	buf=m_strS_N;
	buf=buf+"_";
	buf=buf+m_strE_W;
	return buf;
}
float CGPSString::GetRate()//���o�ثe�t�ר��
{
	return m_fltRate;
}
int CGPSString::GetDataOK()//���o��ƥ��T��
{
	return m_DataOK;
}
CGPSString::~CGPSString()//�Ѻc�l���
{

}
