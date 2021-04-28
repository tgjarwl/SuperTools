#include "stdafx.h"
#include "st_convert.h"

BOOL Dec2TextA(LPCSTR lpDecimal, int len, byte *lpOut, int outLen)
{
    int nOutIndex = 0;
    ZeroMemory(lpOut, outLen);

    CStringA szADec;
    szADec.Append(lpDecimal, len);

    int iPos = 0;
    CStringA strTmp;
    strTmp = szADec.Tokenize(" ", iPos);
    while (strTmp.Trim() != _T(""))
    {
        DWORD dwHex = atoi(strTmp);
        lpOut[nOutIndex++] = byte(dwHex);

        strTmp = szADec.Tokenize(" ", iPos);
    }

    if (nOutIndex)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL Dec2TextW(LPCWSTR lpDecimal, int len, byte *lpOut, int outLen)
{
    CString szDecimal;
    szDecimal.Append(lpDecimal, len);

    CStringA szADecimal = szDecimal;

    return Dec2TextA(szADecimal, szADecimal.GetLength(), lpOut, outLen);
}

BOOL Hex2TextA(LPCSTR lpHex, int len, byte *lpOut, int outLen)
{
    int outIndex = 0;
    ZeroMemory(lpOut, outLen);

    int chPair[2] = { 0 };
    int pariIndex = 0;

    int index = 0;
    while (index < len)
    {
        char ch = lpHex[index++];
        if ((ch >= 'a' && ch <= 'f'))
        {
            chPair[pariIndex++] = ch - 'a' + 10;
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            chPair[pariIndex++] = ch - 'A' + 10;
        }
        else if (ch >= '0' && ch <= '9')
        {
            chPair[pariIndex++] = ch - '0';
        }

        if (pariIndex == 2)
        {
            char chDigit = ((chPair[0] << 4) | chPair[1]) & 0xff;
            lpOut[outIndex++] = chDigit;

            pariIndex = 0;
            chPair[0] = 0;
            chPair[0] = 0;
        }
    }

    if (pariIndex == 1)
    {
        char chDigit = chPair[0];
        lpOut[outIndex++] = chDigit;

        pariIndex = 0;
        chPair[0] = 0;
        chPair[0] = 0;
    }

    if (outIndex)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL Hex2TextW(LPCWSTR lpHex, int len, byte *lpOut, int outLen)
{
    CString szHex;
    szHex.Append(lpHex, len);

    CStringA szAHex = szHex;
    return Hex2TextA(szAHex, szAHex.GetLength(), lpOut, outLen);

}

BOOL Text2HexA(byte* lpText, int len, CStringA &szOut)
{
    int chPair[2] = { 0 };
    int pariIndex = 0;

    int index = 0;
    while (index < len)
    {
        DWORD ch = lpText[index++];
        CStringA szCh;
        szCh.Format("%02X ", ch);
        szOut += szCh;
    }

    if (szOut.GetLength())
    {
        return TRUE;
    }
    return TRUE;
}

BOOL Text2HexW(byte* lpText, int len, CStringW &szOut)
{
    CStringA szAOut;
    BOOL bStatus = Text2HexA(lpText, len, szAOut);

    if (bStatus)
    {
        szOut = szAOut;
    }

    return bStatus;
}

BOOL Hex2IntA(LPCSTR lpHex, int & outValue)
{
    BOOL bRet = FALSE;
    int textLen = strlen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextA(lpHex, strlen(lpHex), lpText, textLen))
        {
            outValue = *(int*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }
    
    return bRet;
}

BOOL Hex2IntW(LPCWSTR lpHex, int & outValue)
{
    BOOL bRet = FALSE;
    int textLen = wcslen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextW(lpHex, wcslen(lpHex), lpText, textLen))
        {
            outValue = *(int*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }

    return bRet;
}

BOOL Hex2FloatA(LPCSTR lpHex, float & outValue)
{
    BOOL bRet = FALSE;
    int textLen = strlen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextA(lpHex, strlen(lpHex), lpText, textLen))
        {
            outValue = *(float*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }

    return bRet;
}

BOOL Hex2FloatW(LPCWSTR lpHex, float & outValue)
{
    BOOL bRet = FALSE;
    int textLen = wcslen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextW(lpHex, wcslen(lpHex), lpText, textLen))
        {
            outValue = *(float*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }

    return bRet;
}

BOOL Hex2DoubleA(LPCSTR lpHex, double & outValue)
{
    BOOL bRet = FALSE;
    int textLen = strlen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextA(lpHex, strlen(lpHex), lpText, textLen))
        {
            outValue = *(double*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }

    return bRet;
}

BOOL Hex2DoubleW(LPCWSTR lpHex, double & outValue)
{
    BOOL bRet = FALSE;
    int textLen = wcslen(lpHex) * 3 + 4;
    byte *lpText = (byte*)malloc(textLen);
    {
        if (Hex2TextW(lpHex, wcslen(lpHex), lpText, textLen))
        {
            outValue = *(double*)lpText;
            bRet = TRUE;
        }

        free(lpText);
    }

    return bRet;
}
