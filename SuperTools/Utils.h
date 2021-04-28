#pragma once
namespace Utils
{
    CString ErrorCodeToMessage(DWORD dwError);

    VOID SetLastErrorMsg(CString szErrMsg);
    CString GetLastErrorMsg();
};
