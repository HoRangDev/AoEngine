#pragma once
#include "AoAsset.h"
#include "AoMesh.h"

class AoModel : public AoAsset
{
	friend AoAssetFactory;
private:
	AoModel( std::vector<AoMesh*>&& Meshes );

public:
	~AoModel( );

private:
	std::vector<AoMesh*> Meshes;

};