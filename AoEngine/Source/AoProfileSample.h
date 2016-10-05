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

	double GetDeltaTime( ) const;

	double GetMin( ) const;
	double GetAverage( ) const;
	double GetMax( ) const;
	double GetElasedTime( ) const;
	int GetSampleCount( ) const;

private:
	TimePoint StartPoint;
	TimePoint EndPoint;

	double Min			= 0.0;
	double Average		= 0.0;
	double Max			= 0.0;
	double ElasedTime	= 0.0;
	int Count			= 1;

};