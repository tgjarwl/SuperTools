#include "stdafx.h"
#include "MainDlg.h"
#include "AboutDlg.h"
#include "DlgEncodingDigital.h"
#include "DlgEncodingConv.h"
#include "DlgHash.h"
#include "DlgInject.h"
#include "WmiHelper.h"
#include "st_convert.h"

#define COMBO_INDEX_ERROR_FORMAT    0
#define COMBO_INDEX_WMI             2

BOOL CMainDlg::PreTranslateMessage(MSG * pMsg)
{
    return CWindow::IsDialogMessage(pMsg);
}

BOOL CMainDlg::OnIdle()
{
    UIUpdateChildWindows();
    return FALSE;
}

LRESULT CMainDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    // center the dialog on the screen
    CenterWindow();

    // set icons
    HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
    SetIcon(hIconSmall, FALSE);

    SetMenu(AtlLoadMenu(IDR_MENU1));

    // register object for message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->AddMessageFilter(this);
    pLoop->AddIdleHandler(this);

    UIAddChildWindowContainer(m_hWnd);

    // RegInfo
    MsgCtl::RegOutputInfo(m_hWnd, IDC_EDIT_OUTPUT);


    ComboBox_InsertString(GetDlgItem(IDC_COMBO_CMD_TYPE), COMBO_INDEX_ERROR_FORMAT, L"错误码");
    //ComboBox_InsertString(GetDlgItem(IDC_COMBO_CMD_TYPE), COMBO_INDEX_WMI, L"WMI");

    ComboBox_SetCurSel(GetDlgItem(IDC_COMBO_CMD_TYPE), COMBO_INDEX_ERROR_FORMAT);
    SetDlgItemText(IDC_EDIT_CMD_BAR, L"0x00000005 | 5");

    AddTrayNotify(m_hWnd);

    return TRUE;
}

LRESULT CMainDlg::OnDestroy(UINT, WPARAM, LPARAM, BOOL &)
{
    // unregister message filtering and idle updates
    CMessageLoop* pLoop = _Module.GetMessageLoop();
    ATLASSERT(pLoop != NULL);
    pLoop->RemoveMessageFilter(this);
    pLoop->RemoveIdleHandler(this);

    return 0;
}

LRESULT CMainDlg::OnAppAbout(WORD, WORD, HWND, BOOL &)
{
    CAboutDlg dlg;
    dlg.DoModal();
    return 0;
}

LRESULT CMainDlg::OnOK(WORD, WORD wID, HWND, BOOL &)
{
    // TODO: Add validation code 
    Shell_NotifyIcon(NIM_DELETE, &m_TrayNotify);
    CloseDialog(wID);
    return 0;
}

LRESULT CMainDlg::OnCancel(WORD, WORD wID, HWND, BOOL &)
{
    ShowWindow(SW_HIDE);
    return 0;
}

void CMainDlg::CloseDialog(int nVal)
{
    DestroyWindow();
    ::PostQuitMessage(nVal);
}

LRESULT CMainDlg::OnToolEncodingDigital(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加命令处理程序代码
    CDlgEncodingDigital dlg;
    dlg.DoModal(NULL);
    return 0;
}

LRESULT CMainDlg::OnToolEncodingConv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加命令处理程序代码
    CDlgEncodingConv dlg;
    dlg.DoModal(NULL);
    return 0;
}

LRESULT CMainDlg::OnToolHash(WORD, WORD, HWND, BOOL &)
{
    CDlgHash dlg;
    dlg.DoModal(NULL);
    return 0;
}


LRESULT CMainDlg::OnToolInject(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加命令处理程序代码
    CDlgInject dlg;
    dlg.DoModal(NULL);
    return 0;
}

LRESULT CMainDlg::AddTrayNotify(HWND hWnd)
{
    m_TrayNotify = { 0 };
    m_TrayNotify.cbSize = sizeof(NOTIFYICONDATA);
    m_TrayNotify.hWnd = hWnd;
    m_TrayNotify.uID = IDR_MAINFRAME;

    m_TrayNotify.hIcon = AtlLoadIcon(IDR_MAINFRAME);
    wcscpy(m_TrayNotify.szTip, L"SuperTools");
    m_TrayNotify.uCallbackMessage = TRAY_NOTIFYICON;
    m_TrayNotify.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    Shell_NotifyIcon(NIM_ADD, &m_TrayNotify);

    return 0;
}

LRESULT CMainDlg::ShowTrayMenu()
{
    LPPOINT mouse_pt = new tagPOINT;
    ::GetCursorPos(mouse_pt);

    HMENU hMenu = AtlLoadMenu(IDR_MENU1);
    HMENU hMenuTool = GetSubMenu(hMenu, 1);
    
    AppendMenu(hMenuTool, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hMenuTool, MF_STRING, ID_TOOL_SHOW_MW, L"显示主窗口");

    AppendMenu(hMenuTool, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hMenuTool, MF_STRING, ID_TOOL_QUIT, L"退出");

    SetForegroundWindow(m_hWnd);
    TrackPopupMenu(hMenuTool, TPM_LEFTALIGN, mouse_pt->x, mouse_pt->y, 0, m_hWnd, 0);
    DestroyMenu(hMenu);
    delete mouse_pt;

    return S_OK;
}

LRESULT CMainDlg::OnTrayNotify(UINT, WPARAM wParam, LPARAM lParam, BOOL &)
{
    switch (lParam)
    {
    case WM_RBUTTONUP:
    {
        ShowTrayMenu();
        break;
    }
    case WM_LBUTTONDBLCLK:
    {
        ShowWindow(SW_SHOW);
        break;
    }
    default:
        break;
    }

    return S_OK;
}

LRESULT CMainDlg::OnShowMainDlg(WORD, WORD wID, HWND, BOOL &)
{
    //Shell_NotifyIcon(NIM_DELETE, &m_TrayNotify);
    ShowWindow(SW_SHOW);
    return S_OK;
}


LRESULT CMainDlg::OnBnClickedButtonDo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    int nCurSel = ComboBox_GetCurSel(GetDlgItem(IDC_COMBO_CMD_TYPE));
    switch (nCurSel)
    {
    case COMBO_INDEX_ERROR_FORMAT:
    {
        CString szError;
        GetDlgItemText(IDC_EDIT_CMD_BAR, szError);
        CString szErrorRst = Utils::ErrorCodeToMessage(wcstoul(szError, NULL, 0));
        MsgCtl::PresentMsg(m_hWnd, IDC_EDIT_OUTPUT, szErrorRst);
        break;
    }
    case COMBO_INDEX_WMI :
    {
        CString szIP;
        GetDlgItemText(IDC_EDIT_CMD_BAR, szIP);

        vector<CString> vecUseDefault;
        CWmi::Instance()->CrackPassword(szIP, "Administrator", vecUseDefault);
        break;
    }
    default:
        break;
    }
    return 0;
}
