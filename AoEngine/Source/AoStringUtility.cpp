#include "AoStringUtility.h"
#include <algorithm>
#include <locale>
#include <codecvt>

namespace AoStringUtility
{
	stdstring WStringToString( const string& Target )
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>( ).to_bytes( Target );
	}

	string StringToWString( const stdstring& Target )
	{
		return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>( ).from_bytes( Target.c_str( ) );
	}

	stdstring StringToLower( const stdstring& Target )
	{
		stdstring Result = Target;
		std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::tolower );
		return Result;
	}

	string WStringToLower( const string& Target )
	{
		string Result = Target;
		std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::towlower );
		return Result;
	}

	stdstring StringToUpper( const stdstring& Target )
	{
		stdstring Result = Target;
		std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::toupper );
		return Result;
	}

	string WStringToUpper( const string& Target )
	{
		string Result = Target;
		std::transform( Result.begin( ), Result.end( ), Result.begin( ), ::towupper );
		return Result;
	}
}


