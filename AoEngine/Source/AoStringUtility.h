#pragma once
#include "AoType.h"

namespace AoStringUtility
{
	stdstring WStringToString( const string& Target );
	string StringToWString( const stdstring& Target );
	stdstring StringToLower( const stdstring& Target );
	string WStringToLower( const string& Target );
	stdstring StringToUpper( const stdstring& Target );
	string WStringToUpper( const string& Target );
}