#include "stdafx.h"
#include "st_inject.h"
#include "PeOperation.h"
#include "wow64ext/wow64ext.h"

struct InjectBuf
{
    char szFuncName[64];
    char szDllPath[MAX_PATH];
    char szShellcode[1024];
};

/*
90                      nop
68 11 11 11 11          push 0x11111111             ret addr
60                      pushad
9C                      pushfd
68 11 11 11 11          push 0x11111111             func_name
68 11 11 11 11          push 0x11111111             dll name
B8 11 11 11 11          mov eax, 0x11111111         LoadLibraryW
FF D0                   call eax
50                      push eax
B8 11 11 11 11          mov eax, 0x11111111         GetProcAddr
FF D0                   call eax
FF D0                   call eax
9D                      popfd
61                      popad
C3                      ret
*/
UCHAR puShellCode[] = { 
    0x90,
    0x68, 0x11, 0x11, 0x11, 0x11,
    0x60,
    0x9C,
    0x68, 0x11, 0x11, 0x11, 0x11,
    0x68, 0x11, 0x11, 0x11, 0x11,
    0xB8, 0x11, 0x11, 0x11, 0x11,
    0xFF, 0xD0,
    0x50,
    0xB8, 0x11, 0x11, 0x11, 0x11,
    0xFF, 0xD0,
    0xFF, 0xD0,
    0x9D,
    0x61,
    0xC3 
};

// 远程线程注入 shellcode
UCHAR puShellCode_RT[] = {
    0x90,
    0x90, 0x90, 0x90, 0x90, 0x90,
    0x60,
    0x9C,
    0x68, 0x11, 0x11, 0x11, 0x11,
    0x68, 0x11, 0x11, 0x11, 0x11,
    0xB8, 0x11, 0x11, 0x11, 0x11,
    0xFF, 0xD0,
    0x50,
    0xB8, 0x11, 0x11, 0x11, 0x11,
    0xFF, 0xD0,
    0xFF, 0xD0,
    0x9D,
    0x61,
    0xC3
};

typedef struct _STRING {
    USHORT Length;
    USHORT MaximumLength;
    DWORD64 Buffer;
} STRING;

struct InjectBufX64
{
    STRING asFuncName;
    CHAR szFuncName[64];
    STRING usDllPath;
    WCHAR szDllPath[MAX_PATH];
    char szShellcode[1024];
};

UCHAR puShellCode_x64[] = {
    0x9C, 0x50, 0x53, 0x51, 0x52, 0x55, 0x56, 0x57, 0x54, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57, 
    0x49, 0xBF, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x54, 0x54, 0x48, 0x8B, 0xF4, 0x4C, 0x8B, 0xCE, 0x56, 0x4D, 0x8D, 0x47, 0x50, 0x41, 0x50, 0x48, 0x33, 0xD2, 0x52, 0x48, 0x33, 0xC9, 0x51, 0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x20,
    0x90, 0x90, 0x90, 0x48, 0x8B, 0x0E, 0x48, 0xC7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0xFC, 0x4C, 0x8B, 0xCF, 0x57, 0x4D, 0x33, 0xC0, 0x41, 0x50, 0x49, 0x8B, 0xD7, 0x52, 0x51, 0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x20, 
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x48, 0x83, 0x3F, 0x00, 0x74, 0x1B, 
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x48, 0x8B, 0x07, 0xFF, 0xD0,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x59, 0x90, 0x5C, 0x41, 0x5F, 0x41, 0x5E, 0x41, 0x5D, 0x41, 0x5C, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5C, 0x5F, 0x5E, 0x5D, 0x5A, 0x59, 0x5B, 0x58, 0x9D, 0x68, 0x11, 0x11, 0x11, 0x11, 0xC7, 0x44, 0x24, 0x04, 0x11, 0x11, 0x11, 0x11, 0xC3
};

