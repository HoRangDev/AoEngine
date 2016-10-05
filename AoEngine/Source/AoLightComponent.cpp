#include "AoLightComponent.h"

AoLightComponent::AoLightComponent( AoLight LightData )
	: LightData( LightData )
{
}

AoLightComponent::~AoLightComponent( )
{
}

AoLight AoLightComponent::GetLightData( ) const
{
	return LightData;
}

void AoLightComponent::SetLightData( AoLight LightData )
{
	this->LightData = LightData;
}
