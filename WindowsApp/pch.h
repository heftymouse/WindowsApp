#pragma once

#undef UNICODE

// remove unnecessary win32 includes
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOMETAFILE
#define NOMINMAX
#define NOSCROLL
#define NOSERVICE
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

// stl headers
#include <string>
#include <sstream>
#include <string_view>
#include <memory>
#include <format>
#include <iostream>

#include <exception>
#include <source_location>
#include <system_error>
#include <optional>

// windows headers
#include <Windows.h>
#include <dwmapi.h>

//winrt
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>

// my headers
#include "Window/WindowException.h"

// global usings
using namespace winrt;

// macros
#define WND_EXCEPT_HR(x) throw WindowException::WindowException(x, std::source_location::current());
#define WND_EXCEPT() throw WindowException::WindowException(GetLastError(), std::source_location::current())


