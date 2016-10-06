#include "AoComponent.h"
#include "AoActor.h"

AoComponent::AoComponent( ) :
	Actor( nullptr ), bIsActive( true )
{

}

AoComponent::~AoComponent( )
{
}

void AoComponent::SetActive( bool bIsActive )
{
	this->bIsActive = bIsActive;
}

bool AoComponent::IsActive( ) const
{
	return bIsActive;
}

bool AoComponent::IsParentActorRegistered( ) const
{
	if ( Actor != nullptr )
	{
		return Actor->IsRegisteredAtLevel( );
	}

	return false;
}

bool AoComponent::IsValid( ) const
{
	return IsActive( ) && IsParentActorRegistered( );
}

AoActor* AoComponent::GetAttachedActor( ) const
{
	return Actor;
}

void AoComponent::SetAttachedActor( AoActor* Actor )
{
	this->Actor = Actor;
	if( Actor != nullptr )
	{
		OnAttach( );
	}
	else
	{
		OnDetach( );
	}
}