#pragma once
namespace PSI
{
    BOOL StartX86Exe(CString szExePath, CString szParam, CString szDllPath, CString szFunc);
    BOOL StartX64Exe(CString szExePath, CString szParam, CString szDllPath, CString szFunc);

    BOOL RemoteInjectExe(DWORD dwRemoteProcessID, CString szParam, CString szDllPath, CString szFunc);
    BOOL RemoteInjectX86Exe(HANDLE hProcess, CString szParam, CString szDllPath, CString szFunc);
    BOOL RemoteInjectX64Exe(HANDLE hProcess, CString szParam, CString szDllPath, CString szFunc);
};

