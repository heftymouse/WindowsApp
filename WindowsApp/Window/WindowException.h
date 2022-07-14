#pragma once

class WindowException : public std::exception
{
private:
	HRESULT errorCode;
	std::string message;
	std::source_location location;
	std::string GetFileName(std::string path) const noexcept;
public:
	WindowException(HRESULT errorCode, std::string message, std::source_location location) noexcept;
	WindowException(HRESULT hr, std::source_location location) noexcept : WindowException(hr, std::system_category().message(hr), location) {};
	const char* what() const noexcept override;
	HRESULT GetErrorCode() const noexcept;
	std::string GetLocationString() const noexcept;
};

