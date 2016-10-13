#pragma once
#include "AoAsset.h"
#include "AoMesh.h"

class AoActor;
class AoMeshRenderComponent;
class AoModel : public AoAsset
{
	friend AoAssetFactory;
private:
	AoModel( std::vector<AoMesh*>&& Meshes );

public:
	~AoModel( );
	std::vector<AoMesh*> GetMeshes( ) const;

	template < typename Ty >
	static Ty* ModelToActor( AoModel* const Model, std::vector<AoMeshRenderComponent*>& CreatedComponent )
	{
		Ty* CreatedActor = nullptr;
		if ( Model != nullptr )
		{
			CreatedActor = new Ty( Model->GetFileName( ) );
			AoActor* MeshRootActor = new AoActor( TEXT( "MeshRoot" ) );
			CreatedActor->AttachChild( MeshRootActor );

			for ( AoMesh* Mesh : Model->GetMeshes( ) )
			{
				AoActor* MeshActor = new AoActor( Mesh->GetName( ) );
				AoMeshRenderComponent* RenderComponent = new AoMeshRenderComponent( );
				RenderComponent->SetMesh( Mesh );
				MeshActor->AttachComponent( RenderComponent );
				MeshRootActor->AttachChild( MeshActor );

				CreatedComponent.push_back( RenderComponent );
			}
		}

		return CreatedActor;
	}

private:
	std::vector<AoMesh*> Meshes;

};