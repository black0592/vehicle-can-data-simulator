
// CanSimulator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCanSimulatorApp: 
// �йش����ʵ�֣������ CanSimulator.cpp
//

class CCanSimulatorApp : public CWinApp
{
public:
	CCanSimulatorApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCanSimulatorApp theApp;