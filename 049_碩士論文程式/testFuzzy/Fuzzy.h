// Fuzzy.h: interface for the CFuzzy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUZZY_H__56037543_7D7C_4D6C_8B48_3C6811DE349C__INCLUDED_)
#define AFX_FUZZY_H__56037543_7D7C_4D6C_8B48_3C6811DE349C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFuzzy  
{
public:
	CFuzzy();
///////////////////////////////////////////////////////////////////////////
	//Input
	float SwInputMem[5];//�ѹ�ڿ�J���ܦ��k�ݫת��s��O���� Z P N
	float InputMem;//��ڿ�J���ܦ��k�ݫת���ڿ�X
	int In_out;////(Z=0,P=1,N=2)
	float Input;//��J��
	void InputFun(float Input1);//���J���Ʀr�ҽk��,�L�]�OCFuzzy���O�i�J�I���@
////////////////////////////////////////////////////////////////////////////
	//out
	float in1,in2;//(Z=0,P=1,N=2)
	int out_rule;
	float fOut1;//��Xout���̤j�k�ݫ�
	float fOut2;//��Xout����ڭ�
	float FuzzyOutPut(float *out,float *x,float *y);//��w�ҽk�ƪ���J�A�z�L�ҽk�W�h�A�Ѽҽk�ơA�o���X,�L�]�OCFuzzy���O�i�J�I���@
/////////////////////////////////////////////////////////////////////////////
	virtual ~CFuzzy();
private:
/////////////////////////////////////////////////////////////////////////
	//Input
	void InputZ();
	void InputSP();
	void InputSN();
	void InputLP();
	void InputLN();
	void max3();
///////////////////////////////////////////////////////////////////////
	void min2();
	void out_rule_switch(int a,int b);//�̷ӿ�J�Ѽƪ����P�A��ܾA�X��Rule�C
	void comput_rule_out(int a,float b);//�̷өҲ��ͪ�Rule�A�A�t��J�A���͸ӿ�X�q�����A�Ҭ۹������k�ݫסC
	void comput_out();//�Q�έ��ߪk�Ѽҽk��
	float data[2][8];//�s���@�W�h�ҹB��X�ӨC�@��X�Ҭ۹������k�ݫסC
	float outdata[2][21];// 21�N��X���G�Q�@�������I
	float sum1,sum2;
//////////////////////////////////////////////////////////////////////
	
};

#endif // !defined(AFX_FUZZY_H__56037543_7D7C_4D6C_8B48_3C6811DE349C__INCLUDED_)
