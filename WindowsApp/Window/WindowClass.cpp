#include "pch.h"

#include "Window.h"
#include "WindowException.h"

#include "WindowClass.h"


bool WindowClass::isRegistered = false;
HINSTANCE WindowClass::hInstance;

void WindowClass::Register(HINSTANCE hInstance)
{
	WindowClass::hInstance = hInstance;
	if (WindowClass::isRegistered) return;

	WNDCLASSA wc = { };
	wc.hInstance = hInstance;
	wc.lpfnWndProc = Window::WndProcShim;
	wc.lpszClassName = WindowClass::name.data();
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

	RegisterClassA(&wc);
	
	WindowClass::isRegistered = true;
}

std::string WindowClass::GetName()
{
	return WindowClass::name.data();
}

WindowClass::~WindowClass()
{
	UnregisterClassA(WindowClass::GetName().c_str(), WindowClass::hInstance);
}