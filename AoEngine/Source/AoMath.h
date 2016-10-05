#pragma once
#include <cmath>
#include <type_traits>
#include <random>

constexpr float Pi = 3.1415926f;

inline static float RadianToDegree( float Radian )
{
	return ( Radian * 57.29577951f );
}

inline static float DegreeToRadian( float Degree )
{
	return ( Degree * 0.017453293f );
}

inline static float DegreeSin( float Degree )
{
	return ( sin( DegreeToRadian( Degree ) ) );
}

inline static float DegreeCos( float Degree )
{
	return ( cos( DegreeToRadian( Degree ) ) );
}

inline static float DegreeTan( float Degree )
{
	return ( tan( DegreeToRadian( Degree ) ) );
}

inline static float DegreeASin( float Value )
{
	return RadianToDegree( asin( Value ) );
}

inline static float DegreeACos( float Value )
{
	return RadianToDegree( acos( Value ) );
}

inline static float DegreeATan( float Value )
{
	return RadianToDegree( atan( Value ) );
}

inline static float DegreeATan2( float Y, float X )
{
	return RadianToDegree( atan2( Y, X ) );
}

template <typename Ty>
inline static Ty Clamp( Ty Value, Ty Min, Ty Max )
{
	if ( Value < Min )
	{
		return Min;
	}
	else if ( Value > Max )
	{
		return Max;
	}
	else
	{
		return Value;
	}
}

inline static float Clamp01( float Value )
{
	if ( Value > 1.0f )
	{
		return 1.0f;
	}
	else if ( Value < 0.0f )
	{
		return 0.0f;
	}
	else
	{
		return Value;
	}
}

template <typename Ty>
inline static Ty Max( Ty Value, Ty Max )
{
	if ( Value > Max )
	{
		return Value;
	}
	else
	{
		return Max;
	}
}

template <typename Ty>
inline static Ty Min( Ty Value, Ty Min )
{
	if ( Value < Min )
	{
		return Value;
	}
	else
	{
		return Min;
	}
}

template <typename Ty
	, Ty _IsPod = std::is_pod<Ty>::value
	, Ty _IsSigned = std::is_signed<Ty>::value>
	inline static Ty Abs( Ty Value )
{
	if ( Value < static_cast< Ty >( 0 ) )
	{
		return ( Value ) * static_cast< Ty >( -1 );
	}
	else
	{
		return Value;
	}
}

inline static int Random( )
{
	static std::random_device Rd;
	static std::mt19937 REngine( Rd( ) );
	static std::uniform_int_distribution<> Dist( 0, INT_MAX );

	return Dist( REngine );
}

inline static double Random01( )
{
	return Random( ) / static_cast< double >( INT_MAX );
}