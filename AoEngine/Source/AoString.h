#pragma once
#include <string>

using string = std::wstring;

class AoString
{
public:
	static std::string WStringToString( const std::wstring& Target );
	static std::wstring StringToWString( const std::string& Target );
	static std::string StringToLower( const std::string& Target );
	static std::wstring WStringToLower( const std::wstring& Target );
	static std::string StringToUpper( const std::string& Target );
	static std::wstring WStringToUpper( const std::wstring& Target );

};
