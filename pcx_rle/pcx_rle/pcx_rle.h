
// pcx_rle.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cpcx_rleApp:
// See pcx_rle.cpp for the implementation of this class
//

class Cpcx_rleApp : public CWinApp
{
public:
	Cpcx_rleApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cpcx_rleApp theApp;