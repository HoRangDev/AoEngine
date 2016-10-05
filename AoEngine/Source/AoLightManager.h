#pragma once
#include "AoType.h"
#include <array>

#define MAX_LIGHT_NUMBER 8

class AoLightComponent;
class AoMaterial;
class AoLightManager
{
private:
	AoLightManager( );

public:
	~AoLightManager( );

	static AoLightManager& GetInstance( );
	void Initialize( );
	void DeInitialize( );

	static void ForceDeallocate( );

	AoLightComponent* RegisterLight( AoLightComponent* const LightComponent, uint32 LightIndex );
	AoLightComponent* UnRegisterLight( uint32 Index );
	void UnRegisterLight( AoLightComponent* const LightComponent );

	void BindLights( AoMaterial* Material );

private:
	static AoLightManager* Instance;
	std::array<AoLightComponent*, MAX_LIGHT_NUMBER> Lights;

};