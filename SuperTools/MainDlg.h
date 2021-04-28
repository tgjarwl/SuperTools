// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#define TRAY_NOTIFYICON                 WM_USER+1

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

    virtual BOOL PreTranslateMessage(MSG* pMsg);


    virtual BOOL OnIdle();


	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
        MESSAGE_HANDLER(TRAY_NOTIFYICON, OnTrayNotify)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
        COMMAND_ID_HANDLER(ID_TOOL_ENCODING_CONV, OnToolEncodingConv)
        COMMAND_ID_HANDLER(ID_TOOL_ENCODING_DIGITAL, OnToolEncodingDigital)
        COMMAND_ID_HANDLER(ID_TOOL_HASH, OnToolHash)
        COMMAND_ID_HANDLER(ID_TOOL_INJECT, OnToolInject)
        COMMAND_ID_HANDLER(ID_TOOL_QUIT, OnOK)
        COMMAND_ID_HANDLER(ID_TOOL_SHOW_MW, OnShowMainDlg)
        COMMAND_HANDLER(IDC_BUTTON_DO, BN_CLICKED, OnBnClickedButtonDo)
        COMMAND_ID_HANDLER(ID_HELP_ABOUT, OnAppAbout)
    END_MSG_MAP()


// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    void CloseDialog(int nVal);

    // 工具窗口
    LRESULT OnToolEncodingDigital(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnToolEncodingConv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnToolHash(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnToolInject(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

    // 托盘相关
    LRESULT AddTrayNotify(HWND hWnd);
    LRESULT ShowTrayMenu();
    LRESULT OnTrayNotify(UINT, WPARAM wParam, LPARAM lParam, BOOL &);

    LRESULT OnShowMainDlg(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
private:

    NOTIFYICONDATA m_TrayNotify;
public:
    LRESULT OnBnClickedButtonDo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
