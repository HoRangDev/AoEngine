#include "AoProfiler.h"

AoProfiler* AoProfiler::Instance = nullptr;

AoProfiler::AoProfiler( )
{
}

AoProfiler& AoProfiler::GetInstance( )
{
	if( Instance == nullptr )
	{
		Instance = new AoProfiler( );
	}

	return *Instance;
}

void AoProfiler::Initialize( )
{
	Samples.InitHashTable( 15 );
}

void AoProfiler::DeInitialize( )
{
	Samples.RemoveAll( );
}

void AoProfiler::ForceDeallocate( )
{
	if( Instance != nullptr )
	{
		delete Instance;
		Instance = nullptr;
	}
}

void AoProfiler::RegisterSample( const string& SampleName, const AoProfileSample& Sample )
{
	SampleMap::CPair* FoundPair = Samples.Lookup( SampleName.c_str() );
	if ( FoundPair != nullptr )
	{
		auto AddSample = ( FoundPair->m_value + Sample );
		Samples.SetAt( SampleName.c_str( ), ( FoundPair->m_value + Sample ) );
	}
	else
	{
		Samples.SetAt( SampleName.c_str( ), Sample );
	}
}

AoProfileSample AoProfiler::FoundSample( const string& SampleName ) const
{
	const SampleMap::CPair* FoundPair = Samples.Lookup( SampleName.c_str( ) );
	if ( FoundPair != nullptr )
	{
		return FoundPair->m_value;
	}

	return AoProfileSample( );
}
