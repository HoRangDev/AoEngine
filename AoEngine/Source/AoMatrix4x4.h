#pragma once
#include <ostream>
#include "DirectXInc.h"
#include "AoVector.h"
#include "AoVector4.h"

class __declspec(align(16)) AoMatrix4x4
{
public:
	//M[ROW INDEX][COLUMN INDEX]
	float M[ 4 ][ 4 ];

public:
	AoMatrix4x4( float InF );
	AoMatrix4x4(
		float InM11 = 0.0f, float InM12 = 0.0f, float InM13 = 0.0f, float InM14 = 0.0f,
		float InM21 = 0.0f, float InM22 = 0.0f, float InM23 = 0.0f, float InM24 = 0.0f,
		float InM31 = 0.0f, float InM32 = 0.0f, float InM33 = 0.0f, float InM34 = 0.0f,
		float InM41 = 0.0f, float InM42 = 0.0f, float InM43 = 0.0f, float InM44 = 0.0f );
	AoMatrix4x4( const AoMatrix4x4& InM );

	AoMatrix4x4& operator=( float Bias );
	AoMatrix4x4& operator=( const AoMatrix4x4& InM );

	AoMatrix4x4 operator+( float Bias ) const;
	AoMatrix4x4 operator+( const AoMatrix4x4& InM ) const;

	AoMatrix4x4 operator-( float Bias ) const;
	AoMatrix4x4 operator-( const AoMatrix4x4& InM ) const;

	AoMatrix4x4 operator*( float Scale ) const;
	AoVector4 operator*( const AoVector4& InV ) const;
	AoMatrix4x4 operator*( const AoMatrix4x4& InM ) const;

	AoMatrix4x4 operator/( float Scale ) const;

	static AoMatrix4x4 CreateTranslationMatrix( AoVector Position );
	static AoMatrix4x4 CreateTranslationMatrix( float X, float Y, float Z );
	static AoMatrix4x4 CreateScaleMatrix( AoVector Scale );
	static AoMatrix4x4 CreateScaleMatrix( float X, float Y, float Z );
	static AoMatrix4x4 CreateRotationX( float Degree );
	static AoMatrix4x4 CreateRotationY( float Degree );
	static AoMatrix4x4 CreateRotationZ( float Degree );
	static AoMatrix4x4 CreateRotation( AoVector Degrees );
	static AoMatrix4x4 CreateInverse( const AoMatrix4x4& InM );
	static AoMatrix4x4 CreateTranspose( const AoMatrix4x4& InM );
	static DirectX::XMMATRIX AoMatrixToXMMATRIX( const AoMatrix4x4& InM );

	friend std::ostream& operator<<( std::ostream& OS, const AoMatrix4x4& InM );

public:
	static AoMatrix4x4 Identity;

};