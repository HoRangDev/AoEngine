#include "AoLightComponent.h"

AoLightComponent::AoLightComponent( AoLight LightData )
	: bIsDirty( true ), LightData( LightData )
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
	this->bIsDirty = true;
}

bool AoLightComponent::IsDirty( ) const
{
	return bIsDirty;
}

void AoLightComponent::SetDirty( bool bIsDirty )
{
	this->bIsDirty = bIsDirty;
}
