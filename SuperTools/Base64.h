#pragma once

namespace base64 {
    BOOL Base64Encrypt(BYTE* lpIn, DWORD pInLen, CStringA &szOut);
    BOOL Base64Decrypt(CStringA strSrc, BYTE* lpOut, DWORD *pOutLen);
    BOOL Base64Decrypt2File(CStringA strSrc, CString szFilePath);
    BOOL Base64DecryptFile(CString strSrc, CString strDst);

};

