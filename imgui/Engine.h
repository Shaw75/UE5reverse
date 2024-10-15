#pragma once
#include <Windows.h>
#include <iostream>
#include <String>

class Engine {
public:
	Engine () = default;
	~Engine() = default;
	static bool Init();
	static std::string GetName(int Index);
	static ULONG64 GetGnameAdr() { return m_Gname; };
private:
	static ULONG64 m_Gname;
	static ULONG64 m_Gworld;


};