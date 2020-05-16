// VMR9PlayerDlg.h : ���Y��
//

#pragma once
#include "cvideo.h"//VMR9_step 02
#include "afxwin.h"

// CVMR9PlayerDlg ��ܤ��
class CVMR9PlayerDlg : public CDialog
{
// �غc
public:
	CVMR9PlayerDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	////////////////////////////////////////////////////////////////////
	//Jash.Liao add member function
	void InitialVariable(void);
	////////////////////////////////////////////////////////////////////
	//Jash.Liao add member variable
	TCHAR m_chrCurDrt[500];//�s��ثe�ؿ��r��
	CString m_StrSettingFileName;
	long m_lngTop,m_lngLeft,m_lngWidth,m_lngHeight;
	CRgn m_rgn;
	////////////////////////////////////////////////////////////////////
	double m_dblPosition;
	CString m_sourceFile;
	CString m_mediaFileName;
	CString  GetFileTitleFromFileName(CString FileName, BOOL Ext);
	CString GetMapMemory(double *dblPosition);//MAP memory_step 04
	////////////////////////////////////////////////
	//VMR9_step 03
	cVideo mVideoClass;
	LRESULT OnGraphNotify ( WPARAM wParam, LPARAM lParam ) ;
	///////////////////////////////////////////////
// ��ܤ�����
	enum { IDD = IDD_VMR9PLAYER_DIALOG };

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
	CStatic m_videoWindow;
};
