// DlgEncodingDigital.cpp: 实现文件
//

#include "stdafx.h"
#include "DlgEncodingDigital.h"
#include "st_convert.h"

#define RADIO_INT       5
#define RADIO_FLOAT     7
#define RADIO_HEX       9

LRESULT CDlgEncodingDigital::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    CenterWindow(GetParent());

    SetDlgItemText(IDC_STATIC_ENCODING_DGT_TYPE, L"输入 - 整数");

    Button_SetCheck(GetDlgItem(IDC_RADIO_INT).m_hWnd, 1);
    m_defaultCheck = RADIO_INT;
    return TRUE;
}

LRESULT CDlgEncodingDigital::OnCloseCmd(WORD, WORD wID, HWND, BOOL &)
{
    EndDialog(wID);
    return 0;
}

#define BYTEX(val, index)   (((char*)&val)[index] & 0x0ff)

void CDlgEncodingDigital::PrintHexValue(LPCWSTR lpData)
{
    CString sValue;
    int iVal = 0;
    Hex2IntW(lpData, iVal);
    sValue.Format(L"%d", iVal);
    SetDlgItemText(IDC_EDIT_CODE_DGT_INT, sValue);

    float fVal = 0;
    Hex2FloatW(lpData, fVal);
    sValue.Format(L"%f", fVal);
    SetDlgItemText(IDC_EDIT_CODE_DGT_FLOAT, sValue);
    

    double dVal = 0;
    Hex2DoubleW(lpData, dVal);
    sValue.Format(L"%lf", dVal);
    SetDlgItemText(IDC_EDIT_CODE_DGT_DOUBLE, sValue);
}

LRESULT CDlgEncodingDigital::OnEnChangeEditCodeDigital(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogImpl::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码

    CString sValue;
    double inputVal = 0;

    CString inputString;
    GetDlgItemText(IDC_EDIT_CODE_DIGITAL, inputString);

    if (m_defaultCheck == RADIO_HEX)
    {
        PrintHexValue(inputString.GetString());
        return 0;
    }
    
    if (m_defaultCheck == RADIO_FLOAT)
    {
        swscanf(inputString.GetString(), L"%lf", &inputVal);
    }
    else
    {
        int iTmp = 0;
        swscanf(inputString.GetString(), L"%d", &iTmp);
        inputVal = iTmp;
    }


    int iVal = (int)inputVal;
    for (int i = 0; i < sizeof(DWORD); ++i)
    {
        if (i)
        {
            sValue.AppendChar(L' ');
        }

        sValue.AppendFormat(L"%02X", BYTEX(iVal, i));
    }
    SetDlgItemText(IDC_EDIT_CODE_DGT_INT, sValue);
    sValue.Empty();

    float fVal = (float)inputVal;
    for (int i = 0; i < sizeof(float); ++i)
    {
        if (i)
        {
            sValue.AppendChar(L' ');
        }

        sValue.AppendFormat(L"%02X", BYTEX(fVal, i));
    }
    SetDlgItemText(IDC_EDIT_CODE_DGT_FLOAT, sValue);
    sValue.Empty();

    double dVal = inputVal;
    for (int i = 0; i < sizeof(double); ++i)
    {
        if (i)
        {
            sValue.AppendChar(L' ');
        }

        sValue.AppendFormat(L"%02X", BYTEX(dVal, i));
    }
    SetDlgItemText(IDC_EDIT_CODE_DGT_DOUBLE, sValue);

    return 0;
}


LRESULT CDlgEncodingDigital::OnBnClickedRadioInt(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SetDlgItemText(IDC_STATIC_ENCODING_DGT_TYPE, L"输入 - 整数");

    m_defaultCheck = RADIO_INT;

    BOOL bRet;
    OnEnChangeEditCodeDigital(0, 0, 0, bRet);
    return 0;
}

LRESULT CDlgEncodingDigital::OnBnClickedRadioFloat(WORD, WORD, HWND, BOOL &)
{
    SetDlgItemText(IDC_STATIC_ENCODING_DGT_TYPE, L"输入 - 浮点数");

    m_defaultCheck = RADIO_FLOAT;

    BOOL bRet;
    OnEnChangeEditCodeDigital(0, 0, 0, bRet);
    return 0;
}


LRESULT CDlgEncodingDigital::OnBnClickedRadioHex(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: 在此添加控件通知处理程序代码
    SetDlgItemText(IDC_STATIC_ENCODING_DGT_TYPE, L"输入 - Hex");

    m_defaultCheck = RADIO_HEX;

    BOOL bRet;
    OnEnChangeEditCodeDigital(0, 0, 0, bRet);
    return 0;
}
