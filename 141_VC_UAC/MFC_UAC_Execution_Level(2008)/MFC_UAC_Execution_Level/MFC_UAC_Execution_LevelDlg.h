
// MFC_UAC_Execution_LevelDlg.h : ���Y��
//

#pragma once


// CMFC_UAC_Execution_LevelDlg ��ܤ��
class CMFC_UAC_Execution_LevelDlg : public CDialog
{
// �غc
public:
	CMFC_UAC_Execution_LevelDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MFC_UAC_EXECUTION_LEVEL_DIALOG };

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
