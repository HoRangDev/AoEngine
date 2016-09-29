#include "AoLevel.h"
#include "AoActor.h"

AoLevel::AoLevel( )
{

}

AoLevel::~AoLevel( )
{
	// 등록되어있는 모든 액터를 삭제해야함
	UnRegisterAllActor( true );
}

void AoLevel::RegisterActor( AoActor* const Actor )
{
	bool bIsRegisteredActor = Actor->GetRegisteredLevel( ) != nullptr;
	if ( !bIsRegisteredActor )
	{
		Actor->SetRegisteredLevel( this );
		RegisteredActors.push_back( Actor );
	}
}

void AoLevel::UnRegisterActor( AoActor* const Actor )
{
	bool bIsRegisteredActor = Actor->GetRegisteredLevel( ) == this;
	if ( bIsRegisteredActor )
	{
		for ( auto Itr = RegisteredActors.begin( ); Itr != RegisteredActors.end( ); ++Itr )
		{
			if ( *Itr == Actor )
			{
				( *Itr )->SetRegisteredLevel( nullptr );
				RegisteredActors.erase( Itr );
				break;
			}
		}
	}
}

AoActor* AoLevel::UnRegisterActor( const string& Name )
{
	for ( auto Itr = RegisteredActors.begin( ); Itr != RegisteredActors.end( ); ++Itr )
	{
		bool bIsTargetActor = ( ( *Itr )->GetName( ) ).compare( Name ) == 0;
		if ( bIsTargetActor )
		{
			( *Itr )->SetRegisteredLevel( nullptr );
			RegisteredActors.erase( Itr );
			return *Itr;
		}
	}

	return nullptr;
}

void AoLevel::UnRegisterAllActor( bool bIsCleanup = true )
{
	if ( bIsCleanup )
	{
		for ( auto* Actor : RegisteredActors )
		{
			delete Actor;
		}
	}

	RegisteredActors.clear( );
}

void AoLevel::Update( float DeltaTime )
{
	for ( auto* Actor : RegisteredActors )
	{
		Actor->Update( DeltaTime );
	}
}