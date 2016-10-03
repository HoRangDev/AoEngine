#include "AoModelAsset.h"

AoModelAsset::AoModelAsset( std::vector<AoMesh*>&& Meshes )
	: Meshes( Meshes )
{

}

AoModelAsset::~AoModelAsset( )
{
	for( AoMesh* MeshData : Meshes )
	{
		delete MeshData;
	}

	Meshes.clear( );
}