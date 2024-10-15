
#include "Memory.h"
HANDLE Memory::m_Process = NULL;
DWORD  Memory::m_Pid = 0;
bool Memory::init()
{   
    HWND hwnd = FindWindowW(L"UnrealWindow",NULL);
    GetWindowThreadProcessId(hwnd,&m_Pid);
    m_Process = OpenProcess(PROCESS_ALL_ACCESS, false, m_Pid);

    return m_Pid && m_Process;
}

ULONG64 Memory::GetModleBaseAdr()
{   

    PROCESS_BASIC_INFORMATION info{};
    ULONG len{}; 

    
    if (NtQueryInformationProcess(m_Process, ProcessBasicInformation, &info, sizeof(PROCESS_BASIC_INFORMATION), &len) < 0) {
        return 0;
    }
   
    return  Read<ULONG64>((ULONG64)(((char*)info.PebBaseAddress) + 0x10));
}  