// 远程线程注入
UCHAR puShellCode_RT_x64[] = {
    0x9C, 0x50, 0x53, 0x51, 0x52, 0x55, 0x56, 0x57, 0x54, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x41, 0x54, 0x41, 0x55, 0x41, 0x56, 0x41, 0x57,
    0x49, 0xBF, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x54, 0x54, 0x48, 0x8B, 0xF4, 0x4C, 0x8B, 0xCE, 0x56, 0x4D, 0x8D, 0x47, 0x50, 0x41, 0x50, 0x48, 0x33, 0xD2, 0x52, 0x48, 0x33, 0xC9, 0x51, 0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x20,
    0x90, 0x90, 0x90, 0x48, 0x8B, 0x0E, 0x48, 0xC7, 0x06, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B, 0xFC, 0x4C, 0x8B, 0xCF, 0x57, 0x4D, 0x33, 0xC0, 0x41, 0x50, 0x49, 0x8B, 0xD7, 0x52, 0x51, 0x48, 0xB8, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x83, 0xC4, 0x20,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x48, 0x83, 0x3F, 0x00, 0x74, 0x1B,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x48, 0x8B, 0x07, 0xFF, 0xD0,
    0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x59, 0x90, 0x5C, 0x41, 0x5F, 0x41, 0x5E, 0x41, 0x5D, 0x41, 0x5C, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5C, 0x5F, 0x5E, 0x5D, 0x5A, 0x59, 0x5B, 0x58, 0x9D, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0xC3
};

BOOL PSI::StartX86Exe(CString szExePath, CString szParam, CString szDllPath, CString szFunc)
{
    // 提权
    CPeOpr::EnableDebugPriv();

    CString szErrorMsg;

    BOOL bStatus = FALSE;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(STARTUPINFO));
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    if (CreateProcess(szExePath, (LPWSTR)szParam.GetString(), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi) == FALSE)
    {
        szErrorMsg.Format(_T("Create Process Failed : %d"), GetLastError());
        Utils::SetLastErrorMsg(szErrorMsg);
        return bStatus;
    }

    do
    {
        CONTEXT ctx;
        ctx.ContextFlags = CONTEXT_ALL;
        if (!GetThreadContext(pi.hThread, &ctx))
        {
            szErrorMsg.Format(_T("GetThreadContext Error : %d"), GetLastError());
            break;
        }

        LPVOID LpAddr = VirtualAllocEx(pi.hProcess, NULL, sizeof(InjectBuf), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (LpAddr == NULL)
        {
            szErrorMsg.Format(_T("VirtualAlloc Error : %d"), GetLastError());
            break;
        }

        InjectBuf inBuf;

        *(DWORD*)&puShellCode[2] = ctx.Eax;
        *(DWORD*)&puShellCode[9] = (DWORD)LpAddr;
        *(DWORD*)&puShellCode[14] = (DWORD)LpAddr + sizeof(inBuf.szFuncName);
        *(DWORD*)&puShellCode[19] = (DWORD)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryA");
        *(DWORD*)&puShellCode[27] = (DWORD)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "GetProcAddress");

        ctx.Eax = (ULONG_PTR)LpAddr + MAX_PATH + sizeof(inBuf.szFuncName);

        strcpy_s(inBuf.szDllPath, MAX_PATH, CW2A(szDllPath));
        strcpy_s(inBuf.szFuncName, 64, CW2A(szFunc));
        memcpy(inBuf.szShellcode, puShellCode, sizeof(puShellCode));

        if (!WriteProcessMemory(pi.hProcess, LpAddr, &inBuf, sizeof(inBuf), NULL))
        {
            szErrorMsg.Format(_T("WriteProcessMemory error : %d"), GetLastError());
            break;
        }

        CString szParam;
        szParam.Format(L"pRemoteAddr : %p", LpAddr);
        MessageBox(NULL, szParam, L"click to continue run ", MB_OK);

        if (!SetThreadContext(pi.hThread, &ctx))
        {
            szErrorMsg.Format(_T("SetThreadContext error : %d"), GetLastError());
            break;
        }

        bStatus = TRUE;
        szErrorMsg.Format(_T("hijack process eip success "));
    } while (0);

    if (szErrorMsg.GetLength())
    {
        Utils::SetLastErrorMsg(szErrorMsg);
    }

    ResumeThread(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return bStatus;
}

