#include "AoRenderComponent.h"
#include "AoApplication.h"
#include "AoRenderer.h"
#include "AoActor.h"

AoRenderComponent::AoRenderComponent( ) :
	Renderer( AoApplication::GetRenderer( ) )
{
	Renderer.RegisterComponent( this );
	//@TODO: Load Basic Material
}

AoRenderComponent::~AoRenderComponent( )
{
	SetActive( false );
	Renderer.UnRegisterComponent( this );
}

void AoRenderComponent::SetMaterial( AoMaterial* Material )
{
	this->Material = Material;
	ActiveTechnique = Material->GetTechniqueByIndex( 0 );
}

AoMaterial* AoRenderComponent::GetMaterial( ) const
{
	return Material;
}

void AoRenderComponent::SetActiveTechnique( const string& TechniqueName )
{
	ActiveTechnique = Material->GetTechniqueByName( TechniqueName );
}

bool AoRenderComponent::IsVisible( ) const
{
	if ( Actor != nullptr )
	{
		return bIsVisible && IsActive( ) && Actor->IsActive( ) && ActiveTechnique != nullptr;
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
