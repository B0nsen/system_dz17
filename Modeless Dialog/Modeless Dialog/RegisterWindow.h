#pragma once
#include "header.h"
#include <fstream>

class CRegisterWindow
{
public:
	CRegisterWindow(void);
public:
	~CRegisterWindow(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CRegisterWindow* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hEdit2, hEdit3;
	static HWND hAddDialog;
};
