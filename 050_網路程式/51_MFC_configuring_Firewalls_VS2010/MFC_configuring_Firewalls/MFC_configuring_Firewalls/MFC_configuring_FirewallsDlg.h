
// MFC_configuring_FirewallsDlg.h : ���Y��
//

#pragma once


// CMFC_configuring_FirewallsDlg ��ܤ��
class CMFC_configuring_FirewallsDlg : public CDialogEx
{
// �غc
public:
	CMFC_configuring_FirewallsDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_MFC_CONFIGURING_FIREWALLS_DIALOG };

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
