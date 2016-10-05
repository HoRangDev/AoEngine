#pragma once
#include "AoType.h"
#include "AoProfileSample.h"
#include <atlcoll.h>
#include <atlstr.h>

class AoProfiler
{
	using SampleMap = CAtlMap<CString, AoProfileSample>;
private:
	AoProfiler( );

public:
	static AoProfiler& GetInstance( );
	void Initialize( );
	void DeInitialize( );
	static void ForceDeallocate( );

	void RegisterSample( const string& SampleName, const AoProfileSample &Sample );
	AoProfileSample FoundSample( const string& SampleName ) const;

private:
	static AoProfiler* Instance;
	SampleMap Samples;

};