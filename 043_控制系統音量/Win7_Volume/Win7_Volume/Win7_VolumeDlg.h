
// Win7_VolumeDlg.h : ���Y��
//

#pragma once


// CWin7_VolumeDlg ��ܤ��
class CWin7_VolumeDlg : public CDialog
{
// �غc
public:
	CWin7_VolumeDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	bool ChangeVolume(double nVolume,bool bScalar);
// ��ܤ�����
	enum { IDD = IDD_WIN7_VOLUME_DIALOG };

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
