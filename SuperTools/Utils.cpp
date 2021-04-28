#include "stdafx.h"
#include "Utils.h"
#include <winternl.h>
#include <comdef.h>

CString Utils::ErrorCodeToMessage(DWORD dwError)
{
    CString szErrorRst;
    if ((dwError & 0xF0000000) == 0x80000000)
    {
        _com_error error(dwError);
        szErrorRst = error.ErrorMessage();
    }
    else
    {
        if ((dwError & 0xF0000000) == 0xC0000000)
        {
            typedef ULONG(NTAPI *pfn_RtlNtStatusToDosError)(NTSTATUS Status);

            static pfn_RtlNtStatusToDosError pRtlNtStatusToDosError = (pfn_RtlNtStatusToDosError)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "RtlNtStatusToDosError");
            if (pRtlNtStatusToDosError) {
                dwError = pRtlNtStatusToDosError(dwError);
            }
        }

        WCHAR szErrorStr[1024] = { 0 };
        if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, LANG_NEUTRAL, szErrorStr, sizeof(szErrorStr) / sizeof(wchar_t), NULL) == 0)
        {
            szErrorRst = "未找到该错误码的说明";
        }
        else
        {
            szErrorRst = szErrorStr;
        }
    }

    return szErrorRst;
}

CString g_szLastErrorMsg;
VOID Utils::SetLastErrorMsg(CString szErrMsg)
{
    g_szLastErrorMsg = szErrMsg;
    return;
}

CString Utils::GetLastErrorMsg()
{
    return g_szLastErrorMsg;
}
