#include "AoActor.h"
#include "AoComponent.h"
#include <Windows.h>

std::atomic<uint64_t> AoActor::InstanceCount = 0;

AoActor::AoActor( string Name ) :
	Name( Name )
{
	++InstanceCount;
	/*@TODO: 트랜스폼 생성하도록 하기 */
}

AoActor::AoActor( ) :
	AoActor( TEXT( "Actor" ) + std::to_wstring( InstanceCount ) )
{
}

AoActor::~AoActor( )
{
	--InstanceCount;
	DetachAllChild( true );
	DetachAllComponent( true );
}

void AoActor::AttachChild( AoActor* const Child )
{
	bool IsAttachedChild = Child->GetParent( ) != nullptr;
	if ( !IsAttachedChild )
	{
		Child->SetParent( this );
		Children.push_back( Child );
	}
}

void AoActor::DetachChild( AoActor* const Child )
{
	bool IsAttachedChild = Child->GetParent( ) == this;
	if ( IsAttachedChild )
	{
		for ( ActorVectorItr Itr = Children.begin( ); Itr != Children.end( ); ++Itr )
		{
			if ( *Itr == Child )
			{
				( *Itr )->SetParent( nullptr );
				Children.erase( Itr );
				break;
			}
		}
	}
}

AoActor* AoActor::DetachChild( const string & Name )
{
	for ( ActorVectorItr Itr = Children.begin( ); Itr != Children.end( ); ++Itr )
	{
		bool bIsTargetActor = ( ( *Itr )->GetName( ) ).compare( Name ) == 0;
		if ( bIsTargetActor )
		{
			( *Itr )->SetParent( nullptr );
			Children.erase( Itr );
			return *Itr;
		}
	}

	return nullptr;
}

void AoActor::DetachAllChild( bool bIsCleanup )
{
	if ( bIsCleanup )
	{
		for ( auto* Child : Children )
		{
			delete Child;
		}
	}
	else
	{
		for ( auto* Child : Children )
		{
			Child->SetParent( nullptr );
		}
	}

	Children.clear( );
}

void AoActor::AttachComponent( AoComponent* const Component )
{
	bool IsAttachedComponent = Component->GetAttachedActor( ) != nullptr;
	if ( !IsAttachedComponent )
	{
		Component->SetAttachedActor( this );
		Components.push_back( Component );
	}
}

void AoActor::DetachComponent( AoComponent* const Component )
{
	bool IsAttachedComponent = Component->GetAttachedActor( ) == this;
	if ( IsAttachedComponent )
	{
		for ( auto Itr = Components.begin( ); Itr != Components.end( ); ++Itr )
		{
			if ( *Itr == Component )
			{
				( *Itr )->SetAttachedActor( nullptr );
				Components.erase( Itr );
				break;
			}
		}
	}
}

void AoActor::DetachAllComponent( bool bIsCleanup )
{
	if ( bIsCleanup )
	{
		for ( auto* Component : Components )
		{
			delete Component;
		}
	}

	Components.clear( );
}

uint64_t AoActor::GetInstanceCount( )
{
	return InstanceCount;
}

string AoActor::GetName( ) const
{
	return Name;
}

AoActor * AoActor::GetParent( ) const
{
	return Parent;
}

AoLevel * AoActor::GetRegisteredLevel( ) const
{
	return RegisteredLevel;
}

void AoActor::SetActive( bool bIsActive )
{
	this->bIsActive = bIsActive;
}

bool AoActor::IsActive( ) const
{
	return bIsActive;
}

bool AoActor::IsRegisteredAtLevel( ) const
{
	return ( RegisteredLevel != nullptr );
}

AoTransform * AoActor::GetTransform( ) const
{
	return Transform;
}

void AoActor::Update( float DeltaTime )
{
	if ( bIsActive )
	{
		if ( bIsTick )
		{
			Tick( DeltaTime );
		}

		for ( auto Child : Children )
		{
			Child->Update( DeltaTime );
		}
	}
}

void AoActor::SetParent( AoActor* const Parent )
{
	this->Parent = Parent;
}

void AoActor::SetRegisteredLevel( AoLevel* const TargetLevel )
{
	this->RegisteredLevel = TargetLevel;
}