BOOL PSI::StartX64Exe(CString szExePath, CString szParam, CString szDllPath, CString szFunc)
{
    // 提权
    CPeOpr::EnableDebugPriv();

    CString szErrorMsg;

    BOOL bStatus = FALSE;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    memset(&si, 0, sizeof(STARTUPINFO));
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    if (FsDisable::Call(CreateProcess, 10,szExePath.GetString(), (LPWSTR)szParam.GetString(), NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi) == FALSE)
    {
        szErrorMsg.Format(_T("Create Process Failed : %d"), GetLastError());
        Utils::SetLastErrorMsg(szErrorMsg);
        return bStatus;
    }

    do
    {
        _CONTEXT64 ctx;
        ctx.ContextFlags = CONTEXT64_ALL;
        if (!GetThreadContext64(pi.hThread, &ctx))
        {
            szErrorMsg.Format(_T("GetThreadContext Error : %d"), GetLastError());
            break;
        }

        DWORD64 LpAddr = VirtualAllocEx64(pi.hProcess, (DWORD64)NULL, (SIZE_T)sizeof(InjectBuf), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (LpAddr == NULL)
        {
            szErrorMsg.Format(_T("VirtualAlloc Error : %d"), GetLastError());
            break;
        }

        InjectBufX64 inBuf;

        *(DWORD64*)&puShellCode_x64[27] = (DWORD64)LpAddr;
        *(DWORD64*)&puShellCode_x64[60] = (DWORD64)GetProcAddress64(GetModuleHandle64(L"ntdll.dll"), "LdrLoadDll");
        *(DWORD64*)&puShellCode_x64[106] = (DWORD64)GetProcAddress64(GetModuleHandle64(L"ntdll.dll"), "LdrGetProcedureAddress");
        *(DWORD*)&puShellCode_x64[191] = (DWORD)ctx.Rcx;
        *(DWORD*)&puShellCode_x64[199] = (DWORD)(ctx.Rcx >> 32);

        ctx.Rcx = (DWORD64)LpAddr + MAX_PATH * sizeof(TCHAR) + sizeof(inBuf.szFuncName) + sizeof(STRING) + sizeof(STRING);

        strcpy_s(inBuf.szFuncName, 64, CW2A(szFunc));
        inBuf.asFuncName.Length = strlen(inBuf.szFuncName);
        inBuf.asFuncName.MaximumLength = sizeof(inBuf.szFuncName);
        inBuf.asFuncName.Buffer = (DWORD64)LpAddr + sizeof(inBuf.asFuncName);

        wcscpy_s(inBuf.szDllPath, MAX_PATH, szDllPath);
        inBuf.usDllPath.Length = wcslen(inBuf.szDllPath)*2;
        inBuf.usDllPath.MaximumLength = sizeof(inBuf.szDllPath);
        inBuf.usDllPath.Buffer = (DWORD64)LpAddr + sizeof(inBuf.asFuncName) + sizeof(inBuf.szFuncName) + sizeof(inBuf.usDllPath);

        memcpy(inBuf.szShellcode, puShellCode_x64, sizeof(puShellCode_x64));

        if (!WriteProcessMemory64(pi.hProcess, LpAddr, &inBuf, sizeof(inBuf), NULL))
        {
            szErrorMsg.Format(_T("WriteProcessMemory error : %d"), GetLastError());
            break;
        }

        CString szParam;
        szParam.Format(L"pRemoteAddr : 0x%08x%08x", ctx.Rcx >>32, ctx.Rcx & 0x0ffffffff);
        MessageBox(NULL, szParam, L"click to continue run ", MB_OK);

        if (!SetThreadContext64(pi.hThread, &ctx))
        {
            szErrorMsg.Format(_T("SetThreadContext error : %d"), GetLastError());
            break;
        }

        bStatus = TRUE;
        szErrorMsg.Format(_T("hijack process eip success "));
    } while (0);

    if (szErrorMsg.GetLength())
    {
        Utils::SetLastErrorMsg(szErrorMsg);
    }

    ResumeThread(pi.hThread);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return bStatus;
}

BOOL PSI::RemoteInjectExe(DWORD dwRemoteProcessID, CString szParam, CString szDllPath, CString szFunc)
{
    BOOL bStatus = FALSE;

    // 提权
    CPeOpr::EnableDebugPriv();
    
    // 打开远程线程
    HANDLE hRemoteProcess;
    if ((hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, dwRemoteProcessID)) == NULL)
    {
        return bStatus;
    }

    do
    {
        // 32 位系统直接走 32 位逻辑
        if (CPeOpr::Is64bitSystem() == FALSE)
        {
            bStatus = RemoteInjectX86Exe(hRemoteProcess, szParam, szDllPath, szFunc);
            break;
        }

        // 64位系统，需判断目标是否 是64位
        BOOL bWow64 = FALSE;
        if (IsWow64Process(hRemoteProcess, &bWow64) == FALSE)
        {
            break;
        }

        if (bWow64)
        {
            bStatus = RemoteInjectX86Exe(hRemoteProcess, szParam, szDllPath, szFunc);
            break;
        }

        bStatus = RemoteInjectX64Exe(hRemoteProcess, szParam, szDllPath, szFunc);
        break;
    } while (FALSE);
    
    CloseHandle(hRemoteProcess);
    return bStatus;
}

