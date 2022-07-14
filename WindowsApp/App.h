#pragma once

#include "Window/Window.h"
#include "Renderer/Renderer.h"

class App
{
public:
	int Run(HINSTANCE hInstance);
	static App& GetInstance()
	{
		static App app;
		return app;
	}
private:
	App() : window(hInstance, "🅱️eans", 640, 480), renderer(window.hWnd) {};
	void DoFrame();
	static bool isInitialized;
	HINSTANCE hInstance;
	Window window;
	Renderer renderer;
};

