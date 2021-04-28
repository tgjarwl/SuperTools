#include "stdafx.h"
#include "DlgEncodingConv.h"
#include "Base64.h"
#include "st_convert.h"

#define SEL_MODE_DEFAULT        0
#define SEL_MODE_HEX2TEXT       1
#define SEL_MODE_DEC2TEXT       2
#define SEL_MODE_TEXT2HEX       3
#define SEL_MODE_BASE64ENCODE   4
#define SEL_MODE_BASE64DECODE   5

typedef LRESULT (CDlgEncodingConv::*pfn_BtnClick)(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

typedef struct _ModeConf
{
    DWORD           dwModeID;
    pfn_BtnClick    callbackBtn;
    LPWSTR          lpTips;
}ModeConf;

ModeConf    g_vecConf[] =
{
    { 0, 0, L"输入" },
    { SEL_MODE_HEX2TEXT, &CDlgEncodingConv::OnBnClickedBtnHex2Text, L"输入 - 16进制转文本" },
    { SEL_MODE_DEC2TEXT, &CDlgEncodingConv::OnBnClickedBtnDec2Text, L"输入 - 10进制转文本" },
    { SEL_MODE_TEXT2HEX, &CDlgEncodingConv::OnBnClickedBtnText2Hex, L"输入 - 文本转16进制" },
    { SEL_MODE_BASE64ENCODE, &CDlgEncodingConv::OnBnClickedBtnBase64Encode, L"输入 - base64编码" },
    { SEL_MODE_BASE64DECODE, &CDlgEncodingConv::OnBnClickedBtnBase64Decode, L"输入 - base64解码" }
};

DWORD CDlgEncodingConv::SeleteMode(DWORD dwMode, BOOL bClearCtrl)
{
    m_selMode = dwMode;

    // 清除控件里面的内容
    if (bClearCtrl)
    {
        ClearCtrls();
    }

    DWORD dwSize = sizeof(g_vecConf) / sizeof(ModeConf);
    for (DWORD i = 0; i < dwSize; ++i)
    {
        if (g_vecConf[i].dwModeID == dwMode)
        {
            if (g_vecConf[i].lpTips)
            {
                SetDlgItemText(IDC_STATIC_INPUT, g_vecConf[i].lpTips);
            }
        }
    }

    return 0;
}

DWORD CDlgEncodingConv::ClearCtrls()
{
    SetDlgItemText(IDC_EDIT_STR, L"");
    SetDlgItemText(IDC_EDIT_ASCII, L"");
    SetDlgItemText(IDC_EDIT_UNICODE, L"");
    SetDlgItemText(IDC_EDIT_UTF8, L"");
    return 0;
}

LRESULT CDlgEncodingConv::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    CenterWindow(GetParent());

    SeleteMode(0);

    m_autoConv = 1;
    Button_SetCheck(GetDlgItem(IDC_CHECK_AUTO_CONV), 1);
    return TRUE;
}

LRESULT CDlgEncodingConv::OnCloseCmd(WORD, WORD wID, HWND, BOOL &)
{
    EndDialog(wID);
    return 0;
}


LRESULT CDlgEncodingConv::OnEnChangeEditInput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    if (m_autoConv)
    {
        DWORD dwSize = sizeof(g_vecConf) / sizeof(ModeConf);
        for (DWORD i = 0; i < dwSize; ++i)
        {
            if (g_vecConf[i].dwModeID == m_selMode)
            {
                BOOL bRet;
                if (g_vecConf[i].callbackBtn)
                {
                    (this->*g_vecConf[i].callbackBtn)(0, 0, 0, bRet);
                }
            }
        }
    }

    return 0;
}

LRESULT CDlgEncodingConv::OnBnClickedBtnHex2Text(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    
    
    CString szFormatText;
    if (wID == IDC_EDIT_STR){
        GetDlgItemText(wID, szFormatText);
    }
    else{
        GetDlgItemText(IDC_EDIT_INPUT, szFormatText);
        SeleteMode(SEL_MODE_HEX2TEXT);
    }

    szFormatText.Trim();
    if (szFormatText.GetLength() == 0)
    {
        return 0;
    }

    CString szText;

    int textLen = szFormatText.GetLength() * 3 + 1;
    byte *lpText = (byte*)malloc(textLen);

    {
        Hex2TextW(szFormatText, szFormatText.GetLength(), lpText, textLen);
    }

    CString szTextAscii = CA2W((LPCSTR)lpText);
    SetDlgItemText(IDC_EDIT_ASCII, szTextAscii);

    CString szTextUnicode = (LPCWSTR)lpText;
    SetDlgItemText(IDC_EDIT_UNICODE, szTextUnicode);

    CString szTextUtf8 = CA2W((LPCSTR)lpText, CP_UTF8);
    SetDlgItemText(IDC_EDIT_UTF8, szTextUtf8);

    return 0;
}


