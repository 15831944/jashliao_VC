// Cute_Main_ControlDlg.h : header file
//
//{{AFX_INCLUDES()
#include "jpg.h"
//}}AFX_INCLUDES

#if !defined(AFX_CUTE_MAIN_CONTROLDLG_H__B0A24405_5F0B_48B0_A720_4072D0FEF259__INCLUDED_)
#define AFX_CUTE_MAIN_CONTROLDLG_H__B0A24405_5F0B_48B0_A720_4072D0FEF259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PDData_Max 10	//ProgramData�̤j�}�C��
/////////////////////////////////////////////////////////////////////////////
// CCute_Main_ControlDlg dialog
#include "WatchDog.h"
class CCute_Main_ControlDlg : public CDialog
{
// Construction
public:
	CCute_Main_ControlDlg(CWnd* pParent = NULL);	// standard constructor
	bool m_MainMonitor_On;//�j��On_OFF�X��1
	bool m_MainMonitor_Off;//�j��On_OFF�X��2
	void Read_Monitor();//step Ū��XML4
	void InitializeXMLMemory();//��l���ܼƨ��
	void MonitorRipData(CString Datainput,int day);//�ù��}�����r���Ѩ��
	void ChangeFormRipData(CString Datainput);//���ܪ������Ѩ��
	void Detect_Command();//����Ū���R�O��
	void Run_Command(int intCommandNumber);//����R�O
	void Start_Program();//�Ұʵ{�����
	void Stop_Program();//�����{�����
	void Stop_ALL();//�����{����ơA�s�q�T��
	void TimerFunction();//�D�{��
	bool Read_ChangeForm();//Ū�����ܪ����T�����
	void Create_ChangeForm();//�إߧ��ܪ����T�����
	void GetProgramInfo();//��Ū�Ұʵ{����T
	void ChangeStyle(CString StrStyleName);//���ܪ����{��
	void OnlyControlMovie(bool blnflag);//����Movie�{��
	void GetMonitorPicture();//�^���ù��e��
	void GetSpeciallyDay();//���o�S�O������
	void CreateCommunication();//�@�}�{���N��q�T�{��
	void CreateLogFile();//�}�Ҭ�����T�\��
	void GetCreateFileFlag();//Ū���O�_�إ߰O���ɮ׺X��
	void BoBoProgramZindex(int p[PDData_Max][2],long n);//ProgramZindex��w�Ƨ�
	void SetSystemVolume( const DWORD dwVolume );//�]�w�t�έ��q//��12.5��->�t�έ��q�]�w
	DWORD GetSystemVolume( void );//���o�t�έ��q//��12.5��->�t�έ��q�]�w
	void SetVolume();////��12.5��->Ū�����q�]�w�Ȩíק�t�έ�
	void SwitchMonitor();//��12.7��->�eCTRL+ALT+F9�Ϸs��STB���w�n��ʵ�����X
	void ChangMonitorSize();//��12.8��->�^���P�]�w�ù��ѪR��
	void BrowseUpdateProgram(CString strDir);//��13.3��->�j�M��s�{���ƶq�P����
	CString GetProgramVersion(CString StrDir);//��13.7��->�d�ߵ{������
	void Reset_Computer();//��13.8��
	CWatchDog m_WDT;//��14.1��->Watch Dog Timer
// Dialog Data
	//{{AFX_DATA(CCute_Main_ControlDlg)
	enum { IDD = IDD_CUTE_MAIN_CONTROL_DIALOG };
	CJPG	m_JPG;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCute_Main_ControlDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCute_Main_ControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton2();
	afx_msg LRESULT onShowTask(WPARAM wParam,LPARAM lParam); //Step �Y�p��t�Τu�@�C4
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUTE_MAIN_CONTROLDLG_H__B0A24405_5F0B_48B0_A720_4072D0FEF259__INCLUDED_)
