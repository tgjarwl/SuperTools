#include "stdafx.h"
#include "MyEdit.h"


BOOL CMyEdit::InitCtrl(HWND hParent, UINT uCtrlID)
{
    m_DlgWnd = hParent;
    m_id = uCtrlID;
    return 0;
}

LRESULT CMyEdit::OnDropFiles(UINT uID, WPARAM wParam, LPARAM, BOOL &)
{
    HDROP hDropInfo = (HDROP)wParam;
    int count_droppedfile = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
    for (int i = 0; i < count_droppedfile; ++i)
    {
        wchar_t filepath[MAX_PATH] = { 0 };
        if (DragQueryFile(hDropInfo, i, filepath, MAX_PATH)>0)
        {
            ::SetDlgItemText(m_DlgWnd, m_id, filepath);
        }
    }

    return 0;
}
