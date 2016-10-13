#include "AoLightManager.h"
#include "AoLight.h"
#include "AoLightComponent.h"
#include "AoMaterial.h"
#include <assert.h>

AoLightManager* AoLightManager::Instance = nullptr;

AoLightManager::AoLightManager( )
{
	/* Nothing in here */
}

AoLightManager::~AoLightManager( )
{
	/* Nothing in here */
}

AoLightManager& AoLightManager::GetInstance( )
{
	if ( Instance == nullptr )
	{
		Instance = new AoLightManager( );
	}
	return *Instance;
}

void AoLightManager::Initialize( )
{
	for ( uint32 Index = 0; Index < MaxLightNumber; ++Index )
	{
		Lights[ Index ] = nullptr;
	}
}

void AoLightManager::DeInitialize( )
{
	for ( uint32 Index = 0; Index < Lights.max_size( ); ++Index )
	{
		Lights[ Index ] = nullptr;
	}
}

void AoLightManager::ForceDeallocate( )
{
	if ( Instance != nullptr )
	{
		Instance->DeInitialize( );
		delete Instance;
		Instance = nullptr;
	}
}

AoLightComponent* AoLightManager::RegisterLight( AoLightComponent* const LightComponent, uint32 LightIndex )
{
	assert( LightIndex < MaxLightNumber );

	AoLightComponent* OldLightComponent = Lights[ LightIndex ];
	Lights[ LightIndex ] = LightComponent;
	return OldLightComponent;
}

AoLightComponent* AoLightManager::UnRegisterLight( uint32 Index )
{
	assert( Index < MaxLightNumber );

	AoLightComponent* OldLightComponent = Lights[ Index ];
	Lights[ Index ] = nullptr;

	return OldLightComponent;
}

void AoLightManager::UnRegisterLight( AoLightComponent* const LightComponent )
{
	for ( uint32 Index = 0; Index < MaxLightNumber; ++Index )
	{
		if ( Lights[ Index ] == LightComponent )
		{
			Lights[ Index ] = nullptr;
			return;
		}
	}
}

void AoLightManager::BindLights( AoMaterial* Material )
{
	uint32 ValidLightsNum = 0;
	for ( uint32 Index = 0; Index < MaxLightNumber; ++Index )
	{
		AoLightComponent* Light = Lights[ Index ];
		if ( Light != nullptr )
		{
			if ( Light->IsValid( ) )
			{
				if ( Light->IsDirty( ) )
				{
					Material->SetVariableByName( TEXT( "Lights" ), &( Light->GetLightData( ) ),
						sizeof( AoLight ) * ValidLightsNum,
						sizeof( AoLight ) );

					Light->SetDirty( false );
					++ValidLightsNum;
				}
			}
		}

		if ( ValidLightsNum > 0 )
		{
			Material->SetIntByName( TEXT( "BindingLightsNumber" ), ValidLightsNum );
		}
	}
}