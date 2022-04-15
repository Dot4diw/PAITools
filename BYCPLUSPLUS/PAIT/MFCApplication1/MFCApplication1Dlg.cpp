
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include <Magick++.h> 
#include <iostream> 
#include <string>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib,"CORE_RL_Magick++_")

// using the namespace of std and magick
using namespace std;
using namespace Magick;

BOOL CONVERTER_FUNCTION(string INFILE, string OUTPUTFILE, int QUAL, string DPI);

//void PATH_CONVERT_SIGNLE2DOUBLE(string& s);

BOOL CONVERTER_FUNCTION(string INFILE, string OUTPUTFILE, int QUAL, string DPI)
{
	//InitializeMagick(".");
	Image MYIMAGE;
	MYIMAGE.quality(QUAL);
	MYIMAGE.resolutionUnits(Magick::PixelsPerInchResolution);
	MYIMAGE.density(DPI);
	MYIMAGE.read(INFILE);
	MYIMAGE.write(OUTPUTFILE);

	return TRUE;
}

//// Convert the path format
//void PATH_CONVERT_SIGNLE2DOUBLE(string& s)
//{
//	string::size_type pos = 0;
//	while ((pos = s.find('\\', pos)) != string::npos)
//	{
//		s.insert(pos, "\\");
//		pos = pos + 2;
//	}
//	//return pos;
//}


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


// CMFCApplication1Dlg dialog

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, QUALITY_COMBOX);
	DDX_Control(pDX, IDC_COMBO1, DPI_COMBOX);
	DDX_Control(pDX, IDC_COMBO3, FORMAT_COMBOX);
	DDX_Control(pDX, IDC_PROGRESS1, PROCESS_PROGRESS);
	DDX_Control(pDX, IDC_EDIT4, DEFAULT_OUTFILENAME);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCApplication1Dlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCApplication1Dlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMFCApplication1Dlg::OnCbnSelchangeCombo3)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCApplication1Dlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)

	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication1Dlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


CString DPI_STR;
CString QUALITY_STR;
CString FORMAT_STR;

// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDR_MAINFRAME & 0xFFF0) == IDR_MAINFRAME);
	ASSERT(IDR_MAINFRAME < 0xF000);


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
			pSysMenu->AppendMenu(MF_STRING, ID_VIEW_TOOLBAR, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Add the combobx data
	QUALITY_COMBOX.AddString(TEXT("50"));
	QUALITY_COMBOX.AddString(TEXT("60"));
	QUALITY_COMBOX.AddString(TEXT("70"));
	QUALITY_COMBOX.AddString(TEXT("80"));
	QUALITY_COMBOX.AddString(TEXT("90"));
	QUALITY_COMBOX.AddString(TEXT("100"));

	QUALITY_COMBOX.SetCurSel(5);
	QUALITY_COMBOX.GetLBText(5, QUALITY_STR);

	DPI_COMBOX.AddString(TEXT("72x72"));
	DPI_COMBOX.AddString(TEXT("96x96"));
	DPI_COMBOX.AddString(TEXT("300x300"));
	DPI_COMBOX.AddString(TEXT("600x600"));
	DPI_COMBOX.AddString(TEXT("800x800"));
	//DPI_COMBOX.AddString(TEXT("1200x1200"));
	//DPI_COMBOX.AddString(TEXT("2400x2400"));
	DPI_COMBOX.SetCurSel(2);
	DPI_COMBOX.GetLBText(2, DPI_STR);

	FORMAT_COMBOX.AddString(TEXT("jpg"));
	FORMAT_COMBOX.AddString(TEXT("png"));
	FORMAT_COMBOX.AddString(TEXT("tiff"));
	FORMAT_COMBOX.AddString(TEXT("svg"));
	FORMAT_COMBOX.AddString(TEXT("eps"));
	FORMAT_COMBOX.AddString(TEXT("pdf"));
	FORMAT_COMBOX.AddString(TEXT("ppm"));

	FORMAT_COMBOX.SetCurSel(0);
	FORMAT_COMBOX.GetLBText(0, FORMAT_STR);

	PROCESS_PROGRESS.SetRange(0, 100);
	
	// Setting the default value of Edit4 control.
	DEFAULT_OUTFILENAME.SetWindowTextW(TEXT("converted_outputile"));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == ID_VIEW_TOOLBAR)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString INPUT_FILEPATH;
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TCHAR szFilter[] = _T("PDF File(*.pdf)|*.pdf|All File(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("pdf"), NULL, 0, szFilter, this);
	
	if (IDOK == fileDlg.DoModal())
	{
		INPUT_FILEPATH = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, INPUT_FILEPATH);
		UpdateData(TRUE);
		//MessageBox(INPUT_FILEPATH);
	}
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

//CString DPI_STR;
void CMFCApplication1Dlg::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	
	int DPI_INDEX = DPI_COMBOX.GetCurSel();

	//DPI_COMBOX.GetWindowTextW(DPI_STR);
	DPI_COMBOX.GetLBText(DPI_INDEX, DPI_STR);

	UpdateData(FALSE);
	//MessageBox(DPI_STR);
}

//CString QUALITY_STR;
void CMFCApplication1Dlg::OnCbnSelchangeCombo2()
{
	// TODO: Add your control notification handler code here
	
	int QUALITY_INDEX = QUALITY_COMBOX.GetCurSel();
	
	QUALITY_COMBOX.GetLBText(QUALITY_INDEX, QUALITY_STR);
	//QUALITY_COMBOX.GetWindowTextW(QUALITY_STR);
	
	UpdateData(TRUE);
	//MessageBox(QUALITY_STR);

}

