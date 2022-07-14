#include "pch.h"
#include "App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try {
		winrt::init_apartment();

		App app = App::GetInstance();
		app.Run(hInstance);
	}
	catch (const WindowException& ex)
	{
		MessageBoxA(nullptr, std::format("Code: 0x{:x}\n{}\n{}\nThe program will now exit.", static_cast<uint32_t>(ex.GetErrorCode()), ex.what(), ex.GetLocationString()).c_str(), "Application Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, std::format("{}\nThe program will now exit.", ex.what()).c_str(), "Application Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "No details available.\nThe program will now exit.", "Unknown Error", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	return -1;
}