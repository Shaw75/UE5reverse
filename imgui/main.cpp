#include <windows.h>
#include <iostream>
#include "dx11.h"
#include "memory.h"
#include "Global.hpp"
#include "Engine.h"

void TestDraw() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("hello world");

	ImGui::End();
	ImGui::Render();
	const float Clear_Color{};
	g_ptr_D3D_DeviceContext->OMSetRenderTargets(1, &g_ptr_MainRenderTargetView, nullptr);
	g_ptr_D3D_DeviceContext->ClearRenderTargetView(g_ptr_MainRenderTargetView,&Clear_Color);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_ptr_Swap_Chain->Present(0, 0);
} 





int main() {

     if (Memory::init() == false) {

		printf("[-]游戏未打开");

	}
	g_Game_Module = Memory::GetModleBaseAdr();

	if (Engine::Init() == NULL) {
		printf("[-] 初始化失败");
	}

	//GWorld -> UWorld -> PersistentLevel - >TArary<AActor> Actros.count
	

	do {
		ULONG64 UWorld = Memory::Read<ULONG64>(g_Game_Module+Offset::GWorld_off);
		ULONG64 PersistenLevel = Memory::Read<ULONG64>(UWorld + 0x30);
		TArary<AActor> Actors = Memory::Read<TArary<AActor>>(PersistenLevel + 0x98);

		
		printf("[+] %d,%d\n", Actors.count, Actors.maxcount);
		getchar();

	} while (true);   
	{}; 

	std::string str= Engine::GetName(0x00150A8E);
	std::cout << str.c_str()<<std::endl;
	
	Initdx11((HWND)0x00010458);
	while (true) {
		MSG msg{};

		while (::PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
			
		}
		TestDraw();
	}
	
	return 0;
}