LRESULT CDlgEncodingConv::OnBnClickedBtnDec2Text(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SeleteMode(SEL_MODE_DEC2TEXT);

    CString szFormatText;
    GetDlgItemText(IDC_EDIT_INPUT, szFormatText);

    szFormatText.Trim();
    if (szFormatText.GetLength() == 0)
    {
        return 0;
    }

    CString szText;

    int textLen = szFormatText.GetLength() * 3 + 1;
    byte *lpText = (byte*)malloc(textLen);

    {
        Dec2TextW(szFormatText, szFormatText.GetLength(), lpText, textLen);
    }

    CString szTextAscii = CA2W((LPCSTR)lpText);
    SetDlgItemText(IDC_EDIT_ASCII, szTextAscii);

    CString szTextUnicode = (LPCWSTR)lpText;
    SetDlgItemText(IDC_EDIT_UNICODE, szTextUnicode);

    CString szTextUtf8 = CA2W((LPCSTR)lpText, CP_UTF8);
    SetDlgItemText(IDC_EDIT_UTF8, szTextUtf8);
    return 0;
}


LRESULT CDlgEncodingConv::OnBnClickedBtnText2Hex(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SeleteMode(SEL_MODE_TEXT2HEX);

    CString szFormatText;
    GetDlgItemText(IDC_EDIT_INPUT, szFormatText);

    szFormatText.Trim();
    if (szFormatText.GetLength() == 0)
    {
        return 0;
    }

    CString szText;

    int textLen = szFormatText.GetLength() * 3 + 1;
    byte *lpText = (byte*)malloc(textLen);

    {
        CString szTextAscii;
        CStringA szATextAscii = CW2A(szFormatText);
        Text2HexW((byte*)szATextAscii.GetString(), szATextAscii.GetLength(), szTextAscii);
        SetDlgItemText(IDC_EDIT_ASCII, szTextAscii);

        CString szTextUnicode;
        Text2HexW((byte*)szFormatText.GetString(), szFormatText.GetLength() * 2, szTextUnicode);
        SetDlgItemText(IDC_EDIT_UNICODE, szTextUnicode);

        CString szTextUtf8;
        CStringA szATextUtf8 = CW2A(szFormatText, CP_UTF8);
        Text2HexW((byte*)szATextUtf8.GetString(), szATextUtf8.GetLength(), szTextUtf8);
        SetDlgItemText(IDC_EDIT_UTF8, szTextUtf8);
        return 0;
    }

    CString szTextAscii = CA2W((LPCSTR)lpText);
    SetDlgItemText(IDC_EDIT_ASCII, szTextAscii);

    CString szTextUnicode = (LPCWSTR)lpText;
    SetDlgItemText(IDC_EDIT_UNICODE, szTextUnicode);

    CString szTextUtf8 = CA2W((LPCSTR)lpText, CP_UTF8);
    SetDlgItemText(IDC_EDIT_UTF8, szTextUtf8);
    return 0;
}


LRESULT CDlgEncodingConv::OnBnClickedBtnBase64Decode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SeleteMode(SEL_MODE_BASE64DECODE);

    CString szData;
    GetDlgItemText(IDC_EDIT_INPUT, szData);
    szData.Trim();
    if (szData.GetLength() == 0)
    {
        return 0;
    }

    if (FsDisable::Call(PathFileExists, 1, szData.GetString()) == FALSE)
    {
        CStringA szAData = CW2A(szData);
        DWORD dwOutLen = szAData.GetLength() * 4;
        BYTE* pOutData = (BYTE*)malloc(szAData.GetLength() * 4);
        if (base64::Base64Decrypt(szAData, pOutData, &dwOutLen))
        {
            CString szOutData;
            Text2HexW(pOutData, dwOutLen, szOutData);
            MsgCtl::PresentMsg(m_hWnd, IDC_EDIT_STR, szOutData);

            BOOL bRet;
            OnBnClickedBtnHex2Text(0, IDC_EDIT_STR, 0, bRet);
        }

        free(pOutData);
    }
    else
    {
        CString szDstFile = szData + L".dec";
        if (base64::Base64DecryptFile(szData, szDstFile))
        {
            CString szOutData;
            szOutData.Format(L"decrity file path : %s", szDstFile);
            MsgCtl::PresentMsg(m_hWnd, IDC_EDIT_STR, szOutData);
        }
    }
    return 0;
}


LRESULT CDlgEncodingConv::OnBnClickedCheckAutoConv(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    if (BST_CHECKED == Button_GetCheck(GetDlgItem(IDC_CHECK_AUTO_CONV)))
    {
        m_autoConv = 1;
    }
    else
    {
        m_autoConv = 0;
    }
    return 0;
}


LRESULT CDlgEncodingConv::OnBnClickedBtnBase64Encode(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SeleteMode(SEL_MODE_BASE64ENCODE);

    CString szData;
    GetDlgItemText(IDC_EDIT_INPUT, szData);

    szData.Trim();

    if (szData.GetLength())
    {
        CStringA szAData = CW2A(szData);
        CStringA szOut;
        if (base64::Base64Encrypt((BYTE*)szAData.GetString(), szAData.GetLength(), szOut))
        {
            CString szOutData = CA2W(szOut);
            MsgCtl::PresentMsg(m_hWnd, IDC_EDIT_STR, szOutData);

        }
    }
    return 0;
}
