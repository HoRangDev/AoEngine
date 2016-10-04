#include "AoString.h"
#include <algorithm>
#include <locale>
#include <codecvt>

std::string AoString::WStringToString( const std::wstring& Target )
{
	return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>( ).to_bytes( Target );
}

std::wstring AoString::StringToWString( const std::string& Target )
{
	return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>( ).from_bytes( Target );
}

std::string AoString::StringToLower( const std::string& Target )
{
	std::string Result = Target;
	std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::tolower );
	return Result;
}

std::wstring AoString::WStringToLower( const std::wstring& Target )
{
	std::wstring Result = Target;
	std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::towlower );
	return Result;
}

std::string AoString::StringToUpper( const std::string& Target )
{
	std::string Result = Target;
	std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::toupper );
	return Result;
}

std::wstring AoString::WStringToUpper( const std::wstring& Target )
{
	std::wstring Result = Target;
	std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::towupper );
	return Result;
}


