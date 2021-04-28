// aboutdlg.h : interface of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CDlgHash : public CDialogImpl<CDlgHash>
{
public:
    enum { IDD = IDD_DLG_HASH };

    BEGIN_MSG_MAP(CDlgHash)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        COMMAND_HANDLER(IDC_BTN_DLG_HASH_BKDR, BN_CLICKED, OnBnClickedBtnDlgHashBkdr)
        COMMAND_HANDLER(IDC_RADIO_HASH_NORMAL, BN_CLICKED, OnBnClickedRadioHashNormal)
        COMMAND_HANDLER(IDC_RADIO_HASH_LOW, BN_CLICKED, OnBnClickedRadioHashLow)
        COMMAND_HANDLER(IDC_RADIO_HASH_UPPER, BN_CLICKED, OnBnClickedRadioHashUpper)
        COMMAND_HANDLER(IDC_EDIT_DLG_HASH_INPUT, EN_CHANGE, OnEnChangeEditDlgHashInput)
    END_MSG_MAP()

public:
    DWORD   m_defaultCheck;
    CString m_szInputMormal;

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)


    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnDlgHashBkdr(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioHashNormal(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioHashLow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioHashUpper(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnEnChangeEditDlgHashInput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
