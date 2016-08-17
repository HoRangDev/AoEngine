#include "AoRenderComponent.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoActor.h"

AoRenderComponent::AoRenderComponent() :
	Renderer(AoApplication::GetRenderer()),
	AoComponent()
{
	SetActive( true );
}

AoRenderComponent::~AoRenderComponent()
{
	SetActive( false );
}

void AoRenderComponent::SetMaterial( AoMaterial * Material )
{
	this->Material = Material;
}

AoMaterial* AoRenderComponent::GetMaterial() const
{
	return Material;
}

void AoRenderComponent::SetActive( bool bIsActive )
{
	AoComponent::SetActive( bIsActive );
	if( bIsActive && !bIsRegistered )
	{
		Renderer->RegisterComponent( this );
		bIsRegistered = true;
	}
	else if( !bIsActive && bIsRegistered )
	{
		Renderer->UnRegisterComponent( this );
		bIsRegistered = false;
	}
}

bool AoRenderComponent::IsVisible() const
{
	if( Actor != nullptr )
	{
		return bIsVisible && IsActive() && Actor->IsActive();
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

bool AoRenderComponent::IsRegistered() const
{
	return bIsRegistered;
}
