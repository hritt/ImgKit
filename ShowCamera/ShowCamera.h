
// ShowCamera.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowCameraApp:
// �йش����ʵ�֣������ ShowCamera.cpp
//

class CShowCameraApp : public CWinApp
{
public:
	CShowCameraApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowCameraApp theApp;