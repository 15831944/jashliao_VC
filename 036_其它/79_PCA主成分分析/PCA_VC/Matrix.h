// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__252F1FEF_F0A7_4E2A_9DFC_DE56FB93288C__INCLUDED_)
#define AFX_MATRIX_H__252F1FEF_F0A7_4E2A_9DFC_DE56FB93288C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatrix  
{
public:
	 ////
	////
	////���������
	CMatrix();//ȱʡֵ�Ĺ��캯��
	CMatrix(int nRows,int nCols);//ָ������
	CMatrix(int nRows,int nCols,double value[]);//ָ�����ݹ��캯��
	CMatrix(int nSize);//�����캯��
	CMatrix(int nSize,double value[]);//ָ�����ݽṹ�ķ����캯��
	CMatrix(const CMatrix &other);//�������캯��
	virtual ~CMatrix();//��������
	bool Init(int nRows,int nCols);//��ʼ������
	bool MakeUnitMatrix(int nSize);//�������ʼ��Ϊ��λ��
	//////
	/////
	/////��������ʾ
	//���ַ���ת��Ϊ��������
	//������ת��Ϊ�ַ���
	//������ָ����ת��Ϊ�ַ���
	//������ָ����ת��Ϊ�ַ���///����
	/////
	////
	////Ԫ����ֵ����
	//����ָ��Ԫ�ص�ֵ
	bool SetElement(int nRow, int nCol, double value);
	double GetElement(int nRow,int nCol)const;//��ȡָ��Ԫ�ص�ֵ
	void SetData(double value[]);//���þ����ֵ
	int GetNumCols() const;//��ȡ��������
	int GetNumRows() const;//��ȡ��������
	double *GetData() const;//��ȡ�����ֵ
	int GetRowVector(int nRow,double *pVector)const;//��ȡָ������������������pVector�У�����Ԫ�ظ���
	int GetColVector(int nCol,double *pVector)const;//��ȡָ������������������pVector�У�����Ԫ�ظ���
	
	///
	///
	///��ѧ�����
	CMatrix& operator=(const CMatrix &other);
	bool operator==(const CMatrix &other)const;
	bool operator!=(const CMatrix &other)const;
	CMatrix operator+(const CMatrix &other)const;
	CMatrix operator-(const CMatrix &other)const;
	CMatrix operator*(double value)const;
	CMatrix operator*(const CMatrix &other)const;
	CMatrix Transpose()const;//ת��
	CMatrix Invert();//��������
	CMatrix Eigenv();//����������ֵ�������������ؾ��󣬵�һ��Ϊ����ֵ��������Ϊ��Ӧ��������
	CMatrix Eigenv2();//����������ֵ���������ڶ��ַ��������ؾ��󣬵�һ��Ϊ����ֵ��������Ϊ��Ӧ��������
protected:
	int m_NumRows;//����
	int m_NumCols;//����
	double *m_pData;//���ݻ�����
private:
	bool InvertGaussJordan();
	bool JacobiEigenv(double EigenValue[], CMatrix &EigenVector,int nMaxIt=60,double eps=0.000001);
	bool JacobiEigenv2(double EigenValue[], CMatrix &EigenVector,int nMaxIt=60,double eps=0.000001);
	void Swape(void);//�Ծ��󰴵�һ���ɴ�С����

};

#endif // !defined(AFX_MATRIX_H__252F1FEF_F0A7_4E2A_9DFC_DE56FB93288C__INCLUDED_)
