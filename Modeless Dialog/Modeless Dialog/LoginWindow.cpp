
#include "LoginWindow.h"
#include "MainWindow.h"
#include "header.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

CLoginWindow* CLoginWindow::ptr = NULL;
HWND CLoginWindow::hAddDialog = NULL;
_TCHAR login_char[50], password_char[50];
HHOOK hHook1;
			

CLoginWindow::CLoginWindow(void)
{
	ptr = this;
}

CLoginWindow::~CLoginWindow(void)
{

}

void CLoginWindow::Cls_OnClose(HWND hwnd)
{
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CLoginWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
	return TRUE;
}

LRESULT CALLBACK HookProc1(int nCode, WPARAM wp, LPARAM lp)
{
	wchar_t wstr[50];
	wchar_t wstr2[50];
	std::ifstream login("Login.txt");
	std::ifstream password("Password.txt");
	bool isLogined = false;
	char file_login[50], file_password[50];
	MessageBox(NULL, L"Login", L"Login failed", MB_OK);
	if (nCode == HC_ACTION)
	{
		while (!login.eof())
		{
			login >> file_login;
			password >> file_password;


			MultiByteToWideChar(CP_UTF8, 0, file_login, -1, wstr, 50);
			MultiByteToWideChar(CP_UTF8, 0, file_password, -1, wstr2, 50);
			if (!_tcscmp(login_char, wstr) && !_tcscmp(password_char, wstr2))
			{
				isLogined = true;
				break;
			}
		}
		if (!isLogined)
		{
			MessageBox(NULL, L"Login", L"Login failed", MB_OK);
		}
		else
		{
			MessageBox(NULL, L"Login", L"Login succsesful", MB_OK);
		}
		login.close();
		password.close();
	}
	return CallNextHookEx(hHook1, nCode, wp, lp);
}



void CLoginWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	hEdit4 = GetDlgItem(hwnd, IDC_LOGIN_LOGIN);
	hEdit5 = GetDlgItem(hwnd, IDC_LOGIN_PASSWORD);
	if (id == IDC_LOGIN_CONFIRM)
	{
		GetWindowText(hEdit4, (LPWSTR)login_char, 50);
		GetWindowText(hEdit5, (LPWSTR)password_char, 50);
		hHook1 = SetWindowsHookEx(HC_ACTION, HookProc1, NULL, GetCurrentThreadId());
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
	else if (id == IDC_LOGIN_CANCEL)
	{
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CLoginWindow::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}