
// UpdateNowNewsAVDlg.h : ���Y��
//

#pragma once


// CUpdateNowNewsAVDlg ��ܤ��
class CUpdateNowNewsAVDlg : public CDialog
{
// �غc
public:
	CUpdateNowNewsAVDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	CString NowNewsHttpPost(CString StrPostData);
// ��ܤ�����
	enum { IDD = IDD_UPDATENOWNEWSAV_DIALOG };

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
