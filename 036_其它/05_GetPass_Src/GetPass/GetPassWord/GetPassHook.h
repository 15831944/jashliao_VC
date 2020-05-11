// GetPassHook.h: interface for the CGetPassHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETPASSHOOK_H__6BD8BF04_D7D6_413F_9D92_0BCC6958389B__INCLUDED_)
#define AFX_GETPASSHOOK_H__6BD8BF04_D7D6_413F_9D92_0BCC6958389B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//========================================
//���ܣ�ͨ����װ��꣬����HOOK���ﵽʵ�ֽٻ����������Ĺ��ܡ�
//�����ƶ���굽*�Ŵ���ʾ*����ʵ���룬
//��Ҫ������SetWindowsHookEx,EnumChildWindows
//Ӧ��ƽ̨��98/2000/xp/2003����ͨ��
//����������VC++6.0
//���ߣ����º��� ���������˹����ң�
//QQ:1368077
//Email:blode@peoplemail.com.cn
//��ҿ��������޸ľͿ�����QQ���Ź���
//ϣ������VC�����߽���
//=======================================

class AFX_EXT_CLASS CGetPassHook : public CObject  
{
public:
	BOOL StopHook();
	BOOL StartHook(HWND hwnd);
	
	CGetPassHook();
	virtual ~CGetPassHook();

};

#endif // !defined(AFX_GETPASSHOOK_H__6BD8BF04_D7D6_413F_9D92_0BCC6958389B__INCLUDED_)
