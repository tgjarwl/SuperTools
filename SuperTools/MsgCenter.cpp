#include "stdafx.h"
#include "MsgCenter.h"


BOOL MsgCtl::PresentMsg(HWND hDlg, int nIDDlgItem, LPCWSTR lpString)
{
    return SetDlgItemText(hDlg, nIDDlgItem, lpString);
}


HWND g_OutputDlg = NULL;
int  g_OutputIDC = NULL;
BOOL MsgCtl::RegOutputInfo(HWND hDlg, int nIDDlgItem)
{
    g_OutputDlg = hDlg;
    g_OutputIDC = nIDDlgItem;
    return TRUE;
}

BOOL MsgCtl::OutputResult(LPCWSTR lpString)
{
    if (g_OutputDlg && g_OutputIDC)
    {
        return PresentMsg(g_OutputDlg, g_OutputIDC, lpString);
    }

    return FALSE;
}
