#pragma once

class CDlgEncodingConv : public CDialogImpl<CDlgEncodingConv>
{
public:
    enum { IDD = IDD_DLG_ENCODING_CONV};

    BEGIN_MSG_MAP(CDlgEncodingConv)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
        COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
        COMMAND_HANDLER(IDC_EDIT_INPUT, EN_CHANGE, OnEnChangeEditInput)
        COMMAND_HANDLER(IDC_BTN_HEX_2_TEXT, BN_CLICKED, OnBnClickedBtnHex2Text)
        COMMAND_HANDLER(IDC_BTN_DEC_2_TEXT, BN_CLICKED, OnBnClickedBtnDec2Text)
        COMMAND_HANDLER(IDC_BTN_TEXT_2_HEX, BN_CLICKED, OnBnClickedBtnText2Hex)
        COMMAND_HANDLER(IDC_BTN_BASE64_DECODE, BN_CLICKED, OnBnClickedBtnBase64Decode)
        COMMAND_HANDLER(IDC_CHECK_AUTO_CONV, BN_CLICKED, OnBnClickedCheckAutoConv)
        COMMAND_HANDLER(IDC_BTN_BASE64_ENCODE, BN_CLICKED, OnBnClickedBtnBase64Encode)
    END_MSG_MAP()

    // Handler prototypes (uncomment arguments if needed):
    //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)


private:
    DWORD m_selMode;
    DWORD m_autoConv;

public:
    DWORD SeleteMode(DWORD dwMode, BOOL bClearCtrl = 1);
    DWORD ClearCtrls();

public:
    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnEnChangeEditInput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnHex2Text(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnDec2Text(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnText2Hex(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnBase64Decode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedCheckAutoConv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBnClickedBtnBase64Encode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};

