
// MFC_get_versionDlg.h : ���^�n
//

#pragma once


// CMFC_get_versionDlg ��Ԓ���K
class CMFC_get_versionDlg : public CDialogEx
{
// ����
public:
	CMFC_get_versionDlg(CWnd* pParent = NULL);	// �˜ʽ�����ʽ
	

// ��Ԓ���K�Y��
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_GET_VERSION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧Ԯ

public:
	CString getAppVersion();
// ��ʽ�a����
protected:
	HICON m_hIcon;

	// �a����ӍϢ������ʽ
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
