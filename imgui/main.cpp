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

	
	
	

	//[7FF7FF497D90 + 17 * 8] + 19506 + 2  7FF7FF497D90为GName第一个数组


	

	if (Memory::init() == false) {

		printf("[-]游戏未打开");

	}
	g_Game_Module = Memory::GetModleBaseAdr();

	if (Engine::Init() == NULL) {
		printf("[-] 初始化失败");
	}

	std::string str= Engine::GetName(0x01A516CC);
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