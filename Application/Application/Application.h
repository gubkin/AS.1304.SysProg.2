
// Application.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include "Game.h"

// CApplicationApp:
// � ���������� ������� ������ ��. Application.cpp
//


class CApplicationApp : public CWinApp
{
	

public:
	Game m_Game;
	CApplicationApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CApplicationApp theApp;