#include "pch.h"

#include "WindowException.h"

WindowException::WindowException(HRESULT errorCode, std::string message, std::source_location location) noexcept
{
	WindowException::errorCode = errorCode;
	WindowException::message = message;
	WindowException::location = location;
}

const char* WindowException::what() const noexcept
{
	return message.c_str();
}

HRESULT WindowException::GetErrorCode() const noexcept
{
	return errorCode;
}

std::string WindowException::GetLocationString() const noexcept
{
	return std::format("At {}, {}:{}\n", WindowException::GetFileName(location.file_name()), WindowException::location.line(), WindowException::location.column());
}

// i tried way too much to get files in nested folders to work properly with this
// so i gave up i'll just have to remember to use descriptive file names

std::string WindowException::GetFileName(std::string path) const noexcept
{
	return path.substr(path.find_last_of("\\", path.length()) + 1, path.length());
}