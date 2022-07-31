
// PAIToolsDlg.h : header file
//
#pragma once


// CPAIToolsDlg dialog
class CPAIToolsDlg : public CDialogEx
{
// Construction
public:
	CPAIToolsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAITOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboQuality();
	afx_msg void OnCbnSelchangeComboResolution();
	afx_msg void OnCbnSelchangeComboOutformat();
	afx_msg void OnEnChangeEditInputfile();
	afx_msg void OnEnChangeEditOutputPath();
	afx_msg void OnBnClickedButtonOutputpath();
	afx_msg void OnBnClickedButtonInputfile();
	afx_msg void OnEnChangeEditOutfilename();
	afx_msg void OnNMCustomdrawProgressBar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonConverter();
	afx_msg void OnBnClickedButtonExit();
	CEdit INPUT_FILE_BOX;
	CEdit OUTPUT_PATH_BOX;
	CComboBox QUALITY_SEL_COMBOBOX;
	CComboBox DPI_SEL_COMBOBOX;
	CComboBox OUTFORMAT_SEL_COMBOBOX;
	CEdit OUTPUT_FILENAME_BOX;
	CProgressCtrl IDC_PROGRESS_PROCESSING;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};