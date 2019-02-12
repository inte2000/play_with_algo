
// pcx_rleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pcx_rle.h"
#include "pcx_rleDlg.h"
#include "afxdialogex.h"
#include "PcxFileLoader.h"
#include "PcxFileWriter.h"

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


// Cpcx_rleDlg dialog



Cpcx_rleDlg::Cpcx_rleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PCX_RLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpcx_rleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STC_SHOW, m_showWnd);
}

BEGIN_MESSAGE_MAP(Cpcx_rleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_LOAD_PCX, &Cpcx_rleDlg::OnBnClickedBtnLoadPcx)
    ON_BN_CLICKED(IDC_BTN_FADE, &Cpcx_rleDlg::OnBnClickedBtnFade)
    ON_BN_CLICKED(IDC_BTN_SAVE_PCX, &Cpcx_rleDlg::OnBnClickedBtnSavePcx)
END_MESSAGE_MAP()


// Cpcx_rleDlg message handlers

BOOL Cpcx_rleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cpcx_rleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cpcx_rleDlg::OnPaint()
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
HCURSOR Cpcx_rleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int AnsiCharFromCString(char *buf, UINT bufSize, const CString& cstr)
{
    int nCount = 0;
    if (buf)
    {
        buf[0] = 0;
#ifdef UNICODE
        nCount = ::WideCharToMultiByte(CP_ACP, 0, cstr, cstr.GetLength(), buf, bufSize, NULL, NULL);
        buf[nCount] = 0;
#else
        nCount = cstr.GetLength();
        strncpy(buf, cstr, bufSize);
        buf[bufSize - 1] = 0;
#endif
    }

    return nCount;
}


void Cpcx_rleDlg::OnBnClickedBtnLoadPcx()
{
    CFileDialog openDlg(TRUE, _T(""), NULL, 0, _T("PCX file(*.pcx)|*.pcx|All Files(*.*)|*.*||"), this);
    if (openDlg.DoModal() == IDOK)
    {
        char szFileName[256] = { 0 };
        AnsiCharFromCString(szFileName, 256, openDlg.GetPathName());

        CPcxFileLoader loader;
        if (loader.LoadPcxFile(szFileName, m_bmpData))
        {
            m_showWnd.SetBmpData(&m_bmpData);
            m_showWnd.UpdateGridWnd();
        }
    }
}


void Cpcx_rleDlg::OnBnClickedBtnFade()
{
    m_bmpData.Fade(0.85);
    m_showWnd.UpdateGridWnd();
}


void Cpcx_rleDlg::OnBnClickedBtnSavePcx()
{
    CFileDialog openDlg(FALSE, _T(""), NULL, 0, _T("PCX file(*.pcx)|*.pcx|All Files(*.*)|*.*||"), this);
    if (openDlg.DoModal() == IDOK)
    {
        char szFileName[256] = { 0 };
        AnsiCharFromCString(szFileName, 256, openDlg.GetPathName());

        CPcxFileWriter writer;
        if (writer.SavePcxFile(szFileName, m_bmpData))
        {
            AfxMessageBox(_T("Write successfully!"));
        }
        else
        {
            AfxMessageBox(_T("Write fail!"));
        }
    }
}
