#include "stdafx.h"

#include "PeOperation.h"

DWORD CPeOpr::GetPEFileBit(LPCTSTR lpFilePath, DWORD * pdwBit)
{
    DWORD dwStatus = ST_ERROR_FAIL;
    HANDLE hFile = INVALID_HANDLE_VALUE;

    if (pdwBit == NULL)
    {
        return 0;
    }

    hFile = CreateFile(lpFilePath, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    do
    {
        LARGE_INTEGER FileSize = { 0 };
        if (GetFileSizeEx(hFile, &FileSize) == FALSE)
        {
            dwStatus = GetLastError();
            break;
        }

        if (0 == FileSize.HighPart && FileSize.LowPart >= 0)
        {
            IMAGE_DOS_HEADER DosHdr;
            DWORD dwBytesRead = 0;
            
            if (ReadFile(hFile, &DosHdr, sizeof(DosHdr), &dwBytesRead, NULL) == FALSE)
            {
                dwStatus = GetLastError();
                break;
            }

            if (DosHdr.e_magic != IMAGE_DOS_SIGNATURE)
            {
                break;
            }

            LONG ulToMoveHigh = 0;
            if (SetFilePointer(hFile, DosHdr.e_lfanew, &ulToMoveHigh, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
            {
                dwStatus = GetLastError();
                break;
            }

            IMAGE_NT_HEADERS32 NtHdr;
            if (ReadFile(hFile, &NtHdr, sizeof(NtHdr), &dwBytesRead, NULL) == FALSE)
            {
                dwStatus = GetLastError();
                break;
            }

            if (NtHdr.FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64 || NtHdr.FileHeader.Machine == IMAGE_FILE_MACHINE_IA64)
            {
                *pdwBit = PE_OPR_64;
                dwStatus = ERROR_SUCCESS;
            }
            else if (NtHdr.FileHeader.Machine == IMAGE_FILE_MACHINE_I386)
            {
                *pdwBit = PE_OPR_32;
                dwStatus = ERROR_SUCCESS;
            }
        }
    } while (FALSE);
    CloseHandle(hFile);

    return dwStatus;
}

BOOL CPeOpr::EnableDebugPriv()
{
    BOOL bStatus = FALSE;
    HANDLE hToken = INVALID_HANDLE_VALUE;
    LUID sedebugnameValue;
    TOKEN_PRIVILEGES tkp;

    do
    {
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        {
            break;
        }

        if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue))
        {
            break;
        }

        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Luid = sedebugnameValue;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
        {
            break;
        }

        bStatus = TRUE;
    } while (0);

    CloseHandle(hToken);
    return bStatus;
}

BOOL CPeOpr::Is64bitSystem()
{
    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);

    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
        si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
