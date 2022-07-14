#include "pch.h"

#include "Renderer.h"

winrt::com_ptr<IDXGIAdapter1> Renderer::GetAdapter()
{
    winrt::com_ptr<IDXGIAdapter1> adapter;
    winrt::com_ptr<IDXGIFactory6> factory;
    CreateDXGIFactory1(__uuidof(IDXGIFactory6), factory.put_void());
    HRESULT hr = factory.get()->EnumAdapterByGpuPreference(
        0,
        DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
        __uuidof(IDXGIAdapter1),
        adapter.put_void()
    );
    
    if (FAILED(hr))
    {
        WND_EXCEPT_HR(hr);
    }
    else
    {
        return adapter;
    }
}

Renderer::Renderer(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 640;
    sd.BufferDesc.Height = 480;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_1;
    auto adapter = GetAdapter();
    DXGI_ADAPTER_DESC desc;
    adapter.get()->GetDesc(&desc);
    MessageBoxW(hWnd, desc.Description, L"aaaaa", MB_OK | MB_ICONINFORMATION);
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        adapter.get(),
        D3D_DRIVER_TYPE_UNKNOWN,
        NULL,
        D3D11_CREATE_DEVICE_DEBUG,
        &featureLevels,
        1,
        D3D11_SDK_VERSION,
        &sd,
        swapChain.put(),
        device.put(),
        NULL,
        deviceContext.put()
    );

    if (FAILED(hr))
    {
        WND_EXCEPT_HR(hr);
    }

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = 640;
    vp.Height = 480;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);
}