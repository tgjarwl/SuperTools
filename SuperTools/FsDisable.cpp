#include "stdafx.h"
#include "FsDisable.h"
#include "PeOperation.h"

DWORD FsDisable::Call(PVOID func, int argC, ...)
{
    DWORD dwRet = 0;
    DWORD *pdwArgs = (DWORD *)malloc(argC * sizeof(DWORD));
    va_list args;
    va_start(args, argC);

    int index = 0;
    while (index < argC)
    {
        pdwArgs[index] = va_arg(args, DWORD);
        ++index;
    }
    va_end(args);

    PVOID oldValue = NULL;
    if (CPeOpr::Is64bitSystem())
    {
        if (Wow64DisableWow64FsRedirection(&oldValue) == FALSE)
        {
            MsgCtl::OutputResult(L"[FsDisable::Call] Wow64DisableWow64FsRedirection failed");
            return 0;
        }
    }
    
    {
        DWORD dwOldEsp;
        __asm
        {
            pushad;
            mov dwOldEsp, esp;
            mov ecx, argC;

        l_push_arg:
            test ecx, ecx;
            jz l_do_call;
            sub ecx, 1;
            mov eax, pdwArgs;
            lea eax, [eax + ecx * 4];
            push [eax];
            jmp l_push_arg;

        l_do_call:
            mov eax, func;
            call eax;
            mov dwRet, eax;

            mov esp,dwOldEsp
            popad;
        }

        
    }

    if (CPeOpr::Is64bitSystem())
    {
        Wow64RevertWow64FsRedirection(oldValue);
    }

    return dwRet;
}