BOOL PSI::RemoteInjectX86Exe(HANDLE hProcess, CString szParam, CString szDllPath, CString szFunc)
{
    BOOL bStatus = FALSE;
    HANDLE hRemoteThread = NULL;

    CString szErrorMsg;
    do
    {
        LPVOID LpAddr = VirtualAllocEx(hProcess, NULL, sizeof(InjectBuf), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (LpAddr == NULL)
        {
            szErrorMsg.Format(_T("VirtualAlloc Error : %d"), GetLastError());
            break;
        }

        InjectBuf inBuf;

        *(DWORD*)&puShellCode_RT[9] = (DWORD)LpAddr;
        *(DWORD*)&puShellCode_RT[14] = (DWORD)LpAddr + sizeof(inBuf.szFuncName);
        *(DWORD*)&puShellCode_RT[19] = (DWORD)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "LoadLibraryA");
        *(DWORD*)&puShellCode_RT[27] = (DWORD)GetProcAddress(GetModuleHandle(L"Kernel32.dll"), "GetProcAddress");

        strcpy_s(inBuf.szDllPath, MAX_PATH, CW2A(szDllPath));
        strcpy_s(inBuf.szFuncName, 64, CW2A(szFunc));
        memcpy(inBuf.szShellcode, puShellCode_RT, sizeof(puShellCode_RT));

        if (!WriteProcessMemory(hProcess, LpAddr, &inBuf, sizeof(inBuf), NULL))
        {
            szErrorMsg.Format(_T("WriteProcessMemory error : %d"), GetLastError());
            break;
        }

        CString szParam;
        szParam.Format(L"pRemoteAddr : %p", LpAddr);
        MessageBox(NULL, szParam, L"click to continue run ", MB_OK);

        typedef DWORD(WINAPI *typedef_ZwCreateThreadEx)(
            PHANDLE ThreadHandle,
            ACCESS_MASK DesiredAccess,
            LPVOID ObjectAttributes,
            HANDLE ProcessHandle,
            LPTHREAD_START_ROUTINE lpStartAddress,
            LPVOID lpParameter,
            BOOL CreateSuspended,
            DWORD dwStackSize,
            DWORD dw1,
            DWORD dw2,
            LPVOID pUnkown);

        HMODULE hNtdllDll = GetModuleHandleA("ntdll.dll");
        if (NULL == hNtdllDll)
        {
            MessageBox(NULL, L"LoadLibraryA ntdll.dll  failed", L"", MB_OK);
            break;
        }

        char *pStartAddr = (char*)LpAddr;
        pStartAddr = pStartAddr + MAX_PATH + 64;

        typedef_ZwCreateThreadEx ZwCreateThreadEx = (typedef_ZwCreateThreadEx)::GetProcAddress(hNtdllDll, "NtCreateThreadEx");
        if (NULL == ZwCreateThreadEx)
        {
            MessageBox(NULL, L"get proc addr ZwCreateThreadEx failed try CreateRemoteThread", L"", MB_OK);
            HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pStartAddr, NULL, 0, NULL);
            if (hThread)
            {
                bStatus = TRUE;
                break;
            }

            MessageBox(NULL, L" CreateRemoteThread failed fuck", L"", MB_OK);
            break;
        }
        
        // 使用 ZwCreateThreadEx 创建远线程, 实现 DLL 注入
        DWORD dwStatus = ZwCreateThreadEx(&hRemoteThread, STANDARD_RIGHTS_ALL, NULL, hProcess, (LPTHREAD_START_ROUTINE)pStartAddr, NULL, 0, 0, 0, 0, NULL);
        if (NULL == hRemoteThread)
        {
            CString szError;
            szError.Format(L"%p", dwStatus);
            MessageBox(NULL, L"ZwCreateThreadEx  failed", szError, MB_OK);
            break;
        }

        bStatus = TRUE;
    } while (0);


    if (hRemoteThread)
    {
        CloseHandle(hRemoteThread);
    }

    return bStatus;
}

