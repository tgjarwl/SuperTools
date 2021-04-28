#pragma once

#define PE_OPR_32   32
#define PE_OPR_64   64

class CPeOpr
{
public:
    static DWORD GetPEFileBit(LPCTSTR lpFilePath, DWORD * pdwBit);
    static BOOL EnableDebugPriv();

    static BOOL Is64bitSystem();

};

