// MapMemoryUpDlg.h : ���Y��
//

#pragma once


// CMapMemoryUpDlg ��ܤ��
class CMapMemoryUpDlg : public CDialog
{
// �غc
public:
	CMapMemoryUpDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	void CallPlayer();//CreateProcess step02

// ��ܤ�����
	enum { IDD = IDD_MAPMEMORYUP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_V1;
	afx_msg void OnDestroy();
};
