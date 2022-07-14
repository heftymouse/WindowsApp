#pragma once

class WindowClass
{
public:
	~WindowClass();
	static void Register(HINSTANCE hInstance);
	static std::string GetName();
private:
	WindowClass(const WindowClass&) = delete;
	WindowClass& operator=(const WindowClass&) = delete;
	static HINSTANCE hInstance;
	static constexpr std::string_view name = "Base Window Class Thingy";
	static bool isRegistered;
};

