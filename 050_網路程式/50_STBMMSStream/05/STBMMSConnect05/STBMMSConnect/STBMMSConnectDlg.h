// STBMMSConnectDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"


// CSTBMMSConnectDlg ��ܤ��
class CSTBMMSConnectDlg : public CDialog
{
// �غc
public:
	CSTBMMSConnectDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	CArray <CString,CString&> m_ArrayARPIP;//CArray Step_02
	CArray <CString,CString&> m_ArrayCheckIP;//CArray Step_02
	CArray <CString,CString&> m_ArrayMessageIP;//CArray Step_02
	void GetARPTable();
	void InitVariable();
	void ShowARPIP();
	void GetIPList();
	void ShowCheckIP();
	void CompareIP();
	void ShowMSGIP();
	void SendMSG();
	bool ConnectSTB(CString StrIP);
// ��ܤ�����
	enum { IDD = IDD_STBMMSCONNECT_DIALOG };

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
	CListBox ARPListBox;
	CListBox STBListBox;
	afx_msg void OnBnClickedButtrun();
	CListBox MSGListBox;
	afx_msg void OnBnClickedButtshowmms();
	afx_msg void OnBnClickedButtshowstb();
	long m_V1;
	CString m_V2;
	CString m_V3;
};
