#pragma once
#include "AoLevel.h"
#include <vector>

class AoModel;
class AoActor;
class AoMeshRenderComponent;
class AoTestLevel : public AoLevel
{
public:
	AoTestLevel( );
	~AoTestLevel( );

	void Initialize( );

private:
	AoActor* Camera;
	AoModel* Model;
	AoActor* UnityChan;
	std::vector< AoMeshRenderComponent* > UnityChanRenderComponent;

};