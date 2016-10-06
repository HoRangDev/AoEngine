#include "AoRenderComponent.h"
#include "AoRenderer.h"
#include "AoActor.h"
#include "AoAssetManager.h"

AoRenderComponent::AoRenderComponent( ) :
	Renderer( AoRenderer::GetInstance() ), bIsRegistered( false )
{
	SetMaterial( dynamic_cast< AoMaterial* >( AoAssetManager::GetInstance( ).LoadAsset(
		TEXT( "Materials" ), TEXT( "Basic" ), TEXT( ".material" ) ) ) );
}

AoRenderComponent::~AoRenderComponent( )
{
	Renderer.UnRegisterComponent( this );
	SetActive( false );
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
		return bIsVisible && IsValid() && ActiveTechnique != nullptr;
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

void AoRenderComponent::OnAttach( )
{
	Renderer.RegisterComponent( this );
}

void AoRenderComponent::OnDetach( )
{
	Renderer.UnRegisterComponent( this );
}
