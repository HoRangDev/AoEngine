#pragma once
#include "AoAsset.h"
#include "AoMesh.h"

class AoModelAsset : public AoAsset
{
	friend AoAssetFactory;
private:
	AoModelAsset( std::vector<AoMesh*>&& Meshes );

public:
	~AoModelAsset( );

private:
	std::vector<AoMesh*> Meshes;

};