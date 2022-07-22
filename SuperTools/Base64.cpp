#include "stdafx.h"
#include "Base64.h"


BOOL base64::Base64Encrypt(BYTE* lpIn, DWORD pInLen, CStringA &szOut)
{
#define CRYPT_STRING_BASE64 0x00000001
#define CRYPT_STRING_NOCRLF 0x40000000
    typedef BOOL(WINAPI *pfnCryptBinaryToStringA)(CONST BYTE *pbBinary, DWORD cbBinary, DWORD dwFlags, LPSTR pszString, DWORD *pcchString);
    static pfnCryptBinaryToStringA CryptBinaryToStringA = NULL;

    if (CryptBinaryToStringA == NULL)
    {
        CryptBinaryToStringA = (pfnCryptBinaryToStringA)GetProcAddress(LoadLibraryA("Crypt32.DLL"), "CryptBinaryToStringA");
    }

    if (!CryptBinaryToStringA)
    {
        return FALSE;
    }

    BOOL bSuccess = FALSE;

    DWORD nLenOut = pInLen * 4 / 3 + 4;
    CHAR *pDst = new CHAR[nLenOut];
    if (pDst)
    {
        memset(pDst, 0, nLenOut);

        bSuccess = CryptBinaryToStringA(
            (const BYTE*)lpIn, pInLen,
            CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
            pDst, &nLenOut
        );
        if (bSuccess)
        {
            szOut = pDst;
        }

        delete[] pDst;
    }

    return bSuccess;
}

BOOL base64::Base64Decrypt(CStringA strSrc, BYTE* lpOut, DWORD *pOutLen)
{
    BOOL bRet = FALSE;

#define CRYPT_STRING_BASE64 0x00000001
    typedef BOOL(WINAPI *pfnCryptStringToBinaryA)(LPCSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary, DWORD  *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);
    static pfnCryptStringToBinaryA CryptStringToBinaryA = NULL;
    if (CryptStringToBinaryA == NULL)
    {
        CryptStringToBinaryA = (pfnCryptStringToBinaryA)GetProcAddress(LoadLibraryA("Crypt32.DLL"), "CryptStringToBinaryA");
        if (!CryptStringToBinaryA)
            return bRet;
    }

    DWORD nLenOut = strSrc.GetLength() + 4;

    BYTE *pDst = (BYTE *)malloc(nLenOut);
    if (pDst == NULL)
        return bRet;

    ZeroMemory(pDst, nLenOut);

    DWORD dwBinaryLength = nLenOut;
    BOOL fRet = CryptStringToBinaryA(
        (LPCSTR)strSrc, strSrc.GetLength(),
        CRYPT_STRING_BASE64,
        (BYTE*)pDst, &dwBinaryLength,
        NULL,
        NULL
    );

    if (fRet)
    {
        if (*pOutLen < dwBinaryLength)
        {
            *pOutLen = dwBinaryLength;
        }
        else
        {
            memcpy(lpOut, pDst, dwBinaryLength);
            *pOutLen = dwBinaryLength;
            bRet = TRUE;
        }
    }

    free(pDst);

    return bRet;
}

BOOL SaveDataToFile(LPCWSTR lpFilePath, BYTE *lpBuf, DWORD dwLen)
{
    HANDLE hFile = CreateFile(lpFilePath,
        FILE_GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_DELETE | FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        0,
        NULL);

    if (INVALID_HANDLE_VALUE == hFile)
    {
        DWORD dwError = GetLastError();
        return FALSE;
    }

    DWORD dwNumberOfBytesWritten = 0;
    if (!WriteFile(hFile, lpBuf, dwLen, &dwNumberOfBytesWritten, NULL))
    {
        return FALSE;
    }

    CloseHandle(hFile);
    return TRUE;
}

BOOL base64::Base64Decrypt2File(CStringA strSrc, CString szFilePath)
{
    BOOL bRet = FALSE;

#define CRYPT_STRING_BASE64 0x00000001
    typedef BOOL(WINAPI *pfnCryptStringToBinaryA)(LPCSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary, DWORD  *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);
    static pfnCryptStringToBinaryA CryptStringToBinaryA = NULL;
    if (CryptStringToBinaryA == NULL)
    {
        CryptStringToBinaryA = (pfnCryptStringToBinaryA)GetProcAddress(LoadLibraryA("Crypt32.DLL"), "CryptStringToBinaryA");
        if (!CryptStringToBinaryA)
            return bRet;
    }

    DWORD nLenOut = strSrc.GetLength() + 4;

    BYTE *pDst = (BYTE *)malloc(nLenOut);
    if (pDst == NULL)
        return bRet;

    ZeroMemory(pDst, nLenOut);

    DWORD dwBinaryLength = nLenOut;
    BOOL fRet = CryptStringToBinaryA(
        (LPCSTR)strSrc, strSrc.GetLength(),
        CRYPT_STRING_BASE64,
        (BYTE*)pDst, &dwBinaryLength,
        NULL,
        NULL
    );
    if (fRet)
    {
        if (SaveDataToFile(szFilePath, pDst, dwBinaryLength))
        {
            bRet = TRUE;
        }

    }

    free(pDst);

    return bRet;
}

BOOL base64::Base64DecryptFile(CString strSrc, CString strDst)
{
    BOOL bRet = FALSE;

#define CRYPT_STRING_BASE64 0x00000001
    typedef BOOL(WINAPI *pfnCryptStringToBinaryA)(LPCSTR pszString, DWORD cchString, DWORD dwFlags, BYTE *pbBinary, DWORD  *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags);
    static pfnCryptStringToBinaryA CryptStringToBinaryA = NULL;
    if (CryptStringToBinaryA == NULL)
    {
        CryptStringToBinaryA = (pfnCryptStringToBinaryA)GetProcAddress(LoadLibraryA("Crypt32.DLL"), "CryptStringToBinaryA");
        if (!CryptStringToBinaryA)
            return bRet;
    }

    HANDLE hFile = CreateFile(strSrc,
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    DWORD dwHign;
    DWORD dwFileLen = GetFileSize(hFile, &dwHign);
    BYTE *pSrc = (BYTE *)malloc(dwFileLen);
    if (pSrc == NULL)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    if (ReadFile(hFile, pSrc, dwFileLen, &dwHign, NULL) == FALSE)
    {
        free(pSrc);
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);

    DWORD nLenOut = dwFileLen + 4;
    BYTE *pDst = (BYTE *)malloc(nLenOut);
    if (pDst == NULL)
        return bRet;

    ZeroMemory(pDst, nLenOut);


    DWORD dwBinaryLength = nLenOut;
    BOOL fRet = CryptStringToBinaryA(
        (LPCSTR)pSrc, dwFileLen,
        CRYPT_STRING_BASE64,
        (BYTE*)pDst, &dwBinaryLength,
        NULL,
        NULL
    );
    if (fRet)
    {
        if (SaveDataToFile(strDst, pDst, dwBinaryLength))
        {
            bRet = TRUE;
        }
    }

    free(pDst);

    return bRet;
}
