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