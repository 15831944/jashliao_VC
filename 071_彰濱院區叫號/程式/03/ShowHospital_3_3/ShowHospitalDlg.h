// ShowHospitalDlg.h : header file
//

#if !defined(AFX_SHOWHOSPITALDLG_H__B4BAB42B_683C_4A6B_BDCA_5EB51BAE0D0B__INCLUDED_)
#define AFX_SHOWHOSPITALDLG_H__B4BAB42B_683C_4A6B_BDCA_5EB51BAE0D0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShowHospitalDlg dialog
struct Reset_Time
{
	long lngHours;
	long lngMinute;
	long lngShowImageTime;//�q�Ϯɶ�
};
class CShowHospitalDlg : public CDialog
{
// Construction
public:
	CShowHospitalDlg(CWnd* pParent = NULL);	// standard constructor
////////////////////////////////////////////////////////////////////
//Jash.Liao add member function
	void InitialVariable(void);//Ū��XML�]�w�ɨê�l�Ƭ۹�M�����ܼ�
	void SetWindowPositionSize(void);//�I�s��������(��)
	void GetPlayData(void);//��������ALL
	void NetGetData(void);//����������
	void ShowData(void);//��ܼ�����
	void ChangeShowData(void);//������ܸ��
	void ClearMessageData(void);//�M����ܸ��
	CString NormalData(CString StrSource);//���W�����
	void BrowseDir(CString strDir,CString strtype);//Step 2:�C�X�ɮײM��
////////////////////////////////////////////////////////////////////
//Jash.Liao add member variable
	TCHAR m_chrCurDrt[500];//�s��ثe�ؿ��r��
	CString m_StrSettingFileName;//�s��]�w�ɹ�ڸ��|
	long m_lngTop,m_lngLeft,m_lngWidth,m_lngHeight;//�]�w�����j�p��m�ܼ�
	long m_lngImageTop,m_lngImageLeft,m_lngImageWidth,m_lngImageHeight;//�]�w�����j�p��m�ܼ�
	CRgn m_rgn;//����(��)������������
	long m_lngResetTimeCount;//Reset Time ���ƶq
	struct Reset_Time *m_RT;//Reset Time �����c��
	bool m_blnRest_Flag;
	long m_lngGet_Data;//�����Ʈɶ�
	long m_lngChange_Page;//���������ɶ�
	long m_lngData_Count;//XML�w�q����Ƥ��
	CString m_StrPlayDataFileName;
	CArray <CString,CString&> m_ArrPlayData;
	CString m_StrShowDataBuff[11];//�x�s�n��ܸ��
	long m_lngPageVariable;//���������ܼ�
	long m_lngArryDataCount;//��ڸ�Ƥ��
	bool m_bnlInitialPage;//���ƧP�_�X��
	long m_lngTimerCount;//�]��TIMER��10��A�]���n���@��Count�ӻ��U
	CString m_StrNetPath;
	bool m_blnArrayed_Data;//��ƴN���X��
	CString m_StrNormalData;//���W�����
	bool m_blnAttributes;//�z����
	long m_lngShowImageTime;//�q�Ϯɶ�
	long m_lngChangeImage;//�q�Ϥ��ϻP�Ϫ������ɶ�
	CArray <CString,CString&> m_Array;//Step 2:CArray
////////////////////////////////////////////////////////////////////
// Dialog Data
	//{{AFX_DATA(CShowHospitalDlg)
	enum { IDD = IDD_SHOWHOSPITAL_DIALOG };
	CString	m_ShowData00;
	CString	m_ShowData01;
	CString	m_ShowData02;
	CString	m_ShowData03;
	CString	m_ShowData04;
	CString	m_ShowData05;
	CString	m_ShowData06;
	CString	m_ShowData07;
	CString	m_ShowData08;
	CString	m_ShowData09;
	CString	m_ShowData10;
	CString	m_ShowData11;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowHospitalDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShowHospitalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWHOSPITALDLG_H__B4BAB42B_683C_4A6B_BDCA_5EB51BAE0D0B__INCLUDED_)
