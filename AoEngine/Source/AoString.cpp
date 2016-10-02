#include "AoString.h"
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
