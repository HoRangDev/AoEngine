#pragma once
#include "AoRenderComponent.h"

class AoMesh;
class AoMeshRenderComponent : public AoRenderComponent
{
public:
	AoMeshRenderComponent( );
	~AoMeshRenderComponent( );

	void SetMesh( AoMesh* Mesh );
	AoMesh* GetMesh( ) const;

	virtual void Render( ) override;

private:
	AoMesh* Mesh;
	ID3D11InputLayout* InputLayout;

};