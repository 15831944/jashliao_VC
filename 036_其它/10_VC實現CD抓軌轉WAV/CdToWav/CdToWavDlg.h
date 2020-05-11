/*
	NAME:		CdToWAV
	FUNCTION:	CDץ��ת��WAVE����
	AUTHOR:		������(HuangLilong)	Email:landyu@163.com
	DATE:		2003-7
*/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <ntddcdrm.h>
#include <winioctl.h>
#include <Mmreg.h>
#include "DirDialog.h"

#define		NSECTORS		13
#define		UNDERSAMPLING	1
#define		CB_CDDASECTOR	2368
#define		CB_QSUBCHANNEL	16
#define  	CB_CDROMSECTOR	2048
#define		CB_AUDIO		(CB_CDDASECTOR-CB_QSUBCHANNEL)

// CCdToWavDlg �Ի���
class CCdToWavDlg : public CDialog
{
// ����
public:
	CCdToWavDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CDTOWAV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	CComboBox m_Combo_Cdrom;
	CProgressCtrl m_Progress;
	HANDLE		m_hDevice;
	CDROM_TOC CdromTOC;
	CString m_SavePath;
	CString m_csSavePath;
	CString m_csTrack;

	BOOL ReadSector(int sector, BYTE Buffer[], int NumSectors);
	DWORD GetStartSector(int track);
	DWORD GetEndSector(int track);
	BOOL IsReady();

	afx_msg void OnBnClickedGetpath();
	afx_msg void OnBnClickedChange();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCbnSelchangeComboCdrom();
	afx_msg void OnLbnSelchangeList();
};
