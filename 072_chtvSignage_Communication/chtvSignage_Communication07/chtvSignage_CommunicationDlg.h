// chtvSignage_CommunicationDlg.h : header file
//

#if !defined(AFX_CHTVSIGNAGE_COMMUNICATIONDLG_H__D9635E59_3484_4A50_BC38_1FCDB4B3FB3A__INCLUDED_)
#define AFX_CHTVSIGNAGE_COMMUNICATIONDLG_H__D9635E59_3484_4A50_BC38_1FCDB4B3FB3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChtvSignage_CommunicationDlg dialog

class CChtvSignage_CommunicationDlg : public CDialog
{
// Construction
public:
	CChtvSignage_CommunicationDlg(CWnd* pParent = NULL);	// standard constructor
	//////////////////////////////////////////////////////
	void InitialVariable();//Ū��XML�]�w�ɨê�l�Ƭ۹�M�����ܼ�
	void CreateNetDir();//�I�sBAT�إߺ����H��
	bool DownLoadXML();//�U������M��M�]�����
	void ReadXmlPlayList();//Ū��Xml��PlayList���
	bool SearchFile(CString strDir,CString strFile);//�j�M�ɮ�
	void ListingDownLoadFile();//���͹�ڭn�U���M��
	void DownLoadMovieFile();//�U���v����
	void UpLoadLogFile();//�W��LOG��
	//////////////////////////////////////////////////////
	TCHAR m_chrCurDrt[500];//�s��ثe�ؿ��r��
	CArray <CString,CString&> m_ArrPlayListData;//�s�񼽩�M�檺�Ҧ��ɦW
	CArray <CString,CString&> m_ArrDownLoadFileData;//�s��n�U���ɦW
	CString m_StrGet_Data;//�ثe�S�Ψ�->�h�[��@�����
	CString m_StrRunText_XML;//�s��U�]�X�ɮ׸��|
	CString m_StrCheckPlayList_XML;//�s��T�{���v������M����|
	CString m_StrPlayList_XML;//�s��v������M����|
	CString m_StrMovie_path;//�s��v���s����|
	CString m_StrCreateNet_Bat;//�s��BAT�ɸ��|
	CString m_StrDownLoad_Path;//�s��XML�U�����|
	CString m_StrUpLoad_Path;//�s��XML�W�Ǹ��|
	CString m_StrUpLoad_FilePath;//�s��W�ǧ����ɮ׸��|
	CString m_StrMAC;//�s���������MAC
// Dialog Data
	//{{AFX_DATA(CChtvSignage_CommunicationDlg)
	enum { IDD = IDD_CHTVSIGNAGE_COMMUNICATION_DIALOG };
	CString	m_Edit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChtvSignage_CommunicationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChtvSignage_CommunicationDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHTVSIGNAGE_COMMUNICATIONDLG_H__D9635E59_3484_4A50_BC38_1FCDB4B3FB3A__INCLUDED_)
