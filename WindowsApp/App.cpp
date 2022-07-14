#include "pch.h"

#include "App.h"

bool App::isInitialized = false;

int App::Run(HINSTANCE hInstance)
{
	if (isInitialized)
		throw std::exception("App already initialized!");

	hInstance = hInstance;

	MSG msg = { };

	while (true) // message loop
	{
		if (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		else
		{
			DoFrame();
		}
	}
	return msg.wParam;
}

void App::DoFrame()
{
	
}

