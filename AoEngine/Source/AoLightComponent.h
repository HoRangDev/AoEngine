#pragma once
#include "AoComponent.h"
#include "AoLight.h"

class AoLightComponent : public AoComponent
{
public:
	AoLightComponent( AoLight LightData );
	~AoLightComponent( );

	AoLight GetLightData( ) const;
	void SetLightData( AoLight LightData );

private:
	AoLight LightData;

};