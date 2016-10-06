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

	static AoActor* ModelToActor( AoModel* const Model, std::vector<AoMeshRenderComponent*>& CreatedComponent );

private:
	std::vector<AoMesh*> Meshes;

};