#include "AoProfileSample.h"
#include "AoMath.h"

AoProfileSample::AoProfileSample( )
{
}

AoProfileSample::AoProfileSample( TimePoint ProfileStartPoint )
	: StartPoint( ProfileStartPoint )
{
}

AoProfileSample AoProfileSample::operator+( const AoProfileSample& Target )
{
	AoProfileSample Sample;
	Sample.StartPoint = Target.StartPoint;
	Sample.EndPoint = Target.EndPoint;
	Sample.Min = ::Min( Min, Target.Min );
	Sample.Max = ::Max( Max, Target.Max );
	Sample.ElasedTime = ( ElasedTime + Target.ElasedTime );
	Sample.Count = Count + Target.Count;

	return Sample;
}

void AoProfileSample::SetProfileStartPoint( TimePoint Point )
{
	this->StartPoint = Point;
}

void AoProfileSample::SetProfileEndPoint( TimePoint Point )
{
	this->EndPoint = Point;
	Min = Max = ElasedTime = GetDeltaTime( );
}

double AoProfileSample::GetDeltaTime( ) const
{
	auto Duration = 
		std::chrono::duration_cast<std::chrono::duration<double>> ( EndPoint - StartPoint );
	return ( Duration.count( ) );
}

double AoProfileSample::GetMin( ) const
{
	return Min;
}

double AoProfileSample::GetAverage( ) const
{
	return (ElasedTime / ::Max( Count, 1 ));
}

double AoProfileSample::GetMax( ) const
{
	return Max;
}

double AoProfileSample::GetElasedTime( ) const
{
	return ElasedTime;
}

int AoProfileSample::GetSampleCount( ) const
{
	return Count;
}
