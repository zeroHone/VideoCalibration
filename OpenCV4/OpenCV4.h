
// OpenCV4.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// COpenCV4App:
// See OpenCV4.cpp for the implementation of this class
//

class COpenCV4App : public CWinApp
{
public:
	COpenCV4App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern COpenCV4App theApp;
