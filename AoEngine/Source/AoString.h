#pragma once
#include <string>

class AoString
{
public:
	static std::string WStringToString( const std::wstring& Target );
	static std::wstring StringToWString( const std::string& Target );

};
