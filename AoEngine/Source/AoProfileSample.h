#pragma once
#include <chrono>

class AoProfileSample
{
	using TimePoint = std::chrono::high_resolution_clock::time_point;

public:
	AoProfileSample( );
	AoProfileSample( TimePoint ProfileStartPoint );

	AoProfileSample operator+( const AoProfileSample& Target );

	void SetProfileStartPoint( TimePoint Point );
	void SetProfileEndPoint( TimePoint Point );

	float GetDeltaTime( ) const;

	float GetMin( ) const;
	float GetAverage( ) const;
	float GetMax( ) const;
	float GetElasedTime( ) const;
	int GetSampleCount( ) const;

private:
	TimePoint StartPoint;
	TimePoint EndPoint;

	float Min			= 0.0f;
	float Average		= 0.0f;
	float Max			= 0.0f;
	float ElasedTime	= 0.0f;
	int Count			= 1;

};