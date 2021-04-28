#include "stdafx.h"
#include "DlgHash.h"

#define HASH_INOUT_NORMAL       1
#define HASH_INOUT_LOWWER       2
#define HASH_INOUT_UPPER        4
#define HASH_SEL_CHANGE         0x10000000

LRESULT CDlgHash::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
    CenterWindow(GetParent());

    m_defaultCheck = HASH_INOUT_NORMAL;
    Button_SetCheck(GetDlgItem(IDC_RADIO_HASH_NORMAL).m_hWnd, 1);

    return TRUE;
}

LRESULT CDlgHash::OnCloseCmd(WORD, WORD wID, HWND, BOOL &)
{
    EndDialog(wID);
    return 0;
}


LRESULT CDlgHash::OnBnClickedBtnDlgHashBkdr(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������

    CString szHashString;
    GetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, szHashString);
    DWORD seed = GetDlgItemInt(IDC_EDIT_DLG_HASH_EXTRA);

    DWORD hash = 0;
    for (int i = 0; i < szHashString.GetLength(); i++)
    {
        hash = hash * seed + (DWORD)szHashString.GetAt(i);
    }

    szHashString.Format(L"%08x", hash);

    SetDlgItemText(IDC_EDIT_DLG_HASH_OUTPUT, szHashString);

    return 0;
}


LRESULT CDlgHash::OnBnClickedRadioHashNormal(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_defaultCheck = HASH_SEL_CHANGE | HASH_INOUT_NORMAL;

    BOOL bRet = TRUE;
    OnEnChangeEditDlgHashInput(0, 0, 0, bRet);
    return 0;
}


LRESULT CDlgHash::OnBnClickedRadioHashLow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_defaultCheck = HASH_SEL_CHANGE | HASH_INOUT_LOWWER;

    BOOL bRet = TRUE;
    OnEnChangeEditDlgHashInput(0, 0, 0, bRet);
    return 0;
}


LRESULT CDlgHash::OnBnClickedRadioHashUpper(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_defaultCheck = HASH_SEL_CHANGE | HASH_INOUT_UPPER;

    BOOL bRet = TRUE;
    OnEnChangeEditDlgHashInput(0, 0, 0, bRet);
    return 0;
}


LRESULT CDlgHash::OnEnChangeEditDlgHashInput(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
    // ���ʹ�֪ͨ��������д CDialogImpl::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    if (m_defaultCheck & HASH_INOUT_LOWWER)
    {
        CString szData;
        GetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, szData);
        szData.MakeLower();


        SetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, szData);

        SendMessage(GetDlgItem(IDC_EDIT_DLG_HASH_INPUT).m_hWnd, EM_SETSEL, szData.GetLength(), szData.GetLength());
    }
    else if (m_defaultCheck & HASH_INOUT_UPPER)
    {
        CString szData;
        GetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, szData);
        szData.MakeUpper();

        SetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, szData);
        SendMessage(GetDlgItem(IDC_EDIT_DLG_HASH_INPUT).m_hWnd, EM_SETSEL, szData.GetLength(), szData.GetLength());
    }
    else
    {
        /*
        ���ת����Сд�󣬼������룬��bugδ������ʱ����
        if (m_defaultCheck & HASH_SEL_CHANGE)
        {
            SetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, m_szInputMormal);
            m_defaultCheck &= ~HASH_SEL_CHANGE;
        }
        else
        {
            GetDlgItemText(IDC_EDIT_DLG_HASH_INPUT, m_szInputMormal);
        }
        */
    }

    return 0;
}
