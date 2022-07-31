
// PAITools.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPAIToolsApp:
// See PAITools.cpp for the implementation of this class
//

class CPAIToolsApp : public CWinApp
{
public:
	CPAIToolsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPAIToolsApp theApp;
