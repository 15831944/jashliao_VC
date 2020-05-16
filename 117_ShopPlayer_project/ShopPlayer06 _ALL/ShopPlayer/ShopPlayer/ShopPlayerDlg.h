// ShopPlayerDlg.h : ���Y��
//

#pragma once
#include "afxwin.h"
////////////////////////
//DirectShow_step 02
#include "CDXGraph.h"
#include "afxwin.h"
#include "afxcmn.h"


#define SLIDER_TIMER 100
///////////////////////

// CShopPlayerDlg ��ܤ��
class CShopPlayerDlg : public CDialog
{
// �غc
public:
	CShopPlayerDlg(CWnd* pParent = NULL);	// �зǫغc�禡
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
// ��ܤ�����
	enum { IDD = IDD_SHOPPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
public:
	///////////////////////////////
	//DirectShow_step 03
	CDXGraph *m_pFilterGraph;

	CString	m_sourceFile;
	CString m_mediaFileName;

	UINT_PTR m_playerTimer;
	void CreateGraph();
	void DestroyGraph();
	void MovieOpen();
	void MoviePlay();
	void MovieStop();
	CString  GetFileTitleFromFileName(CString FileName, BOOL Ext);
	long m_volume;
	double m_dblPosition;
	///////////////////////////////
	CString GetMapMemory(double *dblPosition);//MAP memory_step 04
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnGraphNotify(WPARAM inWParam, LPARAM inLParam);//DirectShow_step 06
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_videoWindow;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
