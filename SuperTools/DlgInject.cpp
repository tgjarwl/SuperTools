#include "stdafx.h"
#include "DlgInject.h"
#include "PeOperation.h"
#include "st_inject.h"


LRESULT CDlgInject::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    CenterWindow(GetParent());

    // pid控件支持 文件拖拽
    m_dropEditPID.InitCtrl(this->m_hWnd, IDC_EDIT_PID);
    m_dropEditPID.SubclassWindow(GetDlgItem(IDC_EDIT_PID).m_hWnd);

    // dll控件支持 文件拖拽
    m_dropEditDll.InitCtrl(this->m_hWnd, IDC_EDIT_Dll_PATH);
    m_dropEditDll.SubclassWindow(GetDlgItem(IDC_EDIT_Dll_PATH).m_hWnd);

    return TRUE;
}

LRESULT CDlgInject::OnCloseCmd(WORD, WORD wID, HWND, BOOL &)
{
    EndDialog(wID);
    return 0;
}


LRESULT CDlgInject::OnBnClickedBtnInject(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    CString szPidOrPath;
    GetDlgItemText(IDC_EDIT_PID, szPidOrPath);
    
    CString szFuncName;
    GetDlgItemText(IDC_EDIT_FUNC_NAME, szFuncName);

    CString szFilePath;
    GetDlgItemText(IDC_EDIT_Dll_PATH, szFilePath);

    CString szParam;
    GetDlgItemText(IDC_EDIT_PARAM, szParam);

    if (FsDisable::Call(PathFileExists, 1, szPidOrPath.GetString()))
    {
        DWORD dwDllBit = 0;
        DWORD dwStatus = FsDisable::Call(CPeOpr::GetPEFileBit, 2, szFilePath.GetString(), &dwDllBit);

        DWORD dwBit = 0;
        dwStatus = FsDisable::Call(CPeOpr::GetPEFileBit, 2, szPidOrPath.GetString(), &dwBit);

        if (dwDllBit != dwBit)
        {
            CString szBitError;
            szBitError.Format(L"[OnBnClickedBtnInject] exe bit: %d, dll bit : %d, 不相等，无法注入");
            MessageBox(szBitError);
            return 0;
        }

        switch (dwBit)
        {
            case PE_OPR_32:
            {
                PSI::StartX86Exe(szPidOrPath, szParam, szFilePath, szFuncName);
                break;
            }
            case PE_OPR_64:
            {
                PSI::StartX64Exe(szPidOrPath, szParam, szFilePath, szFuncName);
                break;
            }
            default:
                break;
        }

        CString szErrMsg = Utils::GetLastErrorMsg();
        if (szErrMsg.GetLength())
        {
            MessageBox(szErrMsg);
        }
    }
    else
    {
        long lPid = wcstol(szPidOrPath, NULL, 0);

        PSI::RemoteInjectExe(lPid, szParam, szFilePath, szFuncName);
    }

    return 0;
}
