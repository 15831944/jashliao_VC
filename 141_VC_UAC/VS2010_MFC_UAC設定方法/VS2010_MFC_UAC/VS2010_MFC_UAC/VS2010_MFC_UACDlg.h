
// VS2010_MFC_UACDlg.h : ���Y��
//

#pragma once


// CVS2010_MFC_UACDlg ��ܤ��
class CVS2010_MFC_UACDlg : public CDialogEx
{
// �غc
public:
	CVS2010_MFC_UACDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_VS2010_MFC_UAC_DIALOG };

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
};