BOOL PSI::RemoteInjectX64Exe(HANDLE hProcess, CString szParam, CString szDllPath, CString szFunc)
{
    BOOL bStatus = FALSE;
    CString szErrorMsg;
    HANDLE hRemoteThread = NULL;
    do
    {
        DWORD64 LpAddr = VirtualAllocEx64(hProcess, (DWORD64)NULL, (SIZE_T)sizeof(InjectBuf), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        if (LpAddr == NULL)
        {
            szErrorMsg.Format(_T("VirtualAlloc Error : %d"), GetLastError());
            break;
        }

        InjectBufX64 inBuf;

        *(DWORD64*)&puShellCode_RT_x64[27] = (DWORD64)LpAddr;
        *(DWORD64*)&puShellCode_RT_x64[60] = (DWORD64)GetProcAddress64(GetModuleHandle64(L"ntdll.dll"), "LdrLoadDll");
        *(DWORD64*)&puShellCode_RT_x64[106] = (DWORD64)GetProcAddress64(GetModuleHandle64(L"ntdll.dll"), "LdrGetProcedureAddress");

        strcpy_s(inBuf.szFuncName, 64, CW2A(szFunc));
        inBuf.asFuncName.Length = strlen(inBuf.szFuncName);
        inBuf.asFuncName.MaximumLength = sizeof(inBuf.szFuncName);
        inBuf.asFuncName.Buffer = (DWORD64)LpAddr + sizeof(inBuf.asFuncName);

        wcscpy_s(inBuf.szDllPath, MAX_PATH, szDllPath);
        inBuf.usDllPath.Length = wcslen(inBuf.szDllPath) * 2;
        inBuf.usDllPath.MaximumLength = sizeof(inBuf.szDllPath);
        inBuf.usDllPath.Buffer = (DWORD64)LpAddr + sizeof(inBuf.asFuncName) + sizeof(inBuf.szFuncName) + sizeof(inBuf.usDllPath);

        memcpy(inBuf.szShellcode, puShellCode_RT_x64, sizeof(puShellCode_RT_x64));

        if (!WriteProcessMemory64(hProcess, LpAddr, &inBuf, sizeof(inBuf), NULL))
        {
            szErrorMsg.Format(_T("WriteProcessMemory error : %d"), GetLastError());
            break;
        }

        DWORD64 pStartAddr = LpAddr + MAX_PATH * sizeof(TCHAR) + sizeof(inBuf.szFuncName) + sizeof(STRING) + sizeof(STRING);

        CString szParam;
        szParam.Format(L"pRemoteAddr : 0x%08x%08x", pStartAddr >> 32, pStartAddr & 0x0ffffffff);
        MessageBox(NULL, szParam, L"click to continue run ", MB_OK);

        DWORD64 dwStatus = ZwCreateThreadEx64(&hRemoteThread, STANDARD_RIGHTS_ALL, NULL, hProcess, (DWORD64)pStartAddr, NULL, 0, 0, 0, 0, NULL);
        if (NULL == hRemoteThread)
        {
            CString szError;
            szError.Format(L"pRemoteAddr : 0x%08x%08x", dwStatus >> 32, dwStatus & 0x0ffffffff);
            MessageBox(NULL, L"ZwCreateThreadEx64  failed", szError, MB_OK);
            break;
        }

        bStatus = TRUE;
    } while (0);

    if (hRemoteThread)
    {
        CloseHandle(hRemoteThread);
    }

    return bStatus;
}
