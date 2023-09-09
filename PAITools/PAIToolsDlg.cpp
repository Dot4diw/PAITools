
// PAIToolsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PAITools.h"
#include "PAIToolsDlg.h"
#include "converter.h"
#include "afxdialogex.h"
#include <Magick++.h> 
#include <iostream> 
#include <string>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPAIToolsDlg dialog



CPAIToolsDlg::CPAIToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAITOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPAIToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUTFILE, INPUT_FILE_BOX);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_PATH, OUTPUT_PATH_BOX);
	DDX_Control(pDX, IDC_COMBO_QUALITY, QUALITY_SEL_COMBOBOX);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, DPI_SEL_COMBOBOX);
	DDX_Control(pDX, IDC_COMBO_OUTFORMAT, OUTFORMAT_SEL_COMBOBOX);
	DDX_Control(pDX, IDC_EDIT_OUTFILENAME, OUTPUT_FILENAME_BOX);
	DDX_Control(pDX, IDC_PROGRESS_BAR, IDC_PROGRESS_PROCESSING);
}

BEGIN_MESSAGE_MAP(CPAIToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_QUALITY, &CPAIToolsDlg::OnCbnSelchangeComboQuality)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, &CPAIToolsDlg::OnCbnSelchangeComboResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTFORMAT, &CPAIToolsDlg::OnCbnSelchangeComboOutformat)
	ON_EN_CHANGE(IDC_EDIT_INPUTFILE, &CPAIToolsDlg::OnEnChangeEditInputfile)
	ON_EN_CHANGE(IDC_EDIT_OUTPUT_PATH, &CPAIToolsDlg::OnEnChangeEditOutputPath)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUTPATH, &CPAIToolsDlg::OnBnClickedButtonOutputpath)
	ON_BN_CLICKED(IDC_BUTTON_INPUTFILE, &CPAIToolsDlg::OnBnClickedButtonInputfile)
	ON_EN_CHANGE(IDC_EDIT_OUTFILENAME, &CPAIToolsDlg::OnEnChangeEditOutfilename)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS_BAR, &CPAIToolsDlg::OnNMCustomdrawProgressBar)
	ON_BN_CLICKED(IDC_BUTTON_CONVERTER, &CPAIToolsDlg::OnBnClickedButtonConverter)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CPAIToolsDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()

CString INPUT_FILEPATH;
CString OUTPUT_FOLDER;
CString QUALITY_VALUE;
CString DPI_VALUE;
CString QUTFORMAT_VALUE;
CString OUTPUT_NAME;

// CPAIToolsDlg message handlers

