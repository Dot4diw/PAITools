
// MFCApplication1Dlg.h : header file
//

#pragma once


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
private:
	CComboBox QUALITY_COMBOX;
	CComboBox DPI_COMBOX;
	CComboBox FORMAT_COMBOX;
public:
	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	//afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton3();
	CProgressCtrl PROCESS_PROGRESS;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit4();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit DEFAULT_OUTFILENAME;
};
