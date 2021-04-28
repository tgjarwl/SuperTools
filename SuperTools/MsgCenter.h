#pragma once



namespace MsgCtl
{
    BOOL PresentMsg(HWND hDlg, int nIDDlgItem, LPCWSTR lpString);

    BOOL RegOutputInfo(HWND hDlg, int nIDDlgItem);
    BOOL OutputResult(LPCWSTR lpString);

};





