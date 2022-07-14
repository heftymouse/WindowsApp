#pragma once

#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.ViewManagement.h>

namespace view = winrt::Windows::UI::ViewManagement;

class Window
{
public:
	Window(HINSTANCE hInstance, const std::string title, int width, int height);
	Window(HINSTANCE hInstance, const std::string title) : Window::Window(hInstance, title, CW_USEDEFAULT, CW_USEDEFAULT) {}; // delegating constructor very cool
	~Window();
	static LRESULT CALLBACK WndProcShim(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND hWnd;
private:
	static int windows;
	view::UISettings settings;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SetColorMode(view::UISettings settings);
};

