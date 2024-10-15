#include "dx11.h"


IDXGISwapChain* g_ptr_Swap_Chain{};
ID3D11Device* g_ptr_D3D_Device{};
ID3D11DeviceContext* g_ptr_D3D_DeviceContext{};
ID3D11RenderTargetView* g_ptr_MainRenderTargetView{};

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

    if(ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
    switch (msg) {


    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
 

bool Initdx11(HWND hwnd) {
    
    /*
    ������
    UINT      cbSize;   ���С  
    UINT      style;    ����ʽ
    WNDPROC   lpfnWndProc;  ָ�򴰿ڹ��̵�ָ��
    int       cbClsExtra;   Ҫ���ݴ�����ṹ����Ķ����ֽ����� ϵͳ���ֽڳ�ʼ��Ϊ��
    int       cbWndExtra;   �ڴ���ʵ��֮�����Ķ����ֽ����� ϵͳ���ֽڳ�ʼ��Ϊ�㡣
    HINSTANCE hInstance;    ʵ���ľ������ʵ��������Ĵ��ڹ���
    HICON     hIcon;    ��ͼ��ľ���� �˳�Ա������ͼ����Դ�ľ��
    HCURSOR   hCursor;  ���α�ľ���� �˳�Ա�������α���Դ�ľ��
    HBRUSH    hbrBackground;    �౳�����ʵľ�� 
    LPCWSTR   lpszMenuName;
    LPCWSTR   lpszClassName;
    HICON     hIconSm;
    
    */
    WNDCLASSEXW wc{};

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.hIcon = NULL;
    wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszMenuName = L" ";
    wc.lpszClassName = L" ";
    wc.hIconSm = NULL;

    if (RegisterClassExW(&wc) == 0) {

        std::cout << "Register error" << std::endl; 
       
        return false;


    }
    RECT rect{};
    if (GetWindowRect(hwnd, &rect) == 0) {
        std::cout <<"get window size error"<<std::endl;
        return false;
    }
    int width, height;
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    

    HWND wnd_hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_LAYERED, wc.lpszClassName, wc.lpszMenuName, WS_POPUP, 1,1, width, height, NULL, NULL, 0, 0);
    if (wnd_hwnd == NULL) return false;
    
    //��ʾ���ڣ����´���
    ShowWindow(wnd_hwnd, SW_SHOW);
    UpdateWindow(wnd_hwnd);

    SetLayeredWindowAttributes(wnd_hwnd,RGB(0,0,0),0,LWA_COLORKEY);

    //����WS_EX_TOOLWINDOW  ȥ��WS_EX_APPWINDOW
    LONG old_exstyle = GetWindowLongW(wnd_hwnd, GWL_EXSTYLE);

    SetWindowLongW(wnd_hwnd,GWL_EXSTYLE, old_exstyle & (~WS_EX_APPWINDOW) | WS_EX_TOOLWINDOW);
    
    
    //2.��ʼ��D3D�豸 
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = wnd_hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    D3D_FEATURE_LEVEL featureLevel{};
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_10_0 };

    //IDXGISwapChain   ID3D11Device  ID3D11DeviceContext
    //������ ǰ������ �󻺳��� 
    HRESULT ret = D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr,0, featureLevelArray,2,D3D11_SDK_VERSION,&sd,&g_ptr_Swap_Chain,&g_ptr_D3D_Device,&featureLevel,&g_ptr_D3D_DeviceContext);
    if (ret != S_OK) {
        std::cout<< "creat d3d device error" << std::endl;
        return false;
    }
    //����Ŀ����ͼ
    ID3D11Texture2D* pBackBuffer{};
    g_ptr_Swap_Chain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

    g_ptr_D3D_Device->CreateRenderTargetView(pBackBuffer, nullptr, &g_ptr_MainRenderTargetView);
   
    
    

    pBackBuffer->Release();
    

     //3.��ʼ��imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();

    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\simhei.ttf",16.0f,NULL,io.Fonts->GetGlyphRangesChineseFull());

    ImGui_ImplWin32_Init(wnd_hwnd);
    ImGui_ImplDX11_Init(g_ptr_D3D_Device, g_ptr_D3D_DeviceContext);
    
    return true;


}