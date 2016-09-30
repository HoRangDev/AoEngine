#pragma once

class AoVector
{
public:
	AoVector( float X = 0.0f, float Y = 0.0f, float Z = 0.0f );

	AoVector& operator=( const AoVector& Operand );
	AoVector operator+( float Operand );
	AoVector operator+( const AoVector& Operand );
	AoVector& operator+=( float Operand );
	AoVector& operator+=( const AoVector& Operand );
	AoVector operator-( float Operand );
	AoVector operator-( const AoVector& Operand );
	AoVector& operator-=( float Operand );
	AoVector& operator-=( const AoVector& Operand );
	AoVector operator*( float Operand );
	AoVector operator*( const AoVector& Operand );
	AoVector& operator*=( float Operand );
	AoVector& operator*=( const AoVector& Operand );
	AoVector operator/( float Operand );
	AoVector operator/( const AoVector& Operand );
	AoVector& operator/=( float Operand );
	AoVector& operator/=( const AoVector& Operand );

	/** | is dot product. */
	float operator|( const AoVector& Operand );

	/** ^ is cross product. */
	AoVector operator^( const AoVector& Operand );

	void SetX( float X );
	float GetX( ) const;
	void SetY( float Y );
	float GetY( ) const;
	void SetZ( float Z );
	float GetZ( ) const;

	float Size( ) const;
	float SquaredSize( ) const;

	void Normalize( );
	AoVector GetNormal( ) const;

	bool IsUnit( ) const;
	bool IsOne( ) const;
	bool IsZero( ) const;

public:
	float X;
	float Y;
	float Z;

public:
	static const AoVector Zero;
	static const AoVector One;

};