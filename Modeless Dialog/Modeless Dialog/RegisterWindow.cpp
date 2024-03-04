
#include "RegisterWindow.h"
#include <iostream>


CRegisterWindow* CRegisterWindow::ptr = NULL;
HWND CRegisterWindow::hAddDialog = NULL;
HHOOK hHook;
_TCHAR str[50];
_TCHAR str2[50];

CRegisterWindow::CRegisterWindow(void)
{
	ptr = this;
}

CRegisterWindow::~CRegisterWindow(void)
{
	UnhookWindowsHookEx(hHook);
}

void CRegisterWindow::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	CloseWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CRegisterWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
	return TRUE;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wp, LPARAM lp)
{
	
	if (nCode == HC_ACTION)
	{
		MessageBox(NULL, str, str2, MB_OK);
		std::wofstream login("Login.txt");
		std::wofstream password("Password.txt");
		if (!login.is_open() || !password.is_open())
		{
			return 0;
		}
		login << str;
		password << str2;
		login.close();
		password.close();
	}
	return CallNextHookEx(hHook, nCode, wp, lp);
}


void CRegisterWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	hEdit2 = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT2);
	
	if (id == IDC_REGISTER_CONFIRM)
	{
		GetWindowText(hEdit2, (LPWSTR)str, 50);
		GetWindowText(hEdit3, (LPWSTR)str2, 50);
		MessageBox(NULL, str, str2, MB_OK);
		hHook = SetWindowsHookEx(HC_ACTION, HookProc, NULL, GetCurrentThreadId());
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
	else if (id == IDC_REGISTER_CANCEL)
	{
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CRegisterWindow::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}



