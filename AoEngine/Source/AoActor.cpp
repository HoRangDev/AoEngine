#include "AoActor.h"
#include "AoTransform.h"
#include "AoRenderComponent.h"
#include <Windows.h>

atomic_uint64 AoActor::InstanceCount = 0;

AoActor::AoActor( string Name ) :
	Name( Name ), Parent( nullptr ), RegisteredLevel( nullptr ), Transform( nullptr ), RenderComponent( nullptr )
{
	++InstanceCount;
	Transform = new AoTransform( );
	AttachComponent( Transform );
}

AoActor::AoActor( ) :
	AoActor( TEXT( "Actor" ) + std::to_wstring( InstanceCount ) )
{
}

AoActor::~AoActor( )
{
	DetachAllComponent( true );
	DetachAllChild( true );

	delete Transform;
	Transform = nullptr;

	--InstanceCount;
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
		if ( this->RenderComponent == nullptr )
		{
			AoRenderComponent* RenderComponent = dynamic_cast< AoRenderComponent* > ( Component );
			if ( RenderComponent != nullptr )
			{
				this->RenderComponent = RenderComponent;
			}
		}

		Component->SetAttachedActor( this );
		Components.push_back( Component );
	}
}

void AoActor::DetachComponent( AoComponent* const Component )
{
	if( Component ==  RenderComponent )
	{
		RenderComponent = nullptr;
	}
	else
	{
		if ( Transform != Component )
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
	}
}

void AoActor::DetachAllComponent( bool bIsCleanup )
{
	for ( auto Itr = Components.begin( ); Itr != Components.end( ); )
	{
		if ( bIsCleanup )
		{
			if ( ( *Itr ) != Transform )
			{
				delete ( *Itr );
			}
		}

		Itr = Components.erase( Itr );
	}

	AttachComponent( Transform );
}

uint64 AoActor::GetInstanceCount( )
{
	return InstanceCount;
}

string AoActor::GetName( ) const
{
	return Name;
}

AoActor* AoActor::GetParent( ) const
{
	return Parent;
}

AoLevel* AoActor::GetRegisteredLevel( ) const
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

AoTransform* AoActor::GetTransform( ) const
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
	Transform->SetParent( Parent->GetTransform( ) );
}

void AoActor::SetRegisteredLevel( AoLevel* const TargetLevel )
{
	this->RegisteredLevel = TargetLevel;

	for( auto Child : Children )
	{
		Child->SetRegisteredLevel( TargetLevel );
	}
}