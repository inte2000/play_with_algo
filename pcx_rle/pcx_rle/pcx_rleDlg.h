
// pcx_rleDlg.h : header file
//

#pragma once

#include "ShowWnd.h"
#include "RawBmpData.h"


// Cpcx_rleDlg dialog
class Cpcx_rleDlg : public CDialogEx
{
// Construction
public:
	Cpcx_rleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PCX_RLE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
    CShowWnd m_showWnd;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedBtnLoadPcx();
	DECLARE_MESSAGE_MAP()

protected:
    CRawBmpData m_bmpData;

public:
    afx_msg void OnBnClickedBtnFade();
    afx_msg void OnBnClickedBtnSavePcx();
};
