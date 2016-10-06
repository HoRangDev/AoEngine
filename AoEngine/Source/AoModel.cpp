#include "AoModel.h"
#include "AoActor.h"
#include "AoMeshRenderComponent.h"
#include <iostream>

AoModel::AoModel( std::vector<AoMesh*>&& Meshes )
	: Meshes( Meshes )
{

}

AoModel::~AoModel( )
{
	for( AoMesh* MeshData : Meshes )
	{
		delete MeshData;
	}

	Meshes.clear( );
}

std::vector<AoMesh*> AoModel::GetMeshes( ) const
{
	return Meshes;
}

AoActor* AoModel::ModelToActor( AoModel* const Model, std::vector<AoMeshRenderComponent*>& CreatedComponent )
{
	AoActor* CreatedActor = nullptr;
	if ( Model != nullptr )
	{
		CreatedActor = new AoActor( Model->GetFileName( ) );
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
