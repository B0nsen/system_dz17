#include "MainWindow.h"
#include "LoginWindow.h"
#include "RegisterWindow.h"

CMainWindow* CMainWindow::ptr = NULL;

CMainWindow::CMainWindow(void)
{
	ptr = this;
}

CMainWindow::~CMainWindow(void)
{

}

void CMainWindow::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainWindow::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return TRUE;
}


void CMainWindow::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	
	
	if(id == IDC_LOGIN)
	{
		CLoginWindow CLW;
		if(CLoginWindow::hAddDialog) 
		{
			SetForegroundWindow(CLoginWindow::hAddDialog);
			return;
		}
		CLoginWindow::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, CLoginWindow::DlgProc);	
		ShowWindow(CLoginWindow::hAddDialog, SW_RESTORE); 
	}
	if (id == IDC_REGISTER)
	{
		CRegisterWindow CRW;
		if (CRegisterWindow::hAddDialog)
		{
			SetForegroundWindow(CRegisterWindow::hAddDialog);
			return;
		}
		CRegisterWindow::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CRegisterWindow::DlgProc);
		ShowWindow(CRegisterWindow::hAddDialog, SW_RESTORE);
	}
}

BOOL CALLBACK CMainWindow::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
