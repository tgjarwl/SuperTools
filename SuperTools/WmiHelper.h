#pragma once
class CWmi
{
public:
    static CWmi * Instance()
    {
        static CWmi inst;
        return &inst;
    }

    static unsigned int WINAPI CrackProxy(void *lpParam);
    DWORD CrackPassword(CString szIP, CString szUser, vector<CString> &vecPassDict);

    DWORD InvokeMethod(CString szObject, CString szMethod, CString szCmdline);

private:
    CWmi();
    ~CWmi();
};

