
// MainFrm.h : CMainFrame ���O������
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // �ȱq�ǦC�ƫإ�
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// �ݩ�
public:

// �@�~
public:
// �мg
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
// �{���X��@
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ͪ��T�������禡
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT On_click0(WPARAM wparam,LPARAM lparam);//HOOK�^���ƥ�
};


