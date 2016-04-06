#pragma once
#include "afxcmn.h"
#include "Game.h"

#define END_ROUND	0
#define END_GAME	1

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)
public:
	CResultDlg(CWnd* pParent = NULL);   // ����������� �����������
	CResultDlg(USHORT _type);
	virtual ~CResultDlg();


// ������ ����������� ����
	enum { IDD = IDD_RESULT_DIALOG };

protected:
	USHORT m_Type;

	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
