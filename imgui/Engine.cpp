#include "Engine.h" 
#include "Global.hpp"
#include "Memory.h"
ULONG64 Engine::m_Gname = 0;
ULONG64 Engine::m_Gworld = 0;
using uint32 = unsigned int;
static constexpr uint32 FNameMaxBlockBits = 13; // Limit block array a bit, still allowing 8k * block size = 1GB - 2G of FName entry data
static constexpr uint32 FNameBlockOffsetBits = 16;
static constexpr uint32 FNameMaxBlocks = 1 << FNameMaxBlockBits;
static constexpr uint32 FNameBlockOffsets = 1 << FNameBlockOffsetBits;
static constexpr uint32 FNameEntryIdBits = FNameBlockOffsetBits + FNameMaxBlockBits;
static constexpr uint32 FNameEntryIdMask = (1 << FNameEntryIdBits) - 1;
struct FNameEntryHeader
{
	short bIsWide : 1;
	static constexpr inline int ProbeHashBits = 5;
	short LowercaseProbeHash : ProbeHashBits;
	short Len : 10;
};


struct FNameEntry
{
public:
	FNameEntryHeader Header;
	union
	{
		char	AnsiName[1024];
		wchar_t	WideName[1024];
	};
};

struct FNameEntryHandle
{
	uint32 Block = 0;
	uint32 Offset = 0;

	

	FNameEntryHandle(uint32 Id)
		: Block(Id >> FNameBlockOffsetBits)
		, Offset(Id& (FNameBlockOffsets - 1))
	{
	}

	explicit operator bool() const { return Block | Offset; }
};


 bool Engine::Init() {

	 m_Gname = g_Game_Module + Offset::GName_off+0x10;

	 return m_Gname;
}
 enum { Stride = alignof(FNameEntry) }; 

 //[7FF7FF497D90 + 17 * 8] + 19506 + 2  7FF7FF497D90为GName第一个数组
 std::string Engine::GetName(int Index) {
	
	 
	 FNameEntryHandle EntryHandle(Index);
	 ULONG64 ptr1 = Memory::Read<ULONG64>((m_Gname + EntryHandle.Block * 8));
	 FNameEntry NameEntry = Memory::Read<FNameEntry>(ptr1+ (Stride *EntryHandle.Offset));

	 return std::string(NameEntry.AnsiName, NameEntry.Header.Len);


}