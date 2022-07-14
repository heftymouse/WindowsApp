#pragma once

#include <dxgi1_6.h>
#include <d3d11.h>

class Renderer
{
private:
	winrt::com_ptr<IDXGISwapChain> swapChain;
	winrt::com_ptr<ID3D11Device> device;
	winrt::com_ptr<ID3D11DeviceContext> deviceContext;

	winrt::com_ptr<IDXGIAdapter1> GetAdapter();
public:
	Renderer(HWND hWnd);
};

