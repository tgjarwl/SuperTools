#pragma once

class CMyEdit : public CWindowImpl<CMyEdit>
{
public:
    BEGIN_MSG_MAP(CMyEdit)
        MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
    END_MSG_MAP()

public:
    UINT    m_id;
    HWND    m_DlgWnd;

public:
    BOOL InitCtrl(HWND hParent, UINT uCtrlID);
    LRESULT OnDropFiles(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