BOOL CPAIToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	QUALITY_SEL_COMBOBOX.AddString(_T("50"));
	QUALITY_SEL_COMBOBOX.AddString(_T("60"));
	QUALITY_SEL_COMBOBOX.AddString(_T("70"));
	QUALITY_SEL_COMBOBOX.AddString(_T("80"));
	QUALITY_SEL_COMBOBOX.AddString(_T("90"));
	QUALITY_SEL_COMBOBOX.AddString(_T("100"));
	QUALITY_SEL_COMBOBOX.SetCurSel(5);
	
	QUALITY_SEL_COMBOBOX.GetLBText(5, QUALITY_VALUE);

	DPI_SEL_COMBOBOX.AddString(_T("72x72"));
	DPI_SEL_COMBOBOX.AddString(_T("96x96"));
	DPI_SEL_COMBOBOX.AddString(_T("150x150"));
	DPI_SEL_COMBOBOX.AddString(_T("300x300"));
	DPI_SEL_COMBOBOX.AddString(_T("400x400"));
	DPI_SEL_COMBOBOX.AddString(_T("500x500"));
	DPI_SEL_COMBOBOX.AddString(_T("600x600"));
	//DPI_SEL_COMBOBOX.AddString(_T("800x800"));
	//DPI_SEL_COMBOBOX.AddString(_T("1000x1000"));
	DPI_SEL_COMBOBOX.SetCurSel(3);
	
	DPI_SEL_COMBOBOX.GetLBText(3, DPI_VALUE);

	OUTFORMAT_SEL_COMBOBOX.AddString(_T("jpeg"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("png"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("eps"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("tiff"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("gif"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("svg"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("bmp"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("ico"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("pdf"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("ppm"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("ps"));
	OUTFORMAT_SEL_COMBOBOX.AddString(_T("ttf"));
	OUTFORMAT_SEL_COMBOBOX.SetCurSel(0);
	
	OUTFORMAT_SEL_COMBOBOX.GetLBText(0, QUTFORMAT_VALUE);

	//Initialization the output file name
	OUTPUT_FILENAME_BOX.SetWindowTextW(TEXT("inputfile_converted"));

	// Initialization the progressing bar
	IDC_PROGRESS_PROCESSING.SetRange(0, 100);
	//IDC_PROGRESS_PROCESSING.SetPos(20);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPAIToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPAIToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPAIToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPAIToolsDlg::OnEnChangeEditInputfile()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CPAIToolsDlg::OnEnChangeEditOutputPath()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



void CPAIToolsDlg::OnBnClickedButtonInputfile()
{
	// TODO: Add your control notification handler code here
	//setlocale(LC_ALL, "Chinese-simplified");
	TCHAR szFilter[] = _T("PDF File(*.pdf)|*.pdf|All File(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("pdf"), NULL, 0, szFilter, this);
	if (IDOK == fileDlg.DoModal())
	{
		INPUT_FILEPATH = fileDlg.GetPathName();
		CString INPUT_FOLDER;
		INPUT_FOLDER = fileDlg.GetFolderPath();
		CString INPUT_FILE_TITLE = fileDlg.GetFileTitle();
		//MessageBox(INPUT_FILE_TITLE);
		OUTPUT_FOLDER = INPUT_FOLDER;
		SetDlgItemText(IDC_EDIT_INPUTFILE, INPUT_FILEPATH);
		SetDlgItemText(IDC_EDIT_OUTPUT_PATH, OUTPUT_FOLDER);
		//SetDlgItemText(IDC_EDIT_OUTPUT_PATH, OUTPUT_FOLDER);
		OUTPUT_FILENAME_BOX.SetWindowTextW(INPUT_FILE_TITLE + TEXT("_converted"));

		UpdateData(TRUE);
		//MessageBox(INPUT_FILEPATH);
	}
}


void CPAIToolsDlg::OnBnClickedButtonOutputpath()
{
	// TODO: Add your control notification handler code here
	//setlocale(LC_ALL, "Chinese-simplified");
	TCHAR szFilter[] = { 0 };
	//CFileDialog fileDlg(FALSE, _T("jpg"), _T("converted_outfile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CFolderPickerDialog FOLDERDLG(FALSE);
	if (IDOK == FOLDERDLG.DoModal())
	{
		OUTPUT_FOLDER = FOLDERDLG.GetFolderPath();
		SetDlgItemText(IDC_EDIT_OUTPUT_PATH, OUTPUT_FOLDER);
		//UpdateData(FALSE);
		UpdateData(TRUE);
		//MessageBox(OUTPUT_FILEPATH);
	}
}

void CPAIToolsDlg::OnCbnSelchangeComboQuality()
{
	// TODO: Add your control notification handler code here
	int QUALITY_INDEX = QUALITY_SEL_COMBOBOX.GetCurSel();

	QUALITY_SEL_COMBOBOX.GetLBText(QUALITY_INDEX, QUALITY_VALUE);
	//QUALITY_COMBOX.GetWindowTextW(QUALITY_STR);

	UpdateData(TRUE);
}

void CPAIToolsDlg::OnCbnSelchangeComboResolution()
{
	// TODO: Add your control notification handler code here
	int DPI_INDEX = DPI_SEL_COMBOBOX.GetCurSel();

	//DPI_COMBOX.GetWindowTextW(DPI_STR);
	DPI_SEL_COMBOBOX.GetLBText(DPI_INDEX, DPI_VALUE);

	UpdateData(TRUE);
}

void CPAIToolsDlg::OnCbnSelchangeComboOutformat()
{
	// TODO: Add your control notification handler code here
	int FORMAT_INDEX = OUTFORMAT_SEL_COMBOBOX.GetCurSel();
	OUTFORMAT_SEL_COMBOBOX.GetLBText(FORMAT_INDEX, QUTFORMAT_VALUE);
	UpdateData(TRUE);

}


void CPAIToolsDlg::OnEnChangeEditOutfilename()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	GetDlgItemText(IDC_EDIT_OUTFILENAME, OUTPUT_NAME);
	UpdateData(TRUE);
	//MessageBox(OUTPUT_NAME);
}


void CPAIToolsDlg::OnNMCustomdrawProgressBar(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	//IDC_PROGRESS_PROCESSING.SetPos(20);
	*pResult = 0;

}

void CPAIToolsDlg::OnBnClickedButtonConverter()
{
	// TODO: Add your control notification handler code here
	//CT2CA pszConvertedAnsiString1(INPUT_FILEPATH);
	//std::string INFILE(pszConvertedAnsiString1);
	std::string INFILE;
	INFILE = CW2A(INPUT_FILEPATH.GetString());
	// 
	//PATH_CONVERT_SIGNLE2DOUBLE(INFILE);
	

	//CT2CA pszConvertedAnsiString2(OUTPUT_FOLDER);
	//std::string OUTPATH(pszConvertedAnsiString2);
	std::string OUTPATH;
	OUTPATH = CW2A(OUTPUT_FOLDER.GetString());
	//std::string OUTPATH = CStringA(OUTPUT_FOLDER);
	//PATH_CONVERT_SIGNLE2DOUBLE(OUTPATH);


	//CT2CA pszConvertedAnsiString3(QUALITY_VALUE);
	//std::string QUALSTR(pszConvertedAnsiString3);
	std::string QUALSTR;
	QUALSTR = CW2A(QUALITY_VALUE.GetString());
	//std::string QUALSTR = CStringA(QUALITY_VALUE);

	int QUAL = atoi(QUALSTR.c_str());
	//int QUAL = std::stoll(QUALSTR);
	//MessageBox(_T("TEST"));

	//CT2CA pszConvertedAnsiString4(QUTFORMAT_VALUE);
	//std::string OUTFORMAT(pszConvertedAnsiString4);
	std::string OUTFORMAT;
	OUTFORMAT = CW2A(QUTFORMAT_VALUE.GetString());
	//std::string OUTFORMAT = CStringA(QUTFORMAT_VALUE);
	//PATH_CONVERT_SIGNLE2DOUBLE(FORMAT);

	//CT2CA pszConvertedAnsiString5(DPI_VALUE);
	//std::string DPI(pszConvertedAnsiString5);
	std::string DPI;
	DPI = CW2A(DPI_VALUE.GetString());
	//std::string DPI = CStringA(DPI_VALUE);
	//PATH_CONVERT_SIGNLE2DOUBLE(DPI);

	//CT2CA pszConvertedAnsiString6(OUTPUT_NAME);
	//std::string OUTFIELNAME(pszConvertedAnsiString6);
	std::string OUTFIELNAME;
	OUTFIELNAME = CW2A(OUTPUT_NAME.GetString());
	//std::string OUTFIELNAME = CStringA(OUTPUT_NAME);
	//PATH_CONVERT_SIGNLE2DOUBLE(OUTFIELNAME);
	std::string SPLIT("\\");
	std::string DOT(".");
	//std::string CONVERTED = "_converted";
	std::string OUTFIELPATH_AND_NAME = OUTPATH.append(SPLIT).append(OUTFIELNAME).append(DOT).append(OUTFORMAT);
	//OUTFIELPATH_AND_NAME.replace(OUTFIELPATH_AND_NAME.begin(), OUTFIELPATH_AND_NAME.end(), '\\', '/');
	//std::cout << "OUT PATH: " << OUTFIELPATH_AND_NAME << std::endl;
	
	// Prevent the progress proceedings to be fake.
	//MSG msg;
	//if (PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE))
	//{
	//	::SendMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
	//	//TranslateMessage(&msg);
	//	//DispatchMessage(&msg);
	//}

	// Run the Converter.
	BOOL CONVERT_FUNCTION_RETURN_CODE = TRUE;
	//MessageBox(_T("Begin Convert..."), _T("Convert information"), MB_ACTIVE);
	CONVERT_FUNCTION_RETURN_CODE = CONVERTER_FUNCTION(INFILE, OUTFIELPATH_AND_NAME, QUAL, DPI);


	// Setting the fake progress bar.
	// Only as an interface display effect.
	int CUR_DPI_INDEX = DPI_SEL_COMBOBOX.GetCurSel();
	for (int i = 0; i <= 100; i = i++)
	{
		if ( 0 >= CUR_DPI_INDEX < 2 )
		{
			IDC_PROGRESS_PROCESSING.SetPos(i);
		}
		else if (2 >= CUR_DPI_INDEX < 4)
		{
			
			IDC_PROGRESS_PROCESSING.SetPos(i);
			Sleep(2);
		}
		else if (4 >= CUR_DPI_INDEX < 6)
		{
			
			IDC_PROGRESS_PROCESSING.SetPos(i);
			Sleep(4);
		}
		else 
		{
			
			IDC_PROGRESS_PROCESSING.SetPos(i);
			Sleep(8);
		}
	}

	if (CONVERT_FUNCTION_RETURN_CODE == TRUE)
	{
		MessageBox(_T("Format conversion succeeded!"), _T("Convert information"), MB_ICONINFORMATION);
	}
	else
	{

		MessageBox(_T("Failed! \nSome errors occurred!"), _T("Convert information"), MB_ICONWARNING);
	}
	IDC_PROGRESS_PROCESSING.SetPos(0);
}


void CPAIToolsDlg::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	UINT i;
	i = MessageBox(_T("Are you sure you want to exit the program?"), _T("Tips"), MB_YESNO | MB_ICONQUESTION);
	if (i == IDNO)
	{
		return;
	}
	CDialogEx::OnOK();
}

// Overide the PreTranslateMessage.
BOOL CPAIToolsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		// If current focus the Ex, enter the Enter button.
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT_OUTFILENAME)
		{
			// Enter the button
			OnBnClickedButtonConverter();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
