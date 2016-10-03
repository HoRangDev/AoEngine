#include "AoRenderComponent.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoActor.h"

AoRenderComponent::AoRenderComponent( ) :
	Renderer( AoApplication::GetRenderer( ) ),
	AoComponent( )
{
	Renderer.RegisterComponent( this );
}

AoRenderComponent::~AoRenderComponent( )
{
	SetActive( false );
	Renderer.UnRegisterComponent( this );
}

void AoRenderComponent::SetMaterial( AoMaterial* Material )
{
	this->Material = Material;
}

AoMaterial* AoRenderComponent::GetMaterial( ) const
{
	return Material;
}

bool AoRenderComponent::IsVisible( ) const
{
	if ( Actor != nullptr )
	{
		return bIsVisible && IsActive( ) && Actor->IsActive( );
	}
	else
	{
		return false;
	}
}

void AoRenderComponent::SetIsVisible( bool bIsVisible )
{
	this->bIsVisible = bIsVisible;
}

bool AoRenderComponent::IsRegistered( ) const
{
	return bIsRegistered;
}
