
// DaAiNewsDownloadDlg.h : ���Y��
//

#pragma once


// CDaAiNewsDownloadDlg ��ܤ��
class CDaAiNewsDownloadDlg : public CDialog
{
// �غc
public:
	CDaAiNewsDownloadDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	CString NowNewsHttpPost(CString StrPostData);
	CString GetFileName(CString Strdata);
	void ReadFileDownLoadXML();
	void DownLoadWMVFile();
	bool GetWebFile(CString theUrl, CString Filename);//Step 2:Http
	CArray <CString,CString&> m_Array0;//CArray Step_02
	CArray <CString,CString&> m_Array1;//CArray Step_02
	CArray <CString,CString&> m_Array2;//CArray Step_02
	int m_intHttpNumber;
// ��ܤ�����
	enum { IDD = IDD_DAAINEWSDOWNLOAD_DIALOG };

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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
