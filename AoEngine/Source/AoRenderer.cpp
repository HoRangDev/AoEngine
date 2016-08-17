#include "AoRenderer.h"
#include "AoRenderComponent.h"

AoRenderer::AoRenderer( AoWindow& Window ) :
	Window( Window )
{

}

AoRenderer::~AoRenderer()
{
	Components.clear();
}

void AoRenderer::Render()
{
	for( auto* Component : Components )
	{
		if( Component->IsVisible() )
		{
			Component->Render();
		}
	}
}

void AoRenderer::RegisterComponent( AoRenderComponent* RenderComponent )
{
	if( !RenderComponent->IsRegistered() )
	{
		Components.push_back( RenderComponent );
	}
}

void AoRenderer::UnRegisterComponent( AoRenderComponent* RenderComponent )
{
	if( RenderComponent->IsRegistered() )
	{
		for( auto Itr = Components.begin(); Itr != Components.end(); ++Itr )
		{
			if( *Itr == RenderComponent )
			{
				Components.erase( Itr );
				break;
			}
		}
	}
}