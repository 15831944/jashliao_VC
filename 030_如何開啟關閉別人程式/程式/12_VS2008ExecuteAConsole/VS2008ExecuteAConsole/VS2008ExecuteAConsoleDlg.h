// VS2008ExecuteAConsoleDlg.h : ���Y��
//

#pragma once


// CVS2008ExecuteAConsoleDlg ��ܤ��
class CVS2008ExecuteAConsoleDlg : public CDialog
{
// �غc
public:
	CVS2008ExecuteAConsoleDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_VS2008EXECUTEACONSOLE_DIALOG };

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
	afx_msg void OnBnClickedButton1();
};
