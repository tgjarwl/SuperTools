#include "stdafx.h"
#include "AboutDlg.h"

LRESULT CAboutDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    CenterWindow(GetParent());

    MsgCtl::OutputResult(L"Ablout Opend");
    return TRUE;
}

LRESULT CAboutDlg::OnCloseCmd(WORD, WORD wID, HWND, BOOL &)
{
    MsgCtl::OutputResult(L"Ablout Closed");
    EndDialog(wID);
    return 0;
}
