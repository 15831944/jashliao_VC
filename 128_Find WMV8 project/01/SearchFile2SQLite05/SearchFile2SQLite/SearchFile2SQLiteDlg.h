
// SearchFile2SQLiteDlg.h : ���Y��
//

#pragma once


// CSearchFile2SQLiteDlg ��ܤ��
class CSearchFile2SQLiteDlg : public CDialog
{
// �غc
public:
	CSearchFile2SQLiteDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	void GetandSetParameter();//step 3:Ū��XML
	CString m_StrDir;
	CString m_StrSearch;
	void BrowseDir(CString strDir);
	void SQLiteCreate();
	void SQLiteInsert(CString StrData);
	void SQLite2File();
	void RunSearch();
	static UINT ThreadRun(LPVOID lpram);
// ��ܤ�����
	enum { IDD = IDD_SEARCHFILE2SQLITE_DIALOG };

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
	afx_msg void OnBnClickedButsearch();
};
