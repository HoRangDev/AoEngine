#include "AoMeshRenderComponent.h"
#include "AoInputLayouts.h"
#include "AoRenderer.h"
#include "AoMesh.h"
#include "AoActor.h"
#include "AoMatrix4x4.h"
#include "AoTransform.h"
#include "AoCameraComponent.h"
#include "AoLightManager.h"

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

void AoMeshRenderComponent::Render( )
{
	bool bIsValidToRendering = Mesh != nullptr
		&& InputLayout != nullptr && Material != nullptr;
	if ( bIsValidToRendering )
	{
		D3DX11_TECHNIQUE_DESC TechniqueDesc;
		ActiveTechnique->GetDesc( &TechniqueDesc );

		for ( uint32 Index = 0; Index < TechniqueDesc.Passes; ++Index )
		{
			Renderer.BindInputLayout( InputLayout );
			Renderer.SetPrimitiveTopology( EPrimitiveTopology::Triangle );
			Renderer.BindVertexBuffer(
				Mesh->GetVertexBuffer( ),
				Mesh->GetVertexSize( ) );
			Renderer.BindIndexBuffer( Mesh->GetIndexBuffer( ) );

			AoTransform* Transform = Actor->GetTransform( );

			bool TransformDirty = Transform->IsDirty( );
			if ( Transform->IsDirty( ) )
			{
				AoMatrix4x4 World = Transform->GetRelativeTransformationMatrix( );
				Material->SetMatrixByName( TEXT( "WorldMatrix" ), World );
				Transform->SetDirty( false );
			}

			Material->ApplyPropertiesToShader( );

			Renderer.ApplyPass( ActiveTechnique->GetPassByIndex( Index ) );
			Renderer.DrawIndexed( Mesh->GetIndexCount( ) );
		}
	}
}
