#pragma once

class AoTimeManager
{
private:
	AoTimeManager( );

public:
	static AoTimeManager& GetInstance( );
	void Initialize( );
	static void ForceDeallocate( );

	void Tick( double DeltaTime );

	void SetTimeScale( float Scale );
	float GetTimeScale( );

	float GetDeltaTime( ) const;
	float GetElasedTime( ) const;

	float GetUnscaledDeltaTime( ) const;
	float GetUnscaledElasedTime( ) const;

	void Start( );
	void Stop( );
	void Resume( );
	void Pause( );
	void Reset( );

	bool IsPaused( ) const;

private:
	static AoTimeManager* Instance;
	static const float OriginTimeScale;

	bool bIsPause;

	float TimeScale;
	double DeltaTime;
	double ElasedTime;

};