#include "AoMeshRenderComponent.h"
#include "AoInputLayouts.h"
#include "AoRenderer.h"
#include "AoMesh.h"

AoMeshRenderComponent::AoMeshRenderComponent( )
	: InputLayout( AoInputLayouts::GetGenericVertexLayout( ) )
{
}

AoMeshRenderComponent::~AoMeshRenderComponent( )
{
}

void AoMeshRenderComponent::SetMesh( AoMesh* Mesh )
{
	this->Mesh = Mesh;
}

AoMesh* AoMeshRenderComponent::GetMesh( ) const
{
	return Mesh;
}

void AoMeshRenderComponent::Render( AoRenderer* Renderer )
{
	bool bIsValidToRendering =
		Renderer != nullptr && Mesh != nullptr
		&& InputLayout != nullptr && Material != nullptr;
	if ( bIsValidToRendering )
	{
		D3DX11_TECHNIQUE_DESC TechniqueDesc;
		ActiveTechnique->GetDesc( &TechniqueDesc );

		for ( uint32 Index = 0; Index < TechniqueDesc.Passes; ++Index )
		{
			Renderer->BindInputLayout( InputLayout );
			Renderer->SetPrimitiveTopology( EPrimitiveTopology::Triangle );
			Renderer->BindVertexBuffer(
				Mesh->GetVertexBuffer( ),
				Mesh->GetVertexSize( ) );
			Renderer->BindIndexBuffer( Mesh->GetIndexBuffer( ) );

			Material->ApplyPropertiesToShader( );

			Renderer->ApplyPass( ActiveTechnique->GetPassByIndex( Index ) );
			Renderer->DrawIndexed( Mesh->GetIndexCount( ) );
		}
	}
}
