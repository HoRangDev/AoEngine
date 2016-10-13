#pragma once
#include "AoLevel.h"
#include <vector>

class AoModel;
class AoActor;
class AoTestActor;
class AoMeshRenderComponent;
class AoTexture2D;
class AoTestLevel : public AoLevel
{
public:
	AoTestLevel( );
	~AoTestLevel( );

	void Initialize( );

private:
	AoActor* Camera;
	AoModel* Model;
	AoTestActor* Sphere;
	std::vector< AoMeshRenderComponent* > RenderComponents;

	AoTexture2D* DiffuseMap;
	AoTexture2D* SpecularMap;
	AoTexture2D* NormalMap;

};