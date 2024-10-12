#include <windows.h>
#include <iostream>
#include "dx11.h"
#include "memory.h"

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


	bool init = Memory::init();
	printf("%d\n", init);
	ULONG64 moduleBase = Memory::GetModleBaseAdr();

	printf("%llx", moduleBase);

	Initdx11((HWND)0x00010436);
	
	
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