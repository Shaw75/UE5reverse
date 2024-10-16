#pragma once
#include <Windows.h>
#include <iostream>
#include <String>
#include "Memory.h"

struct FName {
	int  index;
	int  number;

};

template <typename T>
struct TArary {
	T data;
	int count;
	int maxcount;


};

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

class AActor {
public:
	AActor() = default;
	AActor(unsigned long long adr) :objadr(adr) {


	}
	FName GetObjFName() {

		Memory::Read<FName>(objadr + 0x18);

	}

private:
	unsigned long long objadr;


};