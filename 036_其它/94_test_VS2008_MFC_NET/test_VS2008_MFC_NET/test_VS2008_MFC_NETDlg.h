
// test_VS2008_MFC_NETDlg.h : ���Y��
//

#pragma once


// Ctest_VS2008_MFC_NETDlg ��ܤ��
class Ctest_VS2008_MFC_NETDlg : public CDialog
{
// �غc
public:
	Ctest_VS2008_MFC_NETDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
	enum { IDD = IDD_TEST_VS2008_MFC_NET_DIALOG };

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
