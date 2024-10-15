#pragma once
#include <Windows.h>
#include <winternl.h>
#include <iostream>



class Memory
{ 
	public:
		static bool init();
		template<typename T>
		static T Read(ULONG64 adr) {
			T buf{};
			SIZE_T size;
			ReadProcessMemory(m_Process, (PVOID)adr, &buf,sizeof(buf), &size);
			return buf;

		}

		template<typename T>
		static void Write(ULONG64 adr, T buf) {
			size_t size;
			WriteProcessMemory(m_Process, (PVOID)adr, buf, sizeof(T), &size);


		}
		static ULONG64 GetModleBaseAdr();
	private:
		static HANDLE m_Process;
		static DWORD m_Pid;

};