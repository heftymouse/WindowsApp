#include "pch.h"

#include "WindowClass.h"
#include "WindowException.h"
#include <hidusage.h>
#include <winrt/Windows.System.h>

#include "Window.h"

int Window::windows;

Window::Window(HINSTANCE hInstance, const std::string title, int width, int height)
{
	WindowClass::Register(hInstance);

	RECT rect = { 0, 0, width, height };
	if (width != CW_USEDEFAULT && height != CW_USEDEFAULT)
	{
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	}

	hWnd = CreateWindowExA(
		WS_EX_COMPOSITED,   // important to remove white line around client area
		WindowClass::GetName().c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr,
		nullptr,
		hInstance,
		this
	);

	if (hWnd == NULL)
	{
		WND_EXCEPT();
	}
;
	Window::windows++;

	settings = view::UISettings();
	SetColorMode(settings);
	auto revoker = settings.ColorValuesChanged([this](view::UISettings settings, Windows::Foundation::IInspectable const& sender)
		{
			SetColorMode(settings);
		});
	BOOL yes = TRUE;
	DwmSetWindowAttribute(hWnd, DWMWA_USE_HOSTBACKDROPBRUSH, &yes, sizeof(yes));
	DWM_SYSTEMBACKDROP_TYPE type = DWMSBT_MAINWINDOW;
	MARGINS mar = { -1 };
	DwmExtendFrameIntoClientArea(hWnd, &mar);
	DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &type, sizeof(type));

	ShowWindow(hWnd, SW_SHOW);

	RAWINPUTDEVICE rid[2];
	rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
	rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[0].hwndTarget = hWnd;
	rid[0].dwFlags = RIDEV_INPUTSINK;

	rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
	rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
	rid[1].hwndTarget = hWnd;
	rid[1].dwFlags = RIDEV_NOLEGACY;

	if (RegisterRawInputDevices(rid, 2, sizeof(rid[0])) == FALSE)
	{
		WND_EXCEPT();
	}
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::WndProcShim(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* wndPtr = nullptr;

	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCTA* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* csPtr = reinterpret_cast<Window*>(createStruct->lpCreateParams);
		SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(csPtr));
		wndPtr = csPtr;
	}
	else
	{
		wndPtr = reinterpret_cast<Window*>(GetWindowLongPtrA(hWnd, GWLP_USERDATA));
	}

	if (wndPtr)
	{
		return wndPtr->WndProc(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProcA(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CLOSE:
	{
		Window::windows--;
		if (Window::windows <= 0)
		{
			PostQuitMessage(0);
		}
		break;
	}

	case WM_INPUT:
	{
		UINT size = sizeof(RAWINPUT);
		static BYTE lpb[sizeof(RAWINPUT)];

		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &size, sizeof(RAWINPUTHEADER));

		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(lpb);
		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			SetWindowTextA(hWnd, std::format("{}", raw->data.keyboard.VKey).c_str());
		}
		else if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			SetWindowTextA(hWnd, std::format("{} {}", raw->data.mouse.lLastX, raw->data.mouse.lLastY).c_str());
		}
		break;
	}

	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc;
	//	RECT rect;
	//	GetClientRect(hWnd, &rect);
	//	std::stringstream text;
	//	text << rect.right << " " << rect.bottom;

	//	hdc = BeginPaint(hWnd, &ps);
	//	SetTextAlign(hdc, TA_CENTER);
	//	TextOutA(hdc, rect.right / 2, rect.bottom / 2, text.str().c_str(), static_cast<int>(text.str().length()));
	//	EndPaint(hWnd, &ps);

	//	break;
	//}
	}

	return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

void Window::SetColorMode(view::UISettings settings)
{
	auto foreground = settings.GetColorValue(view::UIColorType::Foreground);
	BOOL dark = (((5 * foreground.G) + (2 * foreground.R) + foreground.B) > (8 * 128));
	DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof(dark));
}