//CString FORMAT_STR;
void CMFCApplication1Dlg::OnCbnSelchangeCombo3()
{
	// TODO: Add your control notification handler code here
	
	int FORMAT_INDEX = FORMAT_COMBOX.GetCurSel();
	
	FORMAT_COMBOX.GetLBText(FORMAT_INDEX, FORMAT_STR);
	//FORMAT_COMBOX.GetWindowTextW(FORMAT_STR);
	UpdateData(TRUE);
	//MessageBox(FORMAT_STR);
}

void CMFCApplication1Dlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


CString OUTPUT_FILEPATH;
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	//// TODO: Add your control notification handler code here
	// Method 1 of Folder choose
	
	//TCHAR szFilter[] = _T("PDF File(*.pdf)|*.pdf|Image File(*.jpg)|Image File(*.png)|Image File(*.eps)||All File(*.*)|*.*||");
	TCHAR szFilter[] = { 0 };
	//CFileDialog fileDlg(FALSE, _T("jpg"), _T("converted_outfile"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CFolderPickerDialog FOLDERDLG(FALSE);
	if (IDOK == FOLDERDLG.DoModal())
	{
		//OUTPUT_FILEPATH = fileDlg.GetPathName();
		OUTPUT_FILEPATH = FOLDERDLG.GetFolderPath();
		SetDlgItemText(IDC_EDIT2, OUTPUT_FILEPATH);
		//UpdateData(FALSE);
		UpdateData(TRUE);
		//MessageBox(OUTPUT_FILEPATH);
	}

	// Method 2 of Folder choose 
	//TCHAR  szPath[MAX_PATH] = { 0 };
	//LPITEMIDLIST PITEM;
	//BROWSEINFO INFO;
	//::ZeroMemory(&INFO, sizeof(INFO));
	//INFO.hwndOwner = this->m_hWnd;
	//INFO.lpszTitle = _T("Please select a path: ");
	//INFO.pszDisplayName = szPath;
	//if (PITEM = ::SHBrowseForFolder(&INFO))
	//{
	//	::SHGetPathFromIDList(PITEM, szPath);
	//	OUTPUT_FILEPATH = szPath;
	//	//MessageBox(OUTPUT_FILEPATH);

	//	SetDlgItemText(IDC_EDIT2, OUTPUT_FILEPATH);
	//	UpdateData(FALSE);
	//	MessageBox(OUTPUT_FILEPATH);
	//}
}


CString INPUT_NAME;
void CMFCApplication1Dlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	GetDlgItemText(IDC_EDIT4, INPUT_NAME);
	UpdateData(TRUE);
	//UpdateData(TRUE);
	//MessageBox(INPUT_NAME);
}



void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplication1Dlg::OnBnClickedButton3()
{
	//// TODO: Add your control notification handler code here
	// 
	CT2CA pszConvertedAnsiString1(INPUT_FILEPATH);
	std::string INFILE(pszConvertedAnsiString1);
	//PATH_CONVERT_SIGNLE2DOUBLE(INFILE);
	
	CT2CA pszConvertedAnsiString2(OUTPUT_FILEPATH);
	std::string OUTPATH(pszConvertedAnsiString2);
	//PATH_CONVERT_SIGNLE2DOUBLE(OUTPATH);

	CT2CA pszConvertedAnsiString3(QUALITY_STR);
	std::string QUALSTR(pszConvertedAnsiString3);
	int QUAL = std::stoi(QUALSTR);

	CT2CA pszConvertedAnsiString4(FORMAT_STR);
	std::string FORMAT(pszConvertedAnsiString4);
	//PATH_CONVERT_SIGNLE2DOUBLE(FORMAT);

	CT2CA pszConvertedAnsiString5(DPI_STR);
	std::string DPI(pszConvertedAnsiString5);
	//PATH_CONVERT_SIGNLE2DOUBLE(DPI);

	CT2CA pszConvertedAnsiString6(INPUT_NAME);
	std::string OUTFIELNAME(pszConvertedAnsiString6);
	//PATH_CONVERT_SIGNLE2DOUBLE(OUTFIELNAME);
	string SPLIT("\\");
	string DOT(".");
	string OUTFIELPATH_AND_NAME = OUTPATH.append(SPLIT).append(OUTFIELNAME).append(DOT).append(FORMAT);
	


	BOOL CONVERT_FUNCTION_RETURN_CODE = TRUE;

	CONVERT_FUNCTION_RETURN_CODE = CONVERTER_FUNCTION(INFILE, OUTFIELPATH_AND_NAME, QUAL, DPI);

	//This progress bar is just a display effect and has no practical significance.

	int DPI_INDEX = DPI_COMBOX.GetCurSel();
	if (DPI_INDEX < 2)
	{
		for (int i = 0; i <= 100; i++) {
			Sleep(6);
			PROCESS_PROGRESS.SetPos(i);
		}
	}
	else {
		for (int i = 0; i <= 100; i++) {
			Sleep(8);
			PROCESS_PROGRESS.SetPos(i);
		}
	}


	//MessageBox(_T("Format conversion succeeded"), _T("Convert information"));

	if (CONVERT_FUNCTION_RETURN_CODE == TRUE)
	{
		MessageBox(_T("Format conversion succeeded!"), _T("Convert information"), MB_ICONINFORMATION);
	}
	else
	{
		
		MessageBox(_T("Failed! \nSome errors occurred!"), _T("Convert information"),MB_ICONWARNING);
	}
	// Initialize the progress bar
	PROCESS_PROGRESS.SetPos(0);

}


void CMFCApplication1Dlg::OnBnClickedButton4()
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


//Override the Class of PreTranslateMessage
BOOL CMFCApplication1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
