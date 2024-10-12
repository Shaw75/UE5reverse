#pragma once
#include <iostream>
#include "ImGui/imgui.h"
#include "ImGui/imconfig.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imstb_rectpack.h"
#include "ImGui/imstb_textedit.h"
#include "ImGui/imstb_truetype.h"




#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

extern IDXGISwapChain* g_ptr_Swap_Chain;
extern ID3D11Device* g_ptr_D3D_Device;
extern ID3D11DeviceContext* g_ptr_D3D_DeviceContext;
extern ID3D11RenderTargetView* g_ptr_MainRenderTargetView;
bool Initdx11(HWND hwnd);
