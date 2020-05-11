
// USB_FramView.h : CUSB_FramView ���O������
//


#pragma once
#include <mshtml.h>
#include <comdef.h>
#include <atlbase.h>
#include <mshtmhst.h>

class CUSB_FramView : public CHtmlView
{
protected: // �ȱq�ǦC�ƫإ�
	CUSB_FramView();
	DECLARE_DYNCREATE(CUSB_FramView)

// �ݩ�
public:
	CUSB_FramDoc* GetDocument() const;

// �@�~
public:
	BOOL CheckInternet(LPCTSTR URL);//�P�_�����O�_���`
	void DisDriver();//�P�_�Ϻо��N��
// �мg
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // �غc��Ĥ@���I�s
	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO *pInfo);
// �{���X��@
public:
	virtual ~CUSB_FramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // USB_FramView.cpp ������������
inline CUSB_FramDoc* CUSB_FramView::GetDocument() const
   { return reinterpret_cast<CUSB_FramDoc*>(m_pDocument); }
#endif

