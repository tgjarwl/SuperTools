#pragma once

class CDlgEncodingDigital : public CDialogImpl<CDlgEncodingDigital>
{
public:
    enum { IDD = IDD_DLG_ENCODING_DIGITAL };

    BEGIN_MSG_MAP(CDlgEncodingDigital)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        COMMAND_HANDLER(IDC_EDIT_CODE_DIGITAL, EN_CHANGE, OnEnChangeEditCodeDigital)
        COMMAND_HANDLER(IDC_RADIO_INT, BN_CLICKED, OnBnClickedRadioInt)
        COMMAND_HANDLER(IDC_RADIO_FLOAT, BN_CLICKED, OnBnClickedRadioFloat)
        COMMAND_HANDLER(IDC_RADIO_HEX, BN_CLICKED, OnBnClickedRadioHex)
    END_MSG_MAP()


public:
    DWORD   m_defaultCheck;

    void PrintHexValue(LPCWSTR lpData);

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnEnChangeEditCodeDigital(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioInt(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioFloat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedRadioHex(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};

