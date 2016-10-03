#include "AoModel.h"

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