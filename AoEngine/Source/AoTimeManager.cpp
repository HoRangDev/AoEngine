#include "AoTimeManager.h"
#include "AoMath.h"

AoTimeManager* AoTimeManager::Instance = 0;
const float AoTimeManager::OriginTimeScale = 1.0f;

AoTimeManager::AoTimeManager( )
{
	Stop( );
}

AoTimeManager& AoTimeManager::GetInstance( )
{
	if ( Instance == nullptr )
	{
		Instance = new AoTimeManager( );
	}

	return *Instance;
}

void AoTimeManager::Initialize( )
{
	Start( );
}

void AoTimeManager::ForceDeallocate( )
{
	if ( Instance != nullptr )
	{
		delete Instance;
		Instance = nullptr;
	}
}

void AoTimeManager::Tick( double DeltaTime )
{
	if ( !bIsPause )
	{
		this->DeltaTime = DeltaTime;
		ElasedTime += DeltaTime;
	}
}

void AoTimeManager::SetTimeScale( float Scale )
{
	this->TimeScale = Scale;
}

float AoTimeManager::GetTimeScale( )
{
	return TimeScale;
}

float AoTimeManager::GetDeltaTime( ) const
{
	return static_cast< float >( DeltaTime * TimeScale );
}

float AoTimeManager::GetElasedTime( ) const
{
	return static_cast< float >( ElasedTime * TimeScale );
}

float AoTimeManager::GetUnscaledDeltaTime( ) const
{
	return static_cast< float >( DeltaTime );
}

float AoTimeManager::GetUnscaledElasedTime( ) const
{
	return static_cast< float >( ElasedTime );
}

void AoTimeManager::Start( )
{
	Stop( );
	this->bIsPause = false;
}

void AoTimeManager::Stop( )
{
	Reset( );
	this->bIsPause = true;
}

void AoTimeManager::Resume( )
{
	this->bIsPause = false;
}

void AoTimeManager::Pause( )
{
	this->bIsPause = true;
}

void AoTimeManager::Reset( )
{
	this->DeltaTime = 0.0f;
	this->ElasedTime = 0.0f;
	this->TimeScale = OriginTimeScale;
}

bool AoTimeManager::IsPaused( ) const
{
	return this->bIsPause;
}